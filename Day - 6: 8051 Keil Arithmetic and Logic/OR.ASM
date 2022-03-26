; Yadul Manoj   69
; 8051 - OR using register addressing mode
; The operands are stored in A (6H) and R0 (5H), result is in A (06H OR 05H = 07H)

ORG 0H		    ; Set PC to 0H
MOV R0, #05H    ; Move 05H to R0
MOV A, #06H	    ; Move 06H to A
ORL A, R0		; Perform A OR R0 (06H OR 05H = 07H)
END
