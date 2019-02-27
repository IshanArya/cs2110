;;====================================================
;; CS 2110 - Spring 2019
;; Timed Lab 3
;; tl3.asm
;;====================================================
;; Name: Ishan Arya
;;====================================================

.orig x3000

;;YOUR CODE GOES HERE :D

    LD R0, ARRAY ;;load array starting point into R0
    LD R1, LEN ; load length of array into R1
    ADD R0, R0, R1 ; load position after last in array into R0
    LDR R0, R0, -1 ; load last element in array into R0
    ST R0, CHECKPOINT1 ; store last element in CHECKPOINT1
    BRZ ZERO
    BRN NEGATIVE
    BRP POSITIVE

NEGATIVE
    AND R1, R1, 0 ; nullify R1
    ADD R1, R1, -1 ; store 0 in R1
    ST R1, CHECKPOINT2 ; store -1 in CHECKPOINT2

    AND R2, R2, 0 ; nullify R2
    LD R0, ARRAY ; load R0 with location of first element in array
    LD R3, LEN ; load length of array into R3
    ADD R3, R0, R3 ; index after last of array
    NOT R3, R3 ; make R3 negative
    ADD R3, R3, 1 ; made R3 negative
    ADD R0, R0, -1 ; start 1 before START
NEGLOOP
    ADD R0, R0, 1 ; increment counter
    ADD R1, R0, R3 ; check if reached the end
    BRZP DONE ; exit loop if done
    LDR R1, R0, 0 ; load R1 with first element in array
    BRZP NEGLOOP ; if positive or 0, reloop
    ADD R2, R2, R1 ; add element to sum
    BR NEGLOOP ; loop again

POSITIVE
    AND R1, R1, 0 ; nullify R1
    ADD R1, R1, 1 ; store 0 in R1
    ST R1, CHECKPOINT2 ; store 1 in CHECKPOINT2

    AND R2, R2, 0 ; nullify R2
    LD R0, ARRAY ; load R0 with location of first element in array
    LD R3, LEN ; load length of array into R3
    ADD R3, R0, R3 ; index after last of array
    NOT R3, R3 ; make R3 negative
    ADD R3, R3, 1 ; made R3 negative
    ADD R0, R0, -1 ; start 1 before START
POSLOOP
    ADD R0, R0, 1 ; increment counter
    ADD R1, R0, R3 ; check if reached the end
    BRZP DONE ; exit loop if done
    LDR R1, R0, 0 ; load R1 with first element in array
    BRNZ POSLOOP ; if negative or 0, reloop
    ADD R2, R2, R1 ; add element to sum
    BR POSLOOP ; loop again


DONE
    ST R2, CHECKPOINT3 ; done
    HALT

ZERO
    AND R1, R1, 0 ; nullify R1
    ST R1, CHECKPOINT2 ; store 1 in CHECKPOINT2
    ST R1, CHECKPOINT3 ; store 1 in CHECKPOINT3
    HALT

ARRAY   .fill x5000
LEN     .fill 6

CHECKPOINT1 .blkw 1
CHECKPOINT2 .blkw 1
CHECKPOINT3 .blkw 1
.end