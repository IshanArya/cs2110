;;=============================================================
;;CS 2110 - Spring 2019
;;Homework 6 - Linked List
;;=============================================================
;;Name: Ishan Arya
;;=============================================================

.orig x3000

    LD R0, DATA ;; load searching data
    NOT R0, R0 ;; making data negative
    ADD R0, R0, #1 ;; R0 is now -DATA
    LD R2, LL ;; load LL location
    ADD R1, R2, #1 ;; get location of length of LL
    LDR R1, R1, #0 ;; R1 = length of LL

LOOP
    LDI R2, LL ;; R2 = address of next node
    BRZ STOP ;; if at end of list, stop
    ST R2, LL ;; store current node's address in LL
    LDR R3, R2, #1 ;; store current node's data in R3
    ADD R3, R3, R0 ;; subtract node's data by checking data
    BRNP LOOP ;; if not equal to data, move on
    STR R1, R2, #1 ;; else store length of LL in data
    BRNZP LOOP ;; loop to check if other data equals checking data

STOP
    HALT

DATA .fill 10
LL .fill x6000
.end

.orig x4000
.fill x4008
.fill 5
.fill x400A
.fill 10
.fill x4002
.fill 9
.fill x0000 
.fill 3
.fill x4004
.fill 10
.fill x4006
.fill 7
.end

.orig x6000
.fill x4000
.fill 6
.end
