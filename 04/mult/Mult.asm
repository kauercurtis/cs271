// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Name: Curtis Kauer
// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
//
// This program only needs to handle arguments that satisfy
// R0 >= 0, R1 >= 0, and R0*R1 < 32768.

    //n = 0
    @n
    M=0

    //counter=0
    @counter
    M=0

    //set RAM2 to 0
    @R2
    M=0

(LOOP)
    //if R0 == 0 OR R1 == 0 Go to End
    @n
    D=M
    @R0
    D=D-M
    @END
    D;JEQ

    @n
    D=M
    @R1
    D=D-M
    @END
    D;JEQ

    //if counter == R1 go to END
    @counter
    D=M
    @R1
    D=D-M
    @END
    D;JEQ

    //else add value at RAM0 to RAM2
    @R0
    D=M
    
    @R2
    M=D+M

    //increment counter
    @counter
    D=M
    M=D+1

    //Loop
    @LOOP
    0;JMP
(END)
    @END
    0;JMP