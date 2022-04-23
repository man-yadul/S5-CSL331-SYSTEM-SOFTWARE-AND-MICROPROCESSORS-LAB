; Yadul Manoj 69
; 8086 program to add two 16-bit numbers (with carry)
; The numbers to be added are stored in AX and BX registers
; CX is used to store carry before result is stored in memory
; The final result is stored in a word reserved in the memory (RESULT)
; If a carry is generated, it is stored in the next word succeeding to RESULT
; CF being set signifies a carry 

ASSUME CS: CODE, DS: DATA

DATA SEGMENT
	NUM1 DW 0EC54H			    ; First operand
	NUM2 DW 5678H			    ; Second operand
	RESULT DW 01 DUP(?)		    ; Word of memory reserved for result
DATA ENDS

CODE SEGMENT
START:
	MOV AX, DATA            	; Initialize data segment
	MOV DS, AX
	MOV AX, NUM1            	; Move NUM1 to AX register
	MOV BX, NUM2            	; Move NUM2 to BX register
	CLC                     	; Clear carry flag
	XOR CX, CX              	; Clear CX register
	ADD AX, BX              	; Add the operands, result is stored in AX
	JNC NEXT                	; Jump to NEXT if no carry is generated
	INC CX                  	; Carry is generated and CX is incremented to signify a carry to store it in result
NEXT:
	MOV DI, OFFSET RESULT   	; Move offset of RESULT to DI
	MOV [DI], AX            	; Store result at memory address in DI
	INC DI                  	; DI before this instruction points to the offset of RESULT. A word beginning from this location is already occupied for 16-bit result
	INC DI                  	; In order to store the carry at the next word, INC is done twice since it only increments by a byte 
	MOV [DI], CX            	; Store carry
	
	; Printing starts here
	MOV AH, 02H			        ; Used for print interrupt call
	MOV CX, 03H			        ; Stores the no. of bytes to be printed. eg:- CX here is 3 because two bytes for result and 1 byte for carry
	MOV BX, OFFSET RESULT + 2	; Move the last byte of result to be printed first. eg:- If result is 0142CC, move byte 01
PRINT:
	MOV DL, [BX]
	AND DL, 0F0H			    ; AND with F0 to isolate first hex digit of the byte. eg:- 42 AND F0 = 40
	SHR DL, 01H			        ; Shift right the digit 4 times to move it to lower 4 bits of a byte. eg:- Change 40 to 04
	SHR DL, 01H
	SHR DL, 01H
	SHR DL, 01H
	CMP DL, 0AH                 ; Check if digit is between 0 - 9
	JL L1
	ADD DL, 37H			        ; Add ASCII for printing characters A - F
	JMP L2
L1:
	ADD DL, 30H			        ; Add ASCII for printing numbers 0 - 9
L2:
	INT 21H				        ; Print
	MOV DL, [BX]			    ; Print section of lower hex digit of the byte starts here
	AND DL, 0FH			        ; AND with 0F to isolate the lower hex digit. eg:- 42 AND 0F = 02
	CMP DL, 0AH			        ; Check if digit is between 0 - 9
	JL L3
	ADD DL, 37H			        ; Add ASCII for printing characters A - F
	JMP L4
L3:
	ADD DL, 30H			        ; Add ASCII for printing numbers 0 - 9
L4:
	INT 21H				        ; Print
	DEC BX				        ; Move to next byte
	LOOP PRINT			        ; Loop until CX is 0
	
	MOV AH, 4CH			        ; Return to DOS prompt
	INT 21H
CODE ENDS
END START
