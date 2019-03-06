;;=======================================
;; CS 2110 - Spring 2019
;; Timed Lab 4
;;=======================================
;; Name:
;;=======================================

;; A little reminder from your friendly neighborhood 2110 TA staff:
;; Do not try to run this directly by pressing 'RUN' in Complx.
;; Instead, load it and use 'Debug' -> 'Simulate Subroutine Call'
;; and choose the 'countMult7' label.

.orig x3000

halt ; Do not remove this line – see note above

; mod(a, b)
;
; This looks funky, but it is a subroutine you can call
; like normal. Just be sure to use the LC3 calling convention!
;
; return 1 if a % b == 0 and 0 otherwise
mod
    .fill x1dbf
    .fill x1dbf
    .fill x7f80
    .fill x1dbf
    .fill x7b80
    .fill x1dbf
    .fill x1ba0
    .fill x1dbe
    .fill x7381
    .fill x7580
    .fill x6344
    .fill x6545
    .fill x94bf
    .fill x14a1
    .fill x1242
    .fill x0402
    .fill x0805
    .fill x03fc
    .fill x5260
    .fill x1261
    .fill x7343
    .fill x0e02
    .fill x5260
    .fill x7343
    .fill x6580
    .fill x6381
    .fill x1d63
    .fill x6f42
    .fill x6b41
    .fill xc1c0

; return count of arguments that are multiples of 7
countMult7 ; countMult7(a, ...)
    ; TODO Stack SETUP code here
    ADD R6, R6, -4 ; increment SP to location of lv 1
    STR R7, R6, 2 ; store return address
    STR R5, R6, 1; store old FP
    ADD R5, R6, 0 ; set new FP
    ADD R6, R6, -4 ; increment SP TO location of lv 2
    STR R0, R6, 4 ; save R0 in lv0
    STR R1, R6, 3 ; save R1 in lv1
    STR R2, R6, 2 ; save R2 in lv2
    STR R3, R6, 1 ; save R3 in lv3
    STR R4, R6, 0 ; save R3 in lv4

    LDR R0, R5, 4 ; load number of elements in array into R0
    ST R0, CHECKPOINT1 ; store number of elements in checkpoint1
    BRZ NO_ANSWER
    ADD R1, R5, 5 ; store address of first element in array in R0
    ST R1, CHECKPOINT2 ; store address of first element in CHECKPOINT2

    ADD R6, R6, -1 ; increment SP
    AND R0, R0, 0 ; nullify 0
    STR R0, R6, 0 ; store number of multiples of 7 at lv 5

    ; TODO your function body code here
    LOOP
        LDR R0, R5, 4 ; load counter into R0
        ADD R0, R0, -1 ; decrement counter
        STR R0, R5, 4 ; store counter in arg 1
        BRN ANSWER
        LD R1, CHECKPOINT2 ; load address of first element into R1
        ADD R1, R0, R1 ; load address of counter element into R1
        LDR R1, R1, 0 ; load counter element into R1
        AND R2, R2, 0 ; nullify R2
        ADD R2, R2, 7 ; set R2 = 7
        ADD R6, R6, -2 ; increment SP
        STR R1, R6, 0 ; store counter element in arg 1
        STR R2, R6, 1 ; store 7 in arg 2
        JSR mod
        LDR R0, R6, 0 ; load whether or not counter element is divisible by 1 into R0
        BRZ END_LOOP
        LDR R0, R5, -5 ; load number of multiples of 7
        ADD R0, R0, 1 ; increment number
        STR R0, R5, -5 ; store number of multiples of 7 at lv 5
    END_LOOP
        ADD R6, R6, 3 ; decrement SP
        BR LOOP


    ; TODO your TEARDOWN code here
    ANSWER
        LDR R0, R5, -5 ; load number of multiples of 7 from lv 5 into R0
        STR R0, R5, 3 ; store count, which is stored in R0, at return value place
        BR CLEANUP
    NO_ANSWER
        STR R0, R5, 3 ; store count, which is stored in R0, at return value place
    CLEANUP
        LDR R0, R5, 0
        LDR R1, R5, -1
        LDR R2, R5, -2
        LDR R3, R5, -3
        LDR R4, R5, -4
        ADD R6, R5, 3 ; set SP to location of return value
        LDR R5, R6, -2 ; set FP to old FP value
        LDR R7, R6, -1 ; set R7 to return address
        RET

; Do not remove or modify anything below this line
; Needed for subroutine calls and grading
STACK .fill xF000
CHECKPOINT1 .blkw 1 ; Should store n
CHECKPOINT2 .blkw 1 ; Should store address of first variable argument

.end
