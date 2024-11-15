// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
// The algorithm is based on repetitive addition.

//int i = 1;
//int R2 = 0;
//while (i <= R1){
// R2 += R0;
// i++;
//}


(START)
    @i // i refers to some mem. location.
    M=1 // i=1
    @R2
    M=0 // R2=0
(LOOP)
    @i
    D=M // D=i
    @R1
    A=M
    D=D-A // D=i-R1
    @END
    D;JGT // If (i-R1)>0 goto END
    @R0
    D=M // D=R0
    @R2
    M=D+M // R2=R2+R0
    @i
    M=M+1 // i=i+1
    @LOOP
    0;JMP // Goto LOOP
(END)
    @END
    0;JMP // Infinite loop