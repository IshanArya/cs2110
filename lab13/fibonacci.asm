
.orig x3000

halt

fibonacci
    ADD R6, R6, #-4
    STR R7, R6, #2
    STR R5, R6, #1
    ADD R5, R6, #0
    ADD R6, R6, #-5 ; make space to save registers
    STR R0, R5, #-1,
    STR R1, R5, -2
    STR R2, R5, -3
    STR R3, R5, -4
    STR R4, R5, -5

; start if fib logic
    LDR R0, R5, 4
    ADD R2, R0, -1
    BRnz BASE

    ADD R6, R6, -1
    ADD R1, R0, -1 ; n - 1
    STR R1, R6, 0 ; store n - 1 as param
    JSR fibonacci ; fib(n - 1)
    LDR R1, R6, 0 ; R1 = fib(n - 1)
    ADD R6, R6, 1

    ADD R2, R0, -2 ; n - 2
    STR R2, R6, 0 ; store n - 1 as param
    JSR fibonacci ; fib(n - 1)
    LDR R2, R6, 0 ; R2 = fib(n - 2)
    ADD R6, R6, 2

    ADD R3, R1, R2 ; FIB(N - 1) + FIB(N - 2)
    STR R3, R5, 3 ; return fib(n - 1) + fib(n - 2)
    BR STACK_BREAKDOWN

BASE
    STR R0, R5, 3
    BR STACK_BREAKDOWN

STACK_BREAKDOWN
    LDR R4, R5, -5
    LDR R3, R5, -4
    LDR R2, R5, -3
    LDR R1, R5, -2
    LDR R0, R5, -1

    ADD R6, R5, 0
    LDR R5, R6, 1
    LDR R7, R6, 2
    RET

STACK .fill xF000
.end
