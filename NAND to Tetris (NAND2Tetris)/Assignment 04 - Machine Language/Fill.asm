// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, 
// the screen should be cleared.

//while (true){
// int i = SCREEN;
// int size = SCREEN + 8192;
// while (i < size){
//  if(keypressed)
//       Color[i] = black
//  else 
//       Color[i] = white
//  i++;
// }
//}

(START)
    @8192
    D=A
    @SCREEN
    D=D+A
    @size
    M = D // size = 512/16 * 256 + SCREEN
    @SCREEN
    D=A
    @i
    M = D // i = SCREEN

(LOOP)
    @i
    D=M // D=i
    @size
    D=D-M // D=i-size
    @END
    D;JGE // If (i-size)>=0 goto END
    
    @KBD
    D=M
    @KEY_NOT_PRESSED
    D;JEQ // If Key not pressed goto INC

(KEY_PRESSED)
    @i
    A=M
    M=-1 // Color pixel black
    @INC
    0;JMP

(KEY_NOT_PRESSED)
    @i
    A=M
    M=0 //Color pixel white

(INC)
    @i
    M=M+1 // i=i+1
    @LOOP
    0;JMP // Goto LOOP

(END)
    @START
    0;JMP