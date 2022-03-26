; Yadul Manoj   69
; 8051 - Subtraction using register addressing mode
; The operands are stored in A (6H) and R0 (5H), result is in A (06H - 05H = 01H)

ORG 0H      ; Set PC to 0H
MOV A, #6H  ; Move 6H to accumulator
MOV R0, #5H ; Move 5H to R0
SUBB A, R0  ; Subtract R0 from A, result is in A (01H)
END
