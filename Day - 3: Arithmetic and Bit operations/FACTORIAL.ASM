; Yadul Manoj 69
; Factorial of a number with user input
; The program can handle factorials which can be represented by upto 2 bytes (upto 8!) 

ASSUME CS: CODE, DS: DATA

DATA SEGMENT
    NUM DB ?
    FACT DW ?

    STR1 DB 'ENTER NUMBER: $'
    STR2 DB 'FACTORIAL: $'
DATA ENDS

CODE SEGMENT
START:
    MOV AX, DATA
    MOV DS, AX

    ; Print "ENTER NUMBER: "
    MOV DX, OFFSET STR1
    MOV AH, 09H
    INT 21H

    ; Read number. The ASCII value of the entered digit will be stored in AL
    MOV AH, 01H
    INT 21H

    ; Subtract ASCII of zero to get the actual digit
    SUB AL, 30H

    ; Move value to NUM
    MOV NUM, AL

    ; Print new line
    MOV DL, 0AH
    MOV AH, 02H
    INT 21H

    ; Factorial computation starts here
    ; AX and BX initially stores the original number.
    ; AX stores the result of the factorial computation
    ; BX is successively decremented and multiplied with the value in AX to find the factorial
    ; Computation stops when BX reaches 0

    XOR AX, AX
    XOR BX, BX
    MOV AL, NUM
    MOV BL, NUM

FACTLOOP:
    DEC BX
    CMP BX, 0H
    JE FINISH
    MUL BX
    JMP FACTLOOP

    ; Storage of result and printing starts here
FINISH:
    ; Store result of factorial to location FACT
    MOV FACT, AX

    ; Print "FACTORIAL: "
    MOV DX, OFFSET STR2
    MOV AH, 09H
    INT 21H

    ; Print operation of the most significant byte of FACT starts here

    ; For shifting bits in SHR operation
    MOV CL, 04H

    MOV SI, OFFSET FACT + 1
    MOV DL, [SI]
    AND DL, 0F0H
    SHR DL, CL
    CMP DL, 0AH
    JL L1
    ADD DL, 37H
    JMP L2
L1:
    ADD DL, 30H
L2:
    MOV AH, 02H
    INT 21H

    MOV SI, OFFSET FACT + 1
    MOV DL, [SI]
    AND DL, 0FH
    CMP DL, 0AH
    JL L3
    ADD DL, 37H
    JMP L4
L3:
    ADD DL, 30H
L4:
    MOV AH, 02H
    INT 21H

    ; Print operation of the least significant byte of FACT starts here

    MOV CL, 04H

    MOV SI, OFFSET FACT
    MOV DL, [SI]
    AND DL, 0F0H
    SHR DL, CL
    CMP DL, 0AH
    JL L5
    ADD DL, 37H
    JMP L6
L5:
    ADD DL, 30H
L6:
    MOV AH, 02H
    INT 21H

    MOV SI, OFFSET FACT
    MOV DL, [SI]
    AND DL, 0FH
    CMP DL, 0AH
    JL L7
    ADD DL, 37H
    JMP L8
L7:
    ADD DL, 30H
L8:
    MOV AH, 02H
    INT 21H

    MOV AH, 4CH
    INT 21H
CODE ENDS
END START
