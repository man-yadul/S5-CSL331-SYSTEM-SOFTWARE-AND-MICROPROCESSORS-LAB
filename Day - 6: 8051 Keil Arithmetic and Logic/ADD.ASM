; Yadul Manoj   69
; 8051 - Addition using immediate addressing mode
; The operands are 5H and 6H, result is in A (05H + 06H = 0BH)

ORG 0H      ; Set PC to 0H
MOV A, #5H  ; Move 5H to accumulator
ADD A, #6H  ; Add 6H to A, result is in A (0BH)
END
