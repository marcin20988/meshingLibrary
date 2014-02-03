#include <iostream>
#include <string>
#include <math.h>
#include "meshing.H"

using namespace meshing;

int main(){

    //pipe radius
    double R = 0.063 / 2.0;
    //pipe length
    double L = 4.5;
    //particle injection ring inner radius
    double injectionR = 0.778 * R;

    //number of cells in z direction
    int nZ = 200;
    //in theta direction
    int nTheta = 36;
    //in r direction for central seciton
    int nR1 = 12;
    //in r direction for ring seciton
    int nR2 = 5;

    pipe::oType centralSection
        (
            L,
            injectionR,
            0.0,
            0.4,
            0.44
        );

    pipe::ring ringSection
        (
            L,
            injectionR,
            R,
            0.0,
            4,
            M_PI / 4.0
        );

    centralSection.nCell(nR1, nTheta, nZ);
    ringSection.nCell(nR2, nTheta , nZ);

    mesh M;
    M.addElement(centralSection);
    M.addElement(ringSection);

    M.addPatch(r, R, "walls", w);
    M.addPatch(z, L, "outlet", p);
    M.addPatch(z, 0.0, "oilInlet", p);
    M.separateFromPatch("oilInlet",r, injectionR, R, "waterInlet", p);

    M.write();
}
