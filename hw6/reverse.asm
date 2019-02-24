;;=============================================================
;;CS 2110 - Spring 2019
;;Homework 6 - Reverse
;;=============================================================
;;Name: Ishan Arya
;;=============================================================

.orig x3000

;;PUT YOUR CODE HERE
    AND R1, R1, 0 ;; load counter i
    LD R2, LENGTH
    ADD R2, R2, #-1 ;; load counter j

CHECK
    NOT R3, R1
    ADD R3, R3, #1 ;; get negative R2 value
    ADD R3, R2, R3 ;; check if i <= j
    BRN STOP

    LD R4, ARRAY
    ADD R4, R4, R1 ;; store index i in R4
    LDR R5, R4, #0 ;; temp store arr[i] in R5
    ST R5, LENGTH ;; temp store arr[i] in LENGTH
    ADD R3, R4, R3 ;; store index j in R3
    LDR R5, R3, #0 ;; temp store arr[j] in R5
    STR R5, R4, #0 ;;store arr[j] at index i in array
    LD R5, LENGTH ;; store old arr[i] in R5
    STR R5, R3, #0 ;; store old arr[i] at index j in array

    ADD R1, R1, #1 ;; i++
    ADD R2, R2, #-1 ;; j--
    BR CHECK ;; loop


STOP
    HALT

ARRAY .fill x4000
LENGTH .fill 7
.end

.orig x4000
.fill 2
.fill 9
.fill 7
.fill 0
.fill 5
.fill 3
.fill 10
.end
