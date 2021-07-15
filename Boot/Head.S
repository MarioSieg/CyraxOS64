.code64
.extern main

xorq %rax, %rax
xorq %rbx, %rbx
xorq %rcx, %rcx
xorq %rdx, %rdx
xorq %rsi, %rsi
xorq %rdi, %rdi
xorq %r8,  %r8
xorq %r8,  %r9
xorq %r10, %r10
xorq %r11, %r11
xorq %r12, %r12
xorq %r13, %r13
xorq %r14, %r14
xorq %r15, %r15

xorps %xmm0,  %xmm0
xorps %xmm1,  %xmm1
xorps %xmm2,  %xmm2
xorps %xmm3,  %xmm3
xorps %xmm4,  %xmm4
xorps %xmm5,  %xmm5
xorps %xmm6,  %xmm6
xorps %xmm7,  %xmm7
xorps %xmm8,  %xmm8
xorps %xmm9,  %xmm9
xorps %xmm10, %xmm10
xorps %xmm11, %xmm11
xorps %xmm12, %xmm12
xorps %xmm13, %xmm13
xorps %xmm14, %xmm14
xorps %xmm15, %xmm15

callq   main
jmp     .
