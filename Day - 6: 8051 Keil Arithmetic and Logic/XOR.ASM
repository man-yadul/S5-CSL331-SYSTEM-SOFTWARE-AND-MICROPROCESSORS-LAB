; Yadul Manoj   69
; 8051 - XOR using register indirect addressing mode
; The first operand (05H) is stored in A
; The address of the second operand (06H) is 40H, stored in R0
; The result (03H) is stored in A (05H XOR 06H = 03H)

ORG 0H		    ; Set PC to 0H
MOV R0, #40H    ; Move address 40H to R0
MOV A, #05H	    ; Move 05H to A
XRL A, @R0		; Perform A XOR [R0] (05H XOR 06H = 03H)
END
