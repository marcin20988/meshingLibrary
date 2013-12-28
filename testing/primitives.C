#include "primitives.H"
#include "block.H"
#include <iostream>
#include <string>
#include <math.h>
#include "pipes.H"

int main(){
    /*pipe::oType pipe1
        (
            1.0,
            1.0,
            0.5
        );*/

/*    pipe::ring pipe1
        (
            1.0, // length,
            0.2, // innerRadious,
            0.3, // outerRadious,
            0.0, //double initialZ = 0.0,
            4, //int numberOfSegments = 4,
            0 //double deltaAlpha = 0,
            //std::string name = "ring"
        );*/
    pipe::restrictedPipe pipe1
        (
            3.0,
            0.1,
            0.6,
            0.4,
            0.2
        );


    /*pipe::oType pipe2
        (
            0.3,
            2.0,
            0.1,
            0.1,
            0.11
        );*/

    /*pipe::ring pipe1
        (
          0.0, //double initialZ,
          1.0, //double length,
          0.2, //double innerRadious,
          0.3,//double outerRadious,
          4,//20//int numberOfSegments = 4,
          1//double deltaAlpha = 0,
          //std::string name = "ring"

        );*/
    pipe1.nCell(25,24,100);

    mesh M;
    M.addElement(pipe1);

    M.write();


    std::cout << pipe1.write();
    return 0;
}
