; Yadul Manoj 69
; 8086 program to multiply two 16-bit numbers
; The operands are two words NUM1 and NUM2 reserved in the memory
; The final result is stored in a double-word reserved in the memory (RESULT)

ASSUME CS: CODE, DS: DATA

DATA SEGMENT
    NUM1 DW 0FFFFH		; First operand
    NUM2 DW 0AAAAH		; Second operand
    RESULT DD ?			; Double word of memory reserved for result
DATA ENDS

CODE SEGMENT
START:
	MOV AX, DATA		; Initialize data segment
	MOV DS, AX

	MOV AX, NUM1		; Move NUM1 to AX register
	MUL NUM2            ; Multiply value in AX to NUM2 (lower 16 bits of result is stored in AX and remaining 16 bits in DX)

	LEA BX, RESULT      ; Load effective address of RESULT to BX
	MOV [BX], AX        ; Move first 16-bits of result in AX to address stored in BX
	MOV [BX + 2], DX    ; Remaining 16-bits of result is stored in DX. This is moved to a word succeding to the word RESULT

	MOV AH, 4CH         ; Return to DOS prompt
	INT 21H
CODE ENDS
END START