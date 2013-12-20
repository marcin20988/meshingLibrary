#include "primitives.H"
#include "block.H"
#include <iostream>
#include <string>
#include <math.h>
#include "pipes.H"

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

/*    const int n = 4;
    cylinder **list;
    list = new cylinder*[n];

    for(int i=0; i<n; i++){
        float alpha1 = (i+1) * n / 2.0 * M_PI / n;
        float alpha2 = (i+2) * n / 2.0 * M_PI / n;
        list[i] = new cylinder
            (
                0.5,
                1.0,
                alpha1,
                alpha2,
                0.0,
                10.0,
                twoSided,
                0.5*0.75
            );
        (*list[i]).nCell(10,10,4);
    }*/

    //cube.nCell(20,20,10);
    //cube2.nCell(20,20,10);
    //box.nCell(20,80,10);
    
/*    cylinder roundedSquare = cylinder
        (
            point(0,0,0),
            1.0,
            10.0,
            1.1
        );*/

    //roundedSquare.nCell(10,10,5);
    //
    //

    pipe::oType pipe1
        (
            10.0,
            1.0,
            0.1,
            0.11
        );

    pipe1.nCell(10,10,4);

    mesh M;
    M.addElement(pipe1);
    //M.addElement(roundedSquare);
    //for(int i=0; i<n; i++) M.addElement( *list[i] );

    //M.addElement(cube);
    //M.addElement(cube2);
    //M.addElement(box);
    //M.addElement(trapezoid1);

    M.write();


    std::cout << pipe1.write();
    return 0;
}
