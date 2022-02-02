; Yadul Manoj 69
; 8086 program to add two 16-bit numbers (with carry)
; The numbers to be added are stored in AX and BX registers
; CX is used to store carry before result is stored in memory
; The final result is stored in a word reserved in the memory (RESULT)
; If a carry is generated, it is stored in the next word succeeding to RESULT
; CF being set signifies a carry 

ASSUME CS: CODE, DS: DATA

DATA SEGMENT
	NUM1 DW 0EC54H			; First operand
	NUM2 DW 5678H			; Second operand
	RESULT DW 01 DUP(?)		; Word of memory reserved for result
DATA ENDS

CODE SEGMENT
START:
	MOV AX, DATA            ; Initialize data segment
	MOV DS, AX

	MOV AX, NUM1            ; Move NUM1 to AX register
	MOV BX, NUM2            ; Move NUM2 to BX register

	CLC                     ; Clear carry flag
	XOR CX, CX              ; Clear CX register

	ADD AX, BX              ; Add the operands, result is stored in AX
	JNC NEXT                ; Jump to NEXT if no carry is generated
	INC CX                  ; Carry is generated and CX is incremented to signify a carry to store it in result
NEXT:
	MOV DI, OFFSET RESULT   ; Move offset of RESULT to DI
	MOV [DI], AX            ; Store result at memory address in DI
	INC DI                  ; DI before this instruction points to the offset of RESULT. A word beginning from this location is already occupied for 16-bit result
	INC DI                  ; In order to store the carry at the next word, INC is done twice since it only increments by a byte 
	MOV [DI], CX            ; Store carry
	
	MOV AH, 4CH             ; Return to DOS prompt
	INT 21H
CODE ENDS
END START
