; Yadul Manoj 69
; 8086 program to subtract two 32-bit numbers (with borrow)
; The operands are 32 bit hex numbers NUM1 and NUM2
; The final result is stored in a double word reserved in the memory (RESULT)

ASSUME CS: CODE, DS: DATA

DATA SEGMENT
	NUM1 DD 98975423H				; First operand
	NUM2 DD 8234B758H				; Second operand
	RESULT DD ?						; Double word of memory reserved for result
DATA ENDS

CODE SEGMENT
START:
	MOV AX, DATA            		; Initialize data segment
	MOV DS, AX
	CLC                             ; Clear carry flag
	MOV AX, WORD PTR NUM1           ; Move lower 16-bits (word) of NUM1 to AX register
	MOV BX, WORD PTR NUM2			; Move higher 16-bits of NUM1 to BX register
	SUB AX, BX						; Subtract BX from AX			
	MOV WORD PTR RESULT, AX         ; Move 16-bit result in AX to lower 16-bits of RESULT
	MOV AX, WORD PTR NUM1 + 2       ; Move lower 16-bits (word) of NUM2 to AX register
	MOV BX, WORD PTR NUM2 + 2       ; Move higher 16-bits (word) of NUM2 to BX register
	SBB AX, BX                      ; Subtract BX from AX (with borrow from previous subtraction)
	MOV WORD PTR RESULT + 2, AX     ; Move 16-bit result in AX to higher 16-bits of RESULT
	MOV WORD PTR RESULT + 4, CX     ; Store carry in the word succeeding to 2 words of RESULT 
	MOV AH, 4CH             		; Return to DOS prompt
	INT 21H
CODE ENDS
END START
