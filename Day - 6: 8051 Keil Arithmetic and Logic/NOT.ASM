; Yadul Manoj   69
; 8051 - NOT using immediate addressing mode
; The operand (1AH) and result (E5H) are stored in A (NOT(1AH) = E5H)

ORG 0H		; Set PC to 0H
MOV A, #1AH	; Move 1AH to A
CPL A		; Perform 1's complement (NOT) on A (NOT(1AH) = E5H)
END
