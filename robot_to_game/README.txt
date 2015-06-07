# CS550 Foundations of Computer Graphics
## Homework 1
### Loran Briggs

The following files have been submitted for the assignment

    Color.h         // header file for color class
    Color.cpp       // contains static color methods
    Robot.h         // header file for robot class
    Robot.cpp       // robot class, represents the robot object
    Thing.h         // header object for thing class
    Thing.cpp       // thing class, basic object with position and angle
    robotarm.h      // header file for robotarm appllication
    robotarm.cpp    // robotarm application, animates the robot on screen

These files have been created, compiled and tested on a **Ubuntu 14.10** computer
using the **g++ compiler** AND **Microsoft Visual Studio 10** on **Windows 7**.

Header guards are included to use the appropriate header files for either
Windows or Linux as you will see at the top of the
header files. If for some reason the header guard does not work for
your machine you can refer to the following website for the appropriate
naming convention for your OS.

http://sourceforge.net/p/predef/wiki/OperatingSystems/

If all else fails you can also comment out the sections labeled `linux headers`
in the two files mentioned above.

If you are compiling with g++ the following command will work:

    g++ *.cpp -o robotarm -lGL -lGLU -lglut

and to execute:

    ./robotarm

If you are using Visual Studio, copy the files into an empty project and
build and run using the gui menu options.
