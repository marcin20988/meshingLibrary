#include <iostream>
#include <string>
#include <math.h>
#include "meshing.H"

using namespace meshing;

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
    /*pipe::restrictedPipe pipe1
        (
            3.0,
            0.1,
            0.6,
            0.4,
            0.2
        );
*/

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
 //   pipe1.nCell(25,24,10,20,100);

    std::cout << asin(1) << std::endl;
    std::cout << sin(asin(1)) << std::endl;

    cylinder cylinder1
        (
            2.0,
            3.0,
            0,
            1,
            0,
            1
        );

    /*block block1
        (
            point(3.0,3.0,0.0),
            1.0
        );*/

    expandingCylinder expPipe
        (
          point(0.0,0.0,0.0),
          1.0,//double a1, //cube x-width
          1.1,//double r1, //rounding radius
          2.0,//double a2, //cube x-width
          2.2,//double r2, //rounding radius
          3.0//double c, //cube z-width
        );
    //expPipe.nCell(10,20,5);
    
    pipe::oTypeExpanding expanding
        (
            1.0,
            0.5,
            1.75,
            0.0,
            0.2,
            0.22
        );
    expanding.nCell(10,20,5);

    mesh M;
    M.addElement(expanding);
    //M.addElement(expPipe);
    //M.addElement(block1);
    //M.addElement(cylinder1);

//    M.addPatch(x,0.0,"wall1");
//    M.addToPatch(x,1.0,"wall1");

//    M.addPatch(y,0.0,"wall2",w);
//    M.addToPatch(y,2.0,"wall2");
    
    //constant::tolerance = 1e-03;
    //M.addPatch(r,3.0,"roundWall1",w);
    //M.addPatch(theta,0,"roundWall2",w);
   // M.addElement(pipe1);

    M.write();


    return 0;
}
