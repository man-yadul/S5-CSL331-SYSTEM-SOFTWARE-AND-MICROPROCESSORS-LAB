; Yadul Manoj 69
; 8086 program to search a character in a string
; Both the string and character to be searched are entered as user input
; The string is a 10-character byte array named STR
; The character is searched byte-by-byte and a message is displayed whether the character is found or not

ASSUME CS: CODE, DS: DATA

DATA SEGMENT
    ENTSTR DB 13, 10, 'Enter string: $'
    ENTCHAR DB 13, 10, 'Enter character to search: $'
    FOUND DB 13, 10, 'Character found.$'
    NOTFOUND DB 13, 10, 'Character not found.$'
    STR DB 10 DUP(0)                                    ; Stores the string to search on
DATA ENDS

CODE SEGMENT
START:
    MOV AX, DATA                                        ; Initialize data segment
    MOV DS, AX

    LEA DX, ENTSTR                                      ; Print "Enter string: " on console
    MOV AH, 09H
    INT 21H

    MOV BX, 00H                                         ; Acts as an index when each character is stored in byte locations of STR
L1:                                                     ; User enters the whole string and the loop stores each character of the string in memory
    MOV AH, 01H                                         ; Get string
    INT 21H

    CMP AL, 0DH                                         ; Check for carriage return (if enter key is pressed)
    JE L2                                               ; Jump to L2 if enter is pressed
    MOV [STR + BX], AL                                  ; After user input, each character is stored in AL. This is stored in memory
    INC BX                                              ; Increment index to store the next character to next byte location
    JMP L1                                              ; Jump to L1
L2:
    LEA DX, ENTCHAR                                     ; Print "Enter character to search: " on console
    MOV AH, 09H
    INT 21H

    MOV AH, 01H                                         ; Enter the character to search. The character entered is stored in AL
    INT 21H

    MOV CX, BX                                          ; BX at this step contains the length of the string. Move it to CX as loop counter
    MOV DI, 0000H                                       ; Index for looping
L3:                                                     ; Loops through the string and compares character-by-character
    CMP AL, [STR + DI]                                  ; Compare character in AL to i'th character of string
    JE L4                                               ; If equal, character found
    INC DI                                              ; Increment index
    LOOP L3                                             ; Decrement CX and jump to L3
    
    LEA DX, NOTFOUND                                    ; Print "Character not found." on console
    MOV AH, 09H
    INT 21H
    JMP FINISH                                          ; Jump to return to DOS prompt
L4:
    LEA DX, FOUND                                       ; Print "Character found." on console
    MOV AH, 09H
    INT 21H
FINISH:
    MOV AH, 4CH                                         ; Return to DOS prompt
    INT 21H
CODE ENDS
END START
