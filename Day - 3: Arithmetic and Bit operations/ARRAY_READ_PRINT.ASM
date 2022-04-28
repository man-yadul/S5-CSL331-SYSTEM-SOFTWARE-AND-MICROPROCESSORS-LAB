; Yadul Manoj 69
; 8086 program to read and display an array of digits
; The digits to be entered are single digit numbers
; The size of the array is entered before receiving the digits

ASSUME CS: CODE, DS: DATA

DATA SEGMENT
    ARRAY DB 10H DUP(?)
    ARRSIZE DB ?

    STR1 DB 13, 10, 'ENTER SIZE OF ARRAY: $'
    STR2 DB 13, 10, 'ENTER NUMBER: $'
DATA ENDS

CODE SEGMENT
START:
    MOV AX, DATA
    MOV DS, AX

    ; Clear registers
    XOR AX, AX
    MOV DX, AX

    ; Print "ENTER SIZE OF ARRAY: "
    LEA DX, STR1
    MOV AH, 09H
    INT 21H
    
    XOR AX, AX

    ; Read array size. ASCII of entered digit is stored in AL
    MOV AH, 01H
    INT 21H
    ; 30H (ASCII of zero) is subtracted to get the actual value of digit
    SUB AL, 30H
    MOV ARRSIZE, AL

    ; Entering the and storing the array elements

    ; CX is loop counter
    ; SI is for indexing the array
    MOV CX, 0000H
    MOV SI, 0000H
L1:
    CMP CL, ARRSIZE
    JE L2

    XOR AX, AX

    ; Print "ENTER NUMBER: "
    LEA DX, STR2
    MOV AH, 09H
    INT 21H

    MOV AH, 01H
    INT 21H
    SUB AL, 30H
    MOV [OFFSET ARRAY + SI], AL
    ; MOV [ARRAY + SI], AL also works instead of the above instruction

    INC CX
    INC SI
    JMP L1

    ; Printing the array

L2:
    ; CX is loop counter
    ; SI is for indexing the array
    MOV CX, 0000H
    MOV SI, CX
L3:
    CMP CL, ARRSIZE
    JE L4

    XOR AX, AX

    ; Print new line
    MOV DL, 0AH
    MOV AH, 02H
    INT 21H

    MOV DL, [OFFSET ARRAY + SI]
    ; MOV DL, [ARRAY + SI] also works instead of the above instruction

    ; Add 30H to get ASCII value of digit
    ADD DL, 30H
    MOV AH, 02H
    INT 21H

    INC CX
    INC SI
    JMP L3

L4:
    MOV AH, 4CH
    INT 21H
CODE ENDS
END START            
