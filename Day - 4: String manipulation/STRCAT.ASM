; Yadul Manoj 69
; 8086 program to concatenate two strings
; Two strings TEXT1 and TEXT2 are reserved in memory
; The string concatenation is done by moving to the end of the first string
; Second string is attached character by character in the subsequent byte locations after TEXT1

ASSUME CS: CODE, DS: DATA

DATA SEGMENT
    TEXT1 DB "TEXT1$"
    TEXT2 DB "TEXT2$"
DATA ENDS

CODE SEGMENT
START:
    MOV AX, DATA    ; Initialize data segment
    MOV DS, AX

    LEA SI, TEXT1   ; Load effective address of TEXT1 to SI
    LEA DI, TEXT2   ; Load effective address of TEXT2 to DI
    MOV AL, '$'     ; Move $ to AL for comparison between each character
L1:                 ; Loop to reach the end of TEXT1
    CMP AL, [SI]    ; Check if current character is '$', i.e. if end of string has reached
    JZ L2           ; Jump to L2 if zero flag is set
    INC SI          ; Increment SI, i.e. move to next character
    JMP L1          ; Loop back to L1
L2:                 ; Loop to move each character of TEXT2 to locations after TEXT1
    CMP AL, [DI]    ; Check if current character is '$', i.e. if end of string has reached
    JZ EXIT         ; Jump to EXIT if zero flag is set
    MOV BL, [DI]    ; Move current character of TEXT2 to address stored in SI
    MOV [SI], BL
    INC SI          ; Increment SI, i.e. move to next location
    INC DI          ; Increment DI, i.e. move to next character
    JMP L2
EXIT:
    MOV [SI], AL    ; Move '$' to the location stored in SI (mark end to the newly concatenated string)

    LEA DX, TEXT1   ; Print string
    MOV AH, 9H
    INT 21H

    MOV AH, 4CH     ; Return to DOS prompt
    INT 21H
CODE ENDS
END START 