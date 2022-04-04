; Yadul Manoj   69
; 8051 - Square wave generation

    ORG 0H		  
LABEL:
	SETB P2.1
    CALL DELAY
    CLR P2.1
    CALL DELAY
    SJMP LABEL
			
DELAY:
    MOV R0, #0FFH
LOOP:	
    DJNZ R0, LOOP
    RET
    END
