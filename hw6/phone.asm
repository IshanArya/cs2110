;;=============================================================
;;CS 2110 - Spring 2019
;;Homework 6 - Phone Number
;;=============================================================
;;Name: Ishan Arya
;;=============================================================

.orig x3000

	;;INSERT CODE AT THIS LOCATION
	LD R0, STRING ;; store location of start of string in R0

	LDR R1, R0, #14 ;; load (hopefully) null character into string
	BRNP FALSE ;; check if string is exactly 14 characters long

	AND R2, R2, 0 ;; make R2 = 0

	LDR R1, R0, #0 ;; load first character into R1
	ADD R2, R2, #-16 ;; R2 = -16
	ADD R2, R2, #-16 ;; R2 = -32
	ADD R2, R2, #-8 ;; R2 = -40
	ADD R1, R1, R2 ;; check if character is "("
	BRNP FALSE
	
	LDR R1, R0, #4 ;; load fifth character into R1
	ADD R2, R2, #-1 ;; R2 = -41
	ADD R1, R1, R2 ;; check if character is ")"
	BRNP FALSE

	LDR R1, R0, #5 ;; load sixth character into R1
	ADD R2, R2, #9 ;; R2 = -32
	ADD R1, R1, R2 ;; check if character is " "
	BRNP FALSE

	LDR R1, R0, #9 ;; load 10th character into R1
	ADD R2, R2, #-13 ;; R2 = -45
	ADD R1, R1, R2 ;; check if character is "-"
	BRNP FALSE

	ADD R3, R2, #-3 ;; set R3 = -48
	ADD R4, R3, #-9 ;; set R4 = -57

	LDR R1, R0, #1 ;; load second character into R1
	ADD R2, R1, R3 ;; check less than '0'
	BRN FALSE ;; if less than '0', reject
	ADD R2, R1, R4 ;; check if greater than '9'
	BRP FALSE ;; if greater than '9', reject

	LDR R1, R0, #2 ;; load third character into R1
	ADD R2, R1, R3 ;; check less than '0'
	BRN FALSE ;; if less than '0', reject
	ADD R2, R1, R4 ;; check if greater than '9'
	BRP FALSE ;; if greater than '9', reject

	LDR R1, R0, #3 ;; load fourth character into R1
	ADD R2, R1, R3 ;; check less than '0'
	BRN FALSE ;; if less than '0', reject
	ADD R2, R1, R4 ;; check if greater than '9'
	BRP FALSE ;; if greater than '9', reject

	LDR R1, R0, #6 ;; load 7th character into R1
	ADD R2, R1, R3 ;; check less than '0'
	BRN FALSE ;; if less than '0', reject
	ADD R2, R1, R4 ;; check if greater than '9'
	BRP FALSE ;; if greater than '9', reject

	LDR R1, R0, #7 ;; load 8th character into R1
	ADD R2, R1, R3 ;; check less than '0'
	BRN FALSE ;; if less than '0', reject
	ADD R2, R1, R4 ;; check if greater than '9'
	BRP FALSE ;; if greater than '9', reject

	LDR R1, R0, #8 ;; load 9th character into R1
	ADD R2, R1, R3 ;; check less than '0'
	BRN FALSE ;; if less than '0', reject
	ADD R2, R1, R4 ;; check if greater than '9'
	BRP FALSE ;; if greater than '9', reject

	LDR R1, R0, #10 ;; load 11th character into R1
	ADD R2, R1, R3 ;; check less than '0'
	BRN FALSE ;; if less than '0', reject
	ADD R2, R1, R4 ;; check if greater than '9'
	BRP FALSE ;; if greater than '9', reject

	LDR R1, R0, #11 ;; load 12th character into R1
	ADD R2, R1, R3 ;; check less than '0'
	BRN FALSE ;; if less than '0', reject
	ADD R2, R1, R4 ;; check if greater than '9'
	BRP FALSE ;; if greater than '9', reject

	LDR R1, R0, #12 ;; load 13th character into R1
	ADD R2, R1, R3 ;; check less than '0'
	BRN FALSE ;; if less than '0', reject
	ADD R2, R1, R4 ;; check if greater than '9'
	BRP FALSE ;; if greater than '9', reject

	LDR R1, R0, #13 ;; load 14th character into R1
	ADD R2, R1, R3 ;; check less than '0'
	BRN FALSE ;; if less than '0', reject
	ADD R2, R1, R4 ;; check if greater than '9'
	BRP FALSE ;; if greater than '9', reject

;; if all tests passed
	AND R0, R0, 0 ;; load 0 into R0
	ADD R0, R0, #1 ;; add 1 to R0
	ST R0, ANSWER ;; store 1 in ANSWER
	HALT

	

FALSE
	AND R0, R0, 0 ;; load 0 into R0
	ST R0, ANSWER ;; store 0 in ANSWER
	HALT

STRING .fill x4000
ANSWER .blkw 1
.end

.orig x4000
.stringz "(704) 555-2110"
.end