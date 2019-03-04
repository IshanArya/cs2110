;;=======================================
;; CS 2110 - Spring 2019
;; Homework 7
;;=======================================
;; Name: Ishan Arya
;;=======================================

;; Little reminder from your friendly neighborhood 2110 TA staff:
;; don't run this directly by pressing 'RUN' in complx, since there is nothing
;; put at address x3000. Instead, load it and use 'Debug' -> 'Simulate Subroutine
;; Call' and choose the 'decimalStringToInt' label.

.orig x3000

halt

checkTreeEquality
;; Put the code for the CHECKTREEEQUALITY subroutine here
    ADD R6, R6, -4 ; increment SP to location of lv 1
    STR R7, R6, 2 ; store return address
    STR R5, R6, 1; store old FP
    ADD R5, R6, 0 ; store new FP
    ADD R6, R6, -2 ; increment SP
    STR R0, R6, 2 ; store R0 at lv 1
    STR R1, R6, 1 ; store R1 at lv 2
    STR R2, R6, 0 ; store R2 at lv 3

    LDR R1, R5, 4 ; load node 1 into R1
    BRZ IMMEDIATE_CHECK ; if node 1 is null, immediately check node 2
    LDR R2, R5, 5 ; load node 2 into R2
    BRZ RET_FALSE ; if node 2 is null at this point, must be false

    ;; at this point, both node 1 and node 2 are not null
    ;; going to check current, left node, then right node

    ;; check current
    LDR R1, R1, 2 ; load node1 data into R1
    LDR R2, R2, 2 ; load node2 data into R2
    NOT R2, R2 ; negate node2 data
    ADD R2, R2, 1 ; made node2 data negative
    ADD R2, R2, R1 ; should equal 0 if node1.data = node2.data
    BRNP RET_FALSE ; if not 0, return false

    LDR R1, R5, 4 ; load node 1 into R1
    LDR R2, R5, 5 ; load node 2 into R2

    ;; check left
    LDR R1, R1, 0 ; load left node of node 1 into R1
    LDR R2, R2, 0 ; load left node of node 2 into R2
    ADD R6, R6, -1 ; increment SP
    STR R2, R6, 0 ; store node2.left in arg 2
    ADD R6, R6, -1 ; increment SP
    STR R1, R6, 0 ; store node1.left in arg 1
    JSR checkTreeEquality ; recurese on this method with left nodes
    LDR R0, R6, 0 ; load return value into R0
    BRZ RET_FALSE ; if false, return false
    ADD R6, R6, 3 ; move R6 back to where it was before subroutine

    LDR R1, R5, 4 ; load node 1 into R1
    LDR R2, R5, 5 ; load node 2 into R2

    ;; check right
    LDR R1, R1, 1 ; load left node of node 1 into R1
    LDR R2, R2, 1 ; load left node of node 2 into R2
    ADD R6, R6, -1 ; increment SP
    STR R2, R6, 0 ; store node2.left in arg 2
    ADD R6, R6, -1 ; increment SP
    STR R1, R6, 0 ; store node1.left in arg 1
    JSR checkTreeEquality ; recurese on this method with left nodes
    LDR R0, R6, 0 ; load return value into R0
    BRZ RET_FALSE ; if false, return false
    
    BR RET_TRUE ; if not false yet, return true


    IMMEDIATE_CHECK
        LDR R2, R5, 5 ; load node 2 into R2
        BRZ RET_TRUE
        BRNP RET_FALSE

    RET_TRUE
        AND R0, R0, 0 ; nullify R0
        ADD R0, R0, 1 ; make R0 = 1
        STR R0, R5, 3 ; store 1 in ret value
        BR CLEANUP
    RET_FALSE
        AND R0, R0, 0 ; nullify R0
        STR R0, R5, 3 ; store 0 in ret value
        BR CLEANUP

CLEANUP
    LDR R0, R5, 0
    LDR R1, R5, -1
    LDR R2, R5, -2
    ADD R6, R5, 3 ; set SP to location of return value
    LDR R5, R6, -2 ; set FP to old FP value
    LDR R7, R6, -1 ; set R7 to return address
    RET




; Needed by Simulate Subroutine Call in complx
STACK .fill xF000
.end
