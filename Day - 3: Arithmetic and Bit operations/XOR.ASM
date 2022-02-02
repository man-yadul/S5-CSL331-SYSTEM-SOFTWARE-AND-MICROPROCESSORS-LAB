; Yadul Manoj 69
; 8086 program to perform XOR operation on two operands
; The operands are directly given to the registers

ASSUME CS: CODE

CODE SEGMENT
START:
	MOV AX, 1234H   ; Move value 1234H to AX
	MOV BX, 5678H   ; Move value 5678H to BX
	XOR AX, BX      ; Perform XOR operation with values in AX and BX
	
	MOV AH, 4CH     ; Return to DOS prompt
	INT 21H
CODE ENDS
END START
