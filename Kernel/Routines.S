.code64

.globl QueryRegSet

QueryRegSet:
    movq    %rax, (%rdi)
    movq    %rbx, 8(%rdi)
    movq    %rcx, 16(%rdi)
    movq    %rdx, 24(%rdi)
    movq    %rsi, 32(%rdi)
    movq    %rdi, 40(%rdi)
    movq    %rsp, 48(%rdi)
    movq    %rbp, 56(%rdi)
    movq    %r8,  64(%rdi)
    movq    %r9,  72(%rdi)
    movq    %r10, 80(%rdi)
    movq    %r11, 88(%rdi)
    movq    %r12, 96(%rdi)
    movq    %r13, 104(%rdi)
    movq    %r14, 112(%rdi)
    movq    %r15, 120(%rdi)

    retq

.macro PUSHAQ
    pushq   %rax
    pushq   %rbx
    pushq   %rcx
    pushq   %rdx
    pushq   %rsi
    pushq   %rdi
    pushq   %rbp
    pushq   %r8
    pushq   %r9
    pushq   %r10
    pushq   %r11
    pushq   %r12
    pushq   %r13
    pushq   %r14
    pushq   %r15
.endm

.macro POPAQ
    popq    %rax
    popq    %rbx
    popq    %rcx
    popq    %rdx
    popq    %rsi
    popq    %rdi
    popq    %rbp
    popq    %r8
    popq    %r9
    popq    %r10
    popq    %r11
    popq    %r12
    popq    %r13
    popq    %r14
    popq    %r15
.endm

.macro ISR id
    .globl InterruptRoutine\id
    InterruptRoutine\id:
        cli
        pushq   $0
        pushq   $\id
        jmp     InterruptStub
.endm

.macro ISR_ERR id
    .globl InterruptRoutine\id
    InterruptRoutine\id:
        cli
        pushq   $\id
        jmp     InterruptStub
.endm

.extern InterruptHandler

InterruptStub:
    PUSHAQ
    movq    120(%rsp), %rdi
    movq    %rsp, %rsi
    callq   InterruptHandler
    POPAQ
    addq    $16, %rsp
    iretq

ISR 0
ISR 1 
ISR 2
ISR 3
ISR 4
ISR 5
ISR 6
ISR 7
ISR_ERR 8
ISR 9
ISR_ERR 10
ISR_ERR 11
ISR_ERR 12
ISR_ERR 13 
ISR_ERR 14 
ISR 15 
ISR 16 
ISR_ERR 17
ISR 18 
ISR 19 
ISR 20
ISR 21
ISR 22
ISR 23
ISR 24
ISR 25
ISR 26
ISR 27
ISR 28
ISR 29
ISR 30
ISR 31
