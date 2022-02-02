; Yadul Manoj 69
; 8086 program to add two 32-bit numbers (with carry)
; The operands are 32 bit hex numbers NUM1 and NUM2
; The final result is stored in a double word reserved in the memory (RESULT)
; Initially the lower 16-bits of both numbers are added
; The result of this addition is stored in the lower 16-bits of RESULT
; Then the higher 16-bits of the numbers along with the carry from the previous addition is added
; The result of this addition is stored in the higher 16-bits of RESULT
; If a carry is generated, it is stored in the next word succeeding to 2 words of RESULT

ASSUME CS: CODE, DS: DATA

DATA SEGMENT
	NUM1 DD 98975423H				; First operand
	NUM2 DD 8234B758H				; Second operand
	RESULT DD ?						; Double word of memory reserved for result
DATA ENDS

CODE SEGMENT
START:
	MOV AX, DATA                    ; Initialize data segment
	MOV DS, AX

	CLC                             ; Clear carry flag
	MOV CX, 0000H                   ; Clear CX register

	MOV AX, WORD PTR NUM1           ; Move lower 16-bits (word) of NUM1 to AX register
	MOV BX, WORD PTR NUM2           ; Move lower 16-bits (word) of NUM2 to BX register

	ADD AX, BX                      ; Add AX and BX
	MOV WORD PTR RESULT, AX         ; Move 16-bit result in AX to lower 16-bits of RESULT
	
	MOV AX, WORD PTR NUM1 + 2       ; Move higher 16-bits (word) of NUM1 to AX register
	MOV BX, WORD PTR NUM2 + 2       ; Move higher 16-bits (word) of NUM2 to BX register

	ADC AX, BX                      ; Add AX and BX (with carry from previous addition)
	JNC NEXT                        ; Jump to NEXT if no carry is generated
	INC CX                          ; Increment CX to store carry in final result
NEXT:        
	MOV WORD PTR RESULT + 2, AX     ; Move 16-bit result in AX to higher 16-bits of RESULT
	MOV WORD PTR RESULT + 4, CX     ; Store carry in the word succeeding to 2 words of RESULT 
	
	MOV AH, 4CH                     ; Return to DOS prompt
	INT 21H
CODE ENDS
END START
