;;=============================================================
;;CS 2110 - Spring 2019
;;Homework 7 - Recursive Reverse Linked List
;;=============================================================
;;Name: Ishan Arya
;;=============================================================

.orig x3000
    ;; Below is a main function that will:
    ;;      - Print the linked list before reversing
    ;;      - Reverse the linked list
    ;;      - Print the reversed linked list
    ;; You shouldn't need to change this main function.

    LDI R1, LL          ; Load first node to R1
    JSR print_ll

    LD R6, STACK        ; Initialize stack pointer
    ADD R6, R6, -1      ; Make room on stack for argument
    STR R1, R6, 0       ; Place first node on stack as argument
    JSR reverse

    LDR R1, R6, 0       ; Load result of reverse
    JSR print_ll
    halt


reverse
;;=============================================================
;; YOUR CODE GOES HERE

    ADD R6, R6, -4 ; increment SP to location of lv 1
    STR R7, R6, 2 ; store return address
    STR R5, R6, 1; store old FP
    ADD R5, R6, 0 ; set new FP
    ADD R6, R6, -1 ; increment SP TO location of lv 2
    STR R0, R6, 1 ; save R0 in lv1
    STR R1, R6, 0 ; save R1 in lv2

    LDR R0, R5, 4 ; load head node into R0
    BRZ RET_HEAD ; return head if head is null
    LDR R0, R0, 0 ; load head.next into R0
    BRZ RET_HEAD ; return head if head.next is null

    ADD R6, R6, -1 ; increment SP
    STR R0, R6, 0 ; store head.next as arg 1
    JSR reverse ; recurse with head.next

    LDR R0, R5, 4 ; load head node into R0
    LDR R1, R0, 0 ; load head.next into R1
    STR R0, R1, 0 ; set head.next.next = head
    AND R1, R1, 0 ; nullify R1
    STR R1, R0, 0 ; set head.next = null

    LDR R1, R6, 0 ; load new_head into R1
    STR R1, R5, 3 ; store new_head at return value

    CLEANUP
        LDR R0, R5, 0
        LDR R1, R5, -1
        ADD R6, R5, 3 ; set SP to location of return value
        LDR R5, R6, -2 ; set FP to old FP value
        LDR R7, R6, -1 ; set R7 to return address
        RET

    RET_HEAD
        LDR R0, R5, 4 ; load head node into R0
        STR R0, R5, 3 ; store head in return value
        BR CLEANUP ; exit
    
    

;;=============================================================


; A subroutine that will print a linked list
; given the first node is in R1
print_ll
    ST R0, Save0        ; Save R0
    ST R1, Save1        ; Save R1
    ST R7, Save7        ; Save R7
    LD R0, QUOTES       ; print('"')
    OUT
loop
    LDR R0, R1, 1       ; R0 = curr.val
    OUT                 ; print(curr.val)
    LDR R1, R1, 0       ; R1 = curr.next
    BRz print_done      ; curr.next == null -> done
    BRnzp loop          ;
print_done
    LD R0, QUOTES       ; print('"')
    OUT
    LD R0, NEWLINE      ; print('\n')
    OUT
    LD R0, Save0        ; Restore R0
    LD R1, Save1        ; Restore R1
    LD R7, Save7        ; Restore R7
    RET
Save0       .blkw 1
Save1       .blkw 1
Save7       .blkw 1
QUOTES      .fill '"'
NEWLINE     .fill '\n'

LL .fill x6000
STACK .fill xF000
.end

.orig x4000
.fill x4002         ; x4000
.fill 'a'           ; x4001
.fill x4004         ; x4002
.fill 'b'           ; x4003
.fill x4006         ; x4004
.fill 'c'           ; x4005
.fill x4008         ; x4006
.fill 'd'           ; x4007
.fill x400A         ; x4008
.fill 'e'           ; x4009
.fill x0000         ; x400A
.fill 'f'           ; x400B
.end


.orig x6000
.fill x4000
.fill 6
.end
