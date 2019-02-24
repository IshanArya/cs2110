;;=============================================================
;;CS 2110 - Spring 2019
;;Homework 6 - Gates
;;=============================================================
;;Name: Ishan Arya
;;=============================================================

.orig x3000

    ;;YOUR CODE GOES HERE
    LD R1, X
    NOT R1, R1
    ADD R1, R1, #1 ;;make X negative
    LD R2, B
    ADD R2, R2, R1 ;;if B > X, R2 will be positive
    BRZ ELSE ;; if 0 go to else
    ST R2, X
    LD R2, A
    ADD R2, R2, R1 ;;if A > X, R2 will be positive
    BRZ ELSE ;; if 0 go to else
    BRP APOS
    BRN ANEG

APOS
    LD R2, X
    BRN NAND
    BRP NOR
ANEG
    LD R2, X
    BRN LOR
    BRP LAND

NAND
    LD R1, A
    LD R2, B
    AND R1, R1, R2
    NOT R1, R1
    ST R1, ANSWER
    HALT
NOR
    LD R1, A
    LD R2, B
    NOT R1, R1
    NOT R2, R2
    AND R1, R1, R2
    ST R1, ANSWER
    HALT
LOR
    LD R1, A
    LD R2, B
    NOT R1, R1
    NOT R2, R2
    AND R1, R1, R2
    NOT R1, R1
    ST R1, ANSWER
    HALT
LAND
    LD R1, A
    LD R2, B
    AND R1, R1, R2
    ST R1, ANSWER
    HALT

ELSE
    LD R2, A
    NOT R2, R2
    ST R2, ANSWER
    HALT
A   .fill x3030 ;x3030
B   .fill x4040 ;x4040
X   .fill x4040

ANSWER .blkw 1

.end
