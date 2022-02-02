; Yadul Manoj 69
; 8086 program to subtract two 32-bit numbers (with borrow)
; The operands are 32 bit hex numbers NUM1 and NUM2
; Initially the lower 16-bits of both numbers are subtracted
; The result of this subtraction is stored in the lower 16-bits of RESULT
; Then the higher 16-bits of the numbers along with the carry from the previous subtraction is subtracted
; The result of this subtraction is stored in the higher 16-bits of RESULT
; The final result is stored in a double word reserved in the memory (RESULT)
; If a carry is generated during the subtraction of higher 16-bits, then 1st no. < 2nd no. 
; In such a case the final result is the 2's complement of the result
; The carry is stored in the next word succeeding to 2 words of RESULT and acts as a sign bit in the result
; CX stores carry during the subtraction of higher 16-bits
; DX stores the carry during the conversion to 2's complement of lower 16-bits of RESULT 

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
	MOV CX, 0000H                   ; Clear CX register
	MOV DX, 0000H					; Clear DX register

	MOV AX, WORD PTR NUM1           ; Move lower 16-bits (word) of NUM1 to AX register
	MOV BX, WORD PTR NUM2			; Move lower 16-bits (word) of NUM2 to BX register

	SUB AX, BX						; Subtract BX from AX			
	MOV WORD PTR RESULT, AX         ; Move 16-bit result in AX to lower 16-bits of RESULT

	MOV AX, WORD PTR NUM1 + 2       ; Move higher 16-bits (word) of NUM1 to AX register
	MOV BX, WORD PTR NUM2 + 2       ; Move higher 16-bits (word) of NUM2 to BX register

	SBB AX, BX                      ; Subtract BX from AX (with borrow from previous 16-bit subtraction)
	JNC NEXT                        ; Jump to NEXT if no carry is generated (i.e 1st no. > 2nd no.)
	INC CX                          ; Increment CX to store carry in final result
	CLC
	MOV BX, WORD PTR RESULT			; Take lower 16-bit result and find its 1's complement
	NOT BX							; Result in BX must be complemented to get actual magnitude
	ADD BX, 0001H					; Adding 1 to get two's complement
	JNC NOC							; If any carry is generated during this 2's complement conversion, it is stored in DX to be added with the next 16-bit 1's complement 
	INC DX							; Increment DX to add the carry generated during lower 16-bit 2's complement conversion
NOC:
	MOV WORD PTR RESULT, BX         ; Move 16-bit result in AX to lower 16-bits of RESULT
	NOT AX							; Result in AX must be complemented to get actual magnitude
	ADD AX, DX						; Add carry from previous 16-bit 2's complement conversion
NEXT:        
	MOV WORD PTR RESULT + 2, AX     ; Move 16-bit result in AX to higher 16-bits of RESULT
	MOV WORD PTR RESULT + 4, CX     ; Store carry (sign) in the word succeeding to 2 words of RESULT 
	
    MOV AH, 4CH             		; Return to DOS prompt
	INT 21H
CODE ENDS
END START
