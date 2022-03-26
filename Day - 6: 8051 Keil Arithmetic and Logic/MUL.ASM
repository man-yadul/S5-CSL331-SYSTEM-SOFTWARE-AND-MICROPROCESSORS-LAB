; Yadul Manoj   69
; 8051 - Multiplication using direct addressing mode
; The operands (8 bits) are at locations: A - 40H, B - 50H
; 40H contains operand 1AH, 50H contains operand 2BH
; The result of the operation is 16 bits in length (1AH X 2BH = 045EH)
; B register stores the higher byte, A register stores the lower byte

ORG 0H      ; Set PC to 0H
MOV A, 40H  ; Move contents of 40H to A (40H contains operand 1AH)
MOV B, 50H  ; Move contents of 50H to B (50H contains operand 2BH)
MUL AB      ; Multiply B to A, result's higher byte in B, lower in A (B - 04H, A – 5EH)
END
