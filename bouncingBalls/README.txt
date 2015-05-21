# CS550 Foundations of Computer Graphics
## Homework 1
### Loran Briggs

The following files have been submitted for the assignment

    bouncing.h    // header file containing global variables
    bouncing.cpp  // main class containing key listeners and drawing functions
    Ball.h        // header file for Ball class
    Ball.cpp      // implements methods for Ball class

These files have been created, compiled and tested on a Ubuntu 14.10 computer
using the g++ compiler.

Header guards are included to use the appropriate header files for either
Windows or Linux as you will see at the top of the `Ball.h` and
`bouncing.h` files. If for some reason the header guard does not work for
your machine you can refer to the following website for the appropriate
naming convention for your OS.

http://sourceforge.net/p/predef/wiki/OperatingSystems/

If all else fails you can also comment out the sections labeled `linux headers`
in the two files mentioned above.

If you are compiling with g++ the following command will work:

    g++ *.cpp -o bouncing -lGL -lGLU -lglut

and to execute:

    ./bouncing
