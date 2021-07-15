.equ KERNEL_OFFSET, 0x8200

# The BIOS gives the control to us
# Main entry of the boot loader:
.code16
MachineBoot:
    xorw    %ax, %ax                # Clear segment registers
    movw    %ax, %es
    movw    %ax, %ds
    movw    %ax, %ss
    movb    %dl, (BOOT_DRIVE)       # The BIOS gives us the boot drive in %dl. We backup it because %dl will probably be overridden
    movw    $0x0500, %bp            # Setup stack
    movw    %bp, %sp                # Setup stack
    callw   LoadKernelImageFromDisk # Load out kernel from disk
    callw   EnterProtectedMode      # Switch from 16-bit real mode into 32-bit protected mode

# Loads the kernel from disk using BIOS
.code16
LoadKernelImageFromDisk:
    movw    $KERNEL_OFFSET, %bx
    movb    $16, %dh 
    movb    (BOOT_DRIVE), %dl
    callw   DiskLoadRoutine         # Invoke disk load routine
    retw

BOOT_DRIVE: .byte 0                 # Boot drive memory storage

# Loads the kernel from disk using BIOS interrupts
.code16
DiskLoadRoutine:
    pusha
    pushw   %dx
    movb    $0x02, %ah    
    movb    %dh, %al      
    movb    $0x02, %cl
    xorb    %ch, %ch
    xorb    %dh, %dh           
    int     $0x13                   # Load from disk using BIOS interrupts
    jc      DiskReadError           # Failed to read disks
    popw    %dx
    cmpb    %dh, %al      
    jne     DiskReadError           # Wrong amount of sectors read
    popa
    retw

# For now just loop if there's a disk error
DiskReadError:
    jmp     .

# Setup GDT (global descriptor table) for 32-bit protected mode
Gdt32Start:
    .long 0x00000000
    .long 0x00000000

Gdt32Code: 
    .word 0xFFFF   
    .word 0x0000       
    .byte 0x00   
    .byte 0b10011010
    .byte 0b11001111 
    .byte 0x00      

Gdt32Data:
    .word 0xFFFF
    .word 0x0000
    .byte 0x00
    .byte 0b10010010
    .byte 0b11001111
    .byte 0x00

Gdt32End:

Gdt32Descriptor:
    .word Gdt32End - Gdt32Start - 1 
    .long Gdt32Start 

.equ CODE_SEG32, Gdt32Code - Gdt32Start # Code segment offsets for 32-bit GDT
.equ DATA_SEG32, Gdt32Data - Gdt32Start # Data segment offsets for 32-bit GDT

# Enters 32-bit protected mode
.code16
EnterProtectedMode:
    cli 
    lgdtw   (Gdt32Descriptor)
    movl    %cr0, %eax
    orl     $1, %eax
    movl    %eax, %cr0
    ljmpw   $CODE_SEG32, $ProtectedModeEntered 
    jmp .

# Now we are in 32-bit protected mode
.code32
ProtectedModeEntered: 
    movw    $DATA_SEG32, %ax 
    movw    %ax, %ds
    movw    %ax, %ss
    movw    %ax, %es
    movw    %ax, %fs
    movw    %ax, %gs
    movl    $0x90000, %ebp
    movl    %ebp, %esp
    calll   InitializePageTable
    calll   EnterLongMode
    jmp     . 

# Setup GDT (global descriptor table) for 64-bit long mode
Gdt64Start:
    .long 0x00000000           
    .long 0x00000000           

Gdt64Code:
    .word 0xFFFF           
    .word 0x0000           
    .byte 0x00             
    .byte 0b10011010       
    .byte 0b10101111       
    .byte 0x00             

Gdt64Data:
    .word 0x0000           
    .word 0x0000           
    .byte 0x00             
    .byte 0b10010010       
    .byte 0b10100000       
    .byte 0x00             

Gdt64End:

Gdt64Descriptor:
    .word Gdt64End - Gdt64Start - 1        
    .long Gdt64Start                         

.equ CODE_SEG64, Gdt64Code - Gdt64Start # Code segment offsets for 64-bit GDT
.equ DATA_SEG64, Gdt64Data - Gdt64Start # Code segment offsets for 64-bit GDT

# Initialize and active the page table 
.code32
InitializePageTable:
    pushal
    movl    $0x1000, %edi
    movl    %edi, %cr3
    xorl    %eax, %eax
    movl    $4096, %ecx
    rep     stosl
    movl    %cr3, %edi
    movl    $0x2003, (%edi)
    addl    $0x1000, %edi
    movl    $0x3003, (%edi)
    addl    $0x1000, %edi
    movl    $0x4003, (%edi)
    addl    $0x1000, %edi
    movl    $0x00000003, %ebx
    movl    $512, %ecx

    PushPageEntry:
    movl    %ebx, (%edi)
    addl    $0x1000, %ebx
    addl    $8, %edi
    loop PushPageEntry

    movl    %cr4, %eax
    orl     $(1 << 5), %eax
    movl    %eax, %cr4
    popal
    retl

# Enter long mode by:
#   1. enabling long mode in %msr
#   2. enabling paging in %cr0
#   3. loading 64-bit GDT
#   4. longjump with different pipeline
.code32
EnterLongMode:
    movl    $0xC0000080, %ecx                   # Enable long mode
    rdmsr                                       # Enable long mode
    orl     $(1 << 8), %eax                     # Enable long mode
    wrmsr                                       # Enable long mode
    movl    %cr0, %eax                          # Enable paging
    orl     $(1 << 31), %eax                    # Enable paging
    movl    %eax, %cr0                          # Enable paging
    lgdtl   (Gdt64Descriptor)                   # Load 64-bit GDT
    ljmpl   $CODE_SEG64, $LongModeEntered       # Far jump using different segment

# Now we are inside long mode.
# We set all segment registers again and call the kernel head.
.code64
LongModeEntered:
    cli
    movw    $DATA_SEG64, %ax
    movw    %ax, %ds
    movw    %ax, %es
    movw    %ax, %fs
    movw    %ax, %gs
    movw    %ax, %ss
    movq    $KERNEL_OFFSET, %rax
    callq   *%rax
    hlt

.fill 510-(.-MachineBoot), 1, 0
.word 0xAA55
