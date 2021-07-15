[org 0x7C00]

KERNEL_OFFSET equ 0x8200

xor ax, ax
mov es, ax
mov ds, ax
mov ss, ax

mov [BOOT_DRIVE], dl 
mov bp, 0x0500
mov sp, bp
call LoadKernelImageFromDisk 
call EnterProtectedMode 
jmp $

[bits 16]
LoadKernelImageFromDisk:
    mov bx, KERNEL_OFFSET 
    mov dh, 16 
    mov dl, [BOOT_DRIVE]
    call DiskLoadRoutine
    ret

[bits 16]
DiskLoadRoutine:
    pusha                 
    push dx
    mov ah, 0x02    
    mov al, dh      
    mov cl, 0x02        
    mov ch, 0x00
    mov dh, 0x00              
    int 0x13        
    jc DiskReadError   
    pop dx
    cmp al, dh      
    jne DiskReadError
    popa
    ret

DiskReadError:
    jmp $

Gdt32Start: 
    dd 0x0 
    dd 0x0 

Gdt32Code: 
    dw 0xFFFF   
    dw 0x0       
    db 0x0       
    db 10011010b 
    db 11001111b 
    db 0x0       

Gdt32Data:
    dw 0xFFFF
    dw 0x0
    db 0x0
    db 10010010b
    db 11001111b
    db 0x0

Gdt32End:

Gdt32Descriptor:
    dw Gdt32End - Gdt32Start - 1 
    dd Gdt32Start 

CODE_SEG32 equ Gdt32Code - Gdt32Start
DATA_SEG32 equ Gdt32Data - Gdt32Start

[bits 16]
EnterProtectedMode:
    cli 
    lgdt [Gdt32Descriptor] 
    mov eax, cr0
    or eax, 0x1 
    mov cr0, eax
    jmp CODE_SEG32:ProtectedModeEntered 
    jmp $

[bits 32]
ProtectedModeEntered: 
    mov ax, DATA_SEG32 
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ebp, 0x90000 
    mov esp, ebp
    call InitializePageTable
    call EnterLongMode
    jmp $ 

Gdt64Start:
    dd 0x00000000           
    dd 0x00000000           

Gdt64Code:
    dw 0xFFFF           
    dw 0x0000           
    db 0x00             
    db 0b10011010       
    db 0b10101111       
    db 0x00             

Gdt64Data:
    dw 0x0000           
    dw 0x0000           
    db 0x00             
    db 0b10010010       
    db 0b10100000       
    db 0x00             

Gdt64End:

Gdt64Descriptor:
    dw Gdt64End - Gdt64Start - 1        
    dd Gdt64Start                         

CODE_SEG64 equ Gdt64Code - Gdt64Start
DATA_SEG64 equ Gdt64Data - Gdt64Start

[bits 32]
InitializePageTable:
    pushad 
    mov edi, 0x1000
    mov cr3, edi
    xor eax, eax
    mov ecx, 4096
    rep stosd 
    mov edi, cr3
    mov dword[edi], 0x2003      
    add edi, 0x1000             
    mov dword[edi], 0x3003      
    add edi, 0x1000             
    mov dword[edi], 0x4003      
    add edi, 0x1000             
    mov ebx, 0x00000003         
    mov ecx, 512
    PushPageEntry:
        mov dword[edi], ebx
        add ebx, 0x1000
        add edi, 8
        loop PushPageEntry
    mov eax, cr4
    or eax, 1 << 5               
    mov cr4, eax   
    popad
    ret

[bits 32]
EnterLongMode:
    mov ecx, 0xC0000080
    rdmsr
    or eax, 1 << 8
    wrmsr
    mov eax, cr0
    or eax, 1 << 31
    mov cr0, eax
    lgdt [Gdt64Descriptor]
    jmp CODE_SEG64:LongModeEntered
    jmp $

[bits 64]
LongModeEntered:
    cli
    mov ax, DATA_SEG64           
    mov ds, ax                    
    mov es, ax                    
    mov fs, ax                    
    mov gs, ax                    
    mov ss, ax                    
    call KERNEL_OFFSET 

BOOT_DRIVE db 0 

times 510 - ($-$$) db 0
dw 0xAA55
