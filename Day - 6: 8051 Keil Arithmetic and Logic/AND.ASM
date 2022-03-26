; Yadul Manoj   69
; 8051 - AND using direct addressing mode
; The first operand (05H) is stored in A
; The second operand (06H) is at location 40H
; The result (04H) is stored in A (05H AND 06H = 04H)

ORG 0H		    ; Set PC to 0H
MOV A, #05H	    ; Move 05H to A
ANL A, 40H		; Perform A AND [40H] (05H AND 06H = 04H)
END
