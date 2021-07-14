[bits 64]
[extern IsrHandler]

InterruptStub:   
    nop

global InterruptRoutine0
global InterruptRoutine1
global InterruptRoutine2
global InterruptRoutine3
global InterruptRoutine4
global InterruptRoutine5
global InterruptRoutine6
global InterruptRoutine7
global InterruptRoutine8
global InterruptRoutine9
global InterruptRoutine10
global InterruptRoutine11
global InterruptRoutine12
global InterruptRoutine13
global InterruptRoutine14
global InterruptRoutine15
global InterruptRoutine16
global InterruptRoutine17
global InterruptRoutine18
global InterruptRoutine19
global InterruptRoutine20
global InterruptRoutine21
global InterruptRoutine22
global InterruptRoutine23
global InterruptRoutine24
global InterruptRoutine25
global InterruptRoutine26
global InterruptRoutine27
global InterruptRoutine28
global InterruptRoutine29
global InterruptRoutine30
global InterruptRoutine31

InterruptRoutine0:
    cli
    push byte 0
    push byte 0
    jmp InterruptStub

InterruptRoutine1:
    cli
    push byte 0
    push byte 1
    jmp InterruptStub

InterruptRoutine2:
    cli
    push byte 0
    push byte 2
    jmp InterruptStub

InterruptRoutine3:
    cli
    push byte 0
    push byte 3
    jmp InterruptStub

InterruptRoutine4:
    cli
    push byte 0
    push byte 4
    jmp InterruptStub

InterruptRoutine5:
    cli
    push byte 0
    push byte 5
    jmp InterruptStub

InterruptRoutine6:
    cli
    push byte 0
    push byte 6
    jmp InterruptStub

InterruptRoutine7:
    cli
    push byte 0
    push byte 7
    jmp InterruptStub

InterruptRoutine8:
    cli
    push byte 8
    jmp InterruptStub

InterruptRoutine9:
    cli
    push byte 0
    push byte 9
    jmp InterruptStub

InterruptRoutine10:
    cli
    push byte 10
    jmp InterruptStub

InterruptRoutine11:
    cli
    push byte 11
    jmp InterruptStub

InterruptRoutine12:
    cli
    push byte 12
    jmp InterruptStub

InterruptRoutine13:
    cli
    push byte 13
    jmp InterruptStub

InterruptRoutine14:
    cli
    push byte 14
    jmp InterruptStub

InterruptRoutine15:
    cli
    push byte 0
    push byte 15
    jmp InterruptStub

InterruptRoutine16:
    cli
    push byte 0
    push byte 16
    jmp InterruptStub

InterruptRoutine17:
    cli
    push byte 0
    push byte 17
    jmp InterruptStub

InterruptRoutine18:
    cli
    push byte 0
    push byte 18
    jmp InterruptStub


InterruptRoutine19:
    cli
    push byte 0
    push byte 19
    jmp InterruptStub

InterruptRoutine20:
    cli
    push byte 0
    push byte 20
    jmp InterruptStub

InterruptRoutine21:
    cli
    push byte 0
    push byte 21
    jmp InterruptStub

InterruptRoutine22:
    cli
    push byte 0
    push byte 22
    jmp InterruptStub

InterruptRoutine23:
    cli
    push byte 0
    push byte 23
    jmp InterruptStub

InterruptRoutine24:
    cli
    push byte 0
    push byte 24
    jmp InterruptStub

InterruptRoutine25:
    cli
    push byte 0
    push byte 25
    jmp InterruptStub

InterruptRoutine26:
    cli
    push byte 0
    push byte 26
    jmp InterruptStub

InterruptRoutine27:
    cli
    push byte 0
    push byte 27
    jmp InterruptStub

InterruptRoutine28:
    cli
    push byte 0
    push byte 28
    jmp InterruptStub

InterruptRoutine29:
    cli
    push byte 0
    push byte 29
    jmp InterruptStub

InterruptRoutine30:
    cli
    push byte 0
    push byte 30
    jmp InterruptStub

InterruptRoutine31:
    cli
    push byte 0
    push byte 31
    jmp InterruptStub
