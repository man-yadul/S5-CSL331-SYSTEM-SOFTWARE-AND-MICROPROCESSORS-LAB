; Yadul Manoj   69
; String palindrome with user input

ASSUME CS: CODE, DS: DATA

DATA SEGMENT
    STR DB 15H DUP(?)
    MSG1 DB 'ENTER STRING: $'
    MSG2 DB 'ENTERED STRING IS: $'
    MSG3 DB 'PALINDROME$'
    MSG4 DB 'NOT PALINDROME$'
DATA ENDS

CODE SEGMENT
START:
    MOV AX, DATA
    MOV DS, AX

    ; Print "ENTER STRING: "
    MOV DX, OFFSET MSG1
    MOV AH, 09H
    INT 21H

    ; Read string
    MOV SI, 0000H
L1:
    MOV AH, 01H
    INT 21H

    ; Check if enter key is pressed
    CMP AL, 0DH
    JE L2

    MOV [STR + SI], AL
    INC SI
    JMP L1

L2:
    ; Attach '$' at end of string to mark its end
    MOV [STR + SI], '$'

    ; Print "ENTERED STRING IS: ......."
    MOV DX, OFFSET MSG2
    MOV AH, 09H
    INT 21H
    MOV DX, OFFSET STR
    MOV AH, 09H
    INT 21H

    ; Palindrome checking starts here
    ; DI is used for indexing from beginning of the string to end
    ; SI is used for indexing from end of the string to beginning (SI at this point holds the length of the string including '$')
    ; AL and BL stores the characters pointed by DI and SI
    ; Loop ends when value in DI > SI

    MOV DI, 0000H
    ; SI is decremented to point to the last letter of string
    DEC SI
L3:
    CMP DI, SI
    JG L4

    MOV AL, [STR + DI]
    MOV BL, [STR + SI]

    CMP AL, BL
    JNE L5

    INC DI
    DEC SI
    JMP L3

L4:
    ; Print "PALINDOME"
    MOV DL, 0AH
    MOV AH, 02H
    INT 21H
    MOV DX, OFFSET MSG3
    MOV AH, 09H
    INT 21H
    JMP L6

L5:
    ; Print "NOT PALINDROME"
    MOV DL, 0AH
    MOV AH, 02H
    INT 21H
    MOV DX, OFFSET MSG4
    MOV AH, 09H
    INT 21H

L6:
    MOV AH, 4CH
    INT 21H
CODE ENDS
END START
