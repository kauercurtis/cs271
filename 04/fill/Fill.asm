// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Name: Curtis Kauer
// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.  

// resets pixel variable to 16384
(REPIXEL)
    @16384
    D=A
    @pixel
    M=D
    
    //if keyboard > 0, jump to BLACK
    @KBD
    D=M
    @BLACK
    D;JGT

//WHITE - fills screen with white
(WHITE)
    @pixel
    D=M
    @SCREEN
    A=D
    M=0

    //if pixel - 24575 == 0, reset pixel, jump to REPIXEL
    @24575
    D=A
    @pixel
    D=D-M
    @REPIXEL
    D;JEQ

    //else increment pixel, jump to WHITE
    @pixel
    M=M+1
    @WHITE
    0;JMP

// BLACK - fills screen with black
(BLACK)
    @pixel
    D=M
    @SCREEN
    A=D
    M=-1

    //if pixel - 24575 == 0, reset pixel, jump to REPIXEL
    @24575
    D=A
    @pixel
    D=D-M
    @REPIXEL
    D;JEQ

    //else increment pixel, jump to BLACK
    @pixel
    M=M+1
    @BLACK
    0;JMP

