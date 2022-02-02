; Yadul Manoj 69
; 8086 program to perform NOT operation on an operand
; The operand is directly given to AX

ASSUME CS: CODE

CODE SEGMENT
START:
	MOV AX, 1234H   ; Move value 1234H to AX
	NOT AX          ; Perform NOT operation on value in AX
	
	MOV AH, 4CH     ; Return to DOS prompt
	INT 21H
CODE ENDS
END START
