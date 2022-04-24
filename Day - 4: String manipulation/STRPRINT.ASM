; Yadul Manoj 69
; 8086 program to display a string stored in memory

ASSUME CS: CODE, DS: DATA

DATA SEGMENT
    STRING DB 'Test string$'    ; Reserve string in memory
DATA ENDS

CODE SEGMENT
START:
    MOV AX, DATA                ; Initialize data segment
	MOV DS, AX

    LEA DX, STRING              ; Load effective address of STRING to DX

    MOV AH, 09H                 ; Call interrupt to print string
	INT 21H 

    MOV AH, 4CH                 ; Return to DOS prompt
	INT 21H
CODE ENDS
END START
