#include "primitives.H"
#include "block.H"
#include "cylinder.H"
#include <iostream>
#include <string>

int main(){
    //block cube(point(0.0, 0.0, 0.0), 1.0);
    //block cube2(point(0.0, 1.0, 0.0), 1.0);
    //block box(point(1.0, 1.0, 0.0), 1.0, 4.0, 1.0);
    /*block trapezoid1
        (
            1.0,
            2.0,
            0.0,
            3.14 / 4,
            0.0,
            1
        );*/

    /*block trapezoid2
        (
            1.0,
            2.0,
            3.14 / 4,
            3.14 / 2,
            0.0,
            1
        );*/

    cylinder trapezoid1
        (
            1.0,
            2.0,
            3.14 / 4,
            3.14 / 2,
            0.0,
            1
        );

    //cube.nCell(20,20,10);
    //cube2.nCell(20,20,10);
    //box.nCell(20,80,10);
    trapezoid1.nCell(20,20,4);

    mesh M;

    //M.addElement(cube);
    //M.addElement(cube2);
    //M.addElement(box);
    M.addElement(trapezoid1);

    M.write();
    return 0;
}
