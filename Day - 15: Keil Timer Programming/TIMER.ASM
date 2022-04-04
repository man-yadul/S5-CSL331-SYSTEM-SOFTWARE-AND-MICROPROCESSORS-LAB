; Yadul Manoj   69
; 8051 - Square wave with 20ms delay using Timer 1 in Mode 1  
    
    ORG 0H
LABEL:
    SETB P1.3
    CALL DELAY
    CLR P1.3
    CALL DELAY
    SJMP LABEL

DELAY:
    MOV TMOD, #10H
    MOV TH1, #0B1H
    MOV TL1, #0E0H
    SETB TR1
LOOP:
    JNB TF1, LOOP
    CLR TR1
    CLR TF1
    RET
    END 