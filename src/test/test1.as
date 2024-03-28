.entry LENGTH 
.extern W
; some commant 
; some commant
; a commant
MAIN: mov r3 ,LENGTH
LOOP: jmp L1(#-1,r6) 
 prn #-5 
 bne W(r4,r5) 
; some other comment 
sub r1, r4
 bne L3 
L1: inc K 
.entry LOOP 
bne LOOP(K,W)
END: stop 
STR: .string "abcdef" 
LENGTH: .data 6,-9,15 
K: .data 22
.extern L3
