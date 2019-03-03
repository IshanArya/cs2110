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

MULT
;; Put the code for the MULT subroutine here
    ADD R6, R6, -4 ; increment SP to location of lv 1
    STR R7, R6, 2 ; store return address
    STR R5, R6, 1; store old FP
    ADD R5, R6, 0 ; store new FP

    AND R0, R0, 0 ; set result to R0
    LDR R1, R5, 4 ; load first arg into R1
    LDR R2, R5, 5 ; load second arg into R2

    LOOPMULT
        BRZ ENDMULT ; exit loop
        ADD R0, R0, R1 ; increment result by 1st arg
        ADD R2, R2, -1 ; decrement 2nd arg by 1
        BR LOOPMULT ; loop

    ENDMULT
        STR R0, R5, 3 ; store result in return value spot
        BR CLEANUP ; cleanup routine and return


LENGTH
;; Put the code for the LENGTH subroutine here
    ADD R6, R6, -4 ; increment SP to location of lv 1
    STR R7, R6, 2 ; store return address
    STR R5, R6, 1; store old FP
    ADD R5, R6, 0 ; store new FP

    AND R0, R0, 0 ; nullify R0

    LOOPLENGTH
        LDR R3, R5, 4 ; load address of start of string into R3
        ADD R3, R3, R0 ; increment character address by length so far
        LDR R3, R3, 0 ; load character at address in R3
        BRZ ENDLENGTH ; exit loop
        ADD R0, R0, 1 ; increment length
        BR LOOPLENGTH ; loop

    ENDLENGTH
        STR R0, R5, 3 ; store length in return value spot
        BR CLEANUP ; cleanup routine and return
    

decimalStringToInt
;; Put the code for the DECIMALSTRINGTOINT subroutine here
    ADD R6, R6, -4 ; increment SP to location of lv 1
    STR R7, R6, 2 ; store return address
    STR R5, R6, 1; store old FP
    ADD R5, R6, 0 ; store new FP

;; call LENGTH subroutine
    ADD R6, R6, -1 ; increment SP
    LDR R0, R5, 4 ; load decimal string into R0
    STR R0, R6, 0 ; load decimal string as first parameter
    JSR LENGTH ; jump to LENGTH subroutine
    LDR R0, R6, 0 ; store length of decimal string in R0
    NOT R0, R0 ; turning length negative
    ADD R0, R0, 1 ; turned length negative
    ADD R6, R6, 2 ; go to local variable place 1
    STR R0, R6, 0 ; store negative length of decimal string here

    AND R1, R1, 0 ; make R1 the counter
    ADD R6, R6, -1 ; increment SP
    STR R1, R6, 0 ; store "ret" at lv place 2
    ADD R1, R1, -1 ; initialize counter i
    ADD R6, R6, -1 ; increment SP
    STR R1, R6, 0 ; store counter at lv place 3
    LOOPDECIMAL
        ;; loop conditional
        LDR R1, R5, -2 ; load R1 with counter value
        LDR R0, R5, 0 ; load R0 with negative string length
        ADD R1, R1, 1 ; increment counter
        STR R1, R5, -2 ; update counter value in memory
        ADD R2, R1, R0 ; check if counter >= string length
        BRZP ENDDECIMAL ; if it is, go to end phase
        
        ;; loop body
        LDR R2, R5, -1 ; load "ret" into R2
        AND R3, R3, 0 ; nullify R3
        ADD R3, R3, 10 ; store 10 in R3
        ADD R6, R6, -1 ; increment counter
        STR R3, R6, 0 ; store 10 in arg 2
        ADD R6, R6, -1 ; increment counter
        STR R2, R6, 0 ; store ret in arg 1
        JSR MULT ; jump to MULT subroutine
        LDR R2, R6, 0 ; load return value of MULT into R2
        ADD R6, R6, 3 ; revert R6 to lv 3
        LDR R3, R5, 4 ; store address of decimal string into R3
        LDR R1, R5, -2 ; load R1 with counter value
        ADD R3, R3, R1 ; get address of character at location of counter
        LDR R3, R3, 0 ; get character at index "counter" in string
        ADD R3, R3, -16
        ADD R3, R3, -16
        ADD R3, R3, -16 ; convert character to number by decrementing by 48
        ADD R2, R3, R2 ; add number to "ret"
        STR R2, R5, -1 ; store "ret" at lv 2
        BR LOOPDECIMAL ; loop again

    ENDDECIMAL
        LDR R2, R5, -1 ; load "ret" into R2
        STR R2, R5, 3 ; store "ret" in return position
        BR CLEANUP ; cleanup routine and return


CLEANUP
    ADD R6, R5, 3 ; set SP to location of return value
    LDR R5, R6, -2 ; set FP to old FP value
    LDR R7, R6, -1 ; set R7 to return address
    RET


NUM .fill 48
; Needed by Simulate Subroutine Call in complx
STACK .fill xF000
.end

.orig x6000
.stringz "10098"
.end
