#include <iostream>
#include <string>
#include <math.h>
#include "meshing.H"

using namespace meshing;

int main(){

    //pipe radius
    double R = 0.038 / 2.0;
    //pipe length
    double L = 3.2;

    //number of cells in z direction
    int nZ = 250;
    double zGrad = 1;

    //in theta direction
    int nTheta = 36;
    //in r direction for central seciton
    int nR = 16;

    pipe::oType element
        (
            L,
            R,
            0.0,
            0.25,
            0.27
        );

    element.nCell(nR, nTheta, nZ);

    element.nGrading(1.0, 1.0, zGrad);

    mesh M;
    M.addElement(element);

    M.addPatch(r, R, "walls", w);
    M.addPatch(z, L, "outlet", p);
    M.addPatch(z, 0.0, "inlet", p);

    M.write();
}
