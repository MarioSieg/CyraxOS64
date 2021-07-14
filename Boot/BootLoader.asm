[org 0x7C00]

KERNEL_OFFSET equ 0x8200

jmp 0x00:entry

entry:
    xor ax, ax
    mov es, ax
    mov ds, ax
    mov ss, ax

    mov [BOOT_DRIVE], dl 
    mov bp, 0x0500
    mov sp, bp
    call load_kernel 
    call switch_to_pm 
    jmp $

disk_load:
    pusha                 
    push dx
    mov ah, 0x02    
    mov al, dh      
    mov cl, 0x02        
    mov ch, 0x00
    mov dh, 0x00              
    int 0x13        
    jc disk_error   
    pop dx
    cmp al, dh      
    jne sectors_error
    popa
    ret

disk_error:
    jmp $

sectors_error:
    jmp $

gdt32_start: 
    dd 0x0 
    dd 0x0 

gdt32_code: 
    dw 0xffff    
    dw 0x0       
    db 0x0       
    db 10011010b 
    db 11001111b 
    db 0x0       

gdt32_data:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10010010b
    db 11001111b
    db 0x0

gdt32_end:

gdt32_descriptor:
    dw gdt32_end - gdt32_start - 1 
    dd gdt32_start 

CODE_SEG32 equ gdt32_code - gdt32_start
DATA_SEG32 equ gdt32_data - gdt32_start

[bits 16]
switch_to_pm:
    cli 
    lgdt [gdt32_descriptor] 
    mov eax, cr0
    or eax, 0x1 
    mov cr0, eax
    jmp CODE_SEG32:init_pm 

[bits 32]
init_pm: 
    mov ax, DATA_SEG32 
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ebp, 0x90000 
    mov esp, ebp
    call BEGIN_PM 

[bits 32]
BEGIN_PM:
    call InitializePageTable
    call elevate_protected
    jmp $ 

[bits 16]
load_kernel:
    mov bx, KERNEL_OFFSET 
    mov dh, 16 
    mov dl, [BOOT_DRIVE]
    call disk_load
    ret

gdt_64_start:

; Define the null sector for the 64 bit gdt
; Null sector is required for memory integrity check
gdt_64_null:
    dd 0x00000000           ; All values in null entry are 0
    dd 0x00000000           ; All values in null entry are 0

; Define the code sector for the 64 bit gdt
gdt_64_code:
    ; Base:     0x00000
    ; Limit:    0xFFFFF
    ; 1st Flags:        0b1001
    ;   Present:        1
    ;   Privelege:      00
    ;   Descriptor:     1
    ; Type Flags:       0b1010
    ;   Code:           1
    ;   Conforming:     0
    ;   Readable:       1
    ;   Accessed:       0
    ; 2nd Flags:        0b1100
    ;   Granularity:    1
    ;   32-bit Default: 0
    ;   64-bit Segment: 1
    ;   AVL:            0

    dw 0xFFFF           ; Limit (bits 0-15)
    dw 0x0000           ; Base  (bits 0-15)
    db 0x00             ; Base  (bits 16-23)
    db 0b10011010       ; 1st Flags, Type flags
    db 0b10101111       ; 2nd Flags, Limit (bits 16-19)
    db 0x00             ; Base  (bits 24-31)

; Define the data sector for the 64 bit gdt
gdt_64_data:
    ; Base:     0x00000
    ; Limit:    0x00000
    ; 1st Flags:        0b1001
    ;   Present:        1
    ;   Privelege:      00
    ;   Descriptor:     1
    ; Type Flags:       0b0010
    ;   Code:           0
    ;   Expand Down:    0
    ;   Writeable:      1
    ;   Accessed:       0
    ; 2nd Flags:        0b1100
    ;   Granularity:    1
    ;   32-bit Default: 0
    ;   64-bit Segment: 1
    ;   AVL:            0

    dw 0x0000           ; Limit (bits 0-15)
    dw 0x0000           ; Base  (bits 0-15)
    db 0x00             ; Base  (bits 16-23)
    db 0b10010010       ; 1st Flags, Type flags
    db 0b10100000       ; 2nd Flags, Limit (bits 16-19)
    db 0x00             ; Base  (bits 24-31)

gdt_64_end:

; Define the gdt descriptor
; This data structure gives cpu length and start address of gdt
; We will feed this structure to the CPU in order to set the protected mode GDT
gdt_64_descriptor:
    dw gdt_64_end - gdt_64_start - 1        ; Size of GDT, one byte less than true size
    dd gdt_64_start                         ; Start of the 64 bit gdt

; Define helpers to find pointers to Code and Data segments
code_seg_64:                            equ gdt_64_code - gdt_64_start
data_seg_64:                            equ gdt_64_data - gdt_64_start

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
    add_page_entry_protected:
        mov dword[edi], ebx
        add ebx, 0x1000
        add edi, 8
        loop add_page_entry_protected
    mov eax, cr4
    or eax, 1 << 5               
    mov cr4, eax   
    popad
    ret

    [bits 32]

elevate_protected:
    ; Elevate to 64-bit mode
    mov ecx, 0xC0000080
    rdmsr
    or eax, 1 << 8
    wrmsr

    ; Enable paging
    mov eax, cr0
    or eax, 1 << 31
    mov cr0, eax
    
    lgdt [gdt_64_descriptor]
    jmp code_seg_64:init_lm

[bits 64]
    init_lm:
    cli
    mov ax, data_seg_64           ; Set the A-register to the data descriptor.
    mov ds, ax                    ; Set the data segment to the A-register.
    mov es, ax                    ; Set the extra segment to the A-register.
    mov fs, ax                    ; Set the F-segment to the A-register.
    mov gs, ax                    ; Set the G-segment to the A-register.
    mov ss, ax                    ; Set the stack segment to the A-register.
    call KERNEL_OFFSET 

BOOT_DRIVE db 0 

times 510 - ($-$$) db 0
dw 0xaa55
