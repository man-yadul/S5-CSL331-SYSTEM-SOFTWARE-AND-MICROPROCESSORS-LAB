; Yadul Manoj   69
; 8051 - Division using register indirect addressing mode
; The operands (8 bits) are at locations: A - 40H, B - 50H
; 40H contains operand 2BH, 50H contains operand 1AH
; B stores the remainder, A stores the quotient (2BH / 1AH = Q: 01H, R: 11H)

ORG 0H          ; Set PC to 0H
MOV R0, #40H    ; Move address 40H to R0 (40H contains operand 2BH)
MOV R1, #50H    ; Move address 50H to R1 (50H contains operand 1AH)
MOV A, @R0      ; Move operand located at address in R0 to A
MOV B, @R1      ; Move operand located at address in R1 to B
DIV AB          ; Divide A by B, remainder in B, quotient in A (B - 11H, A – 01H)
END
