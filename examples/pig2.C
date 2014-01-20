#include <iostream>
#include <string>
#include <math.h>
#include "meshing.H"

using namespace meshing;

int main(){

    //pipe radius
    double R = 1.0;
    double restrictionRadius = 0.1;
    //radius of the expanding section
    double r0 = 0.4;
    //restriction location
    double l1 = 1.0;
    //restriction length
    double l2 = 0.1;
    //length of expanding section
    double l3 = 0.3;
    //length of the pipe succeeding expanding section
    double l4 = 1.0;

    double initialZ = 0.0;

    //inner suare size
    double innerA = 0.4;
    //inner square radius of oTypes
    double innerR = 0.44;

    //number of cells:
    //r-direction for restriction
    int nRestrictionR = 10;
    //r-direction for outer sections
    int nRingsR = 10;
    // 1/4 of cells in theta direction
    int nRestrictionTheta = 10;

    int nRestrictionZ = 10;
    int nDownstreamZ1 = 10;
    int nDownstreamZ2 = 10;
    int nUpstreamZ = 10;

    //create oType pipe for central section of upstream pipe
    pipe::oTypeExpanding upstreamCore
        (
            l1,
            r0,
            restrictionRadius,
            initialZ,
            innerA,
            innerR
        );

    element ** upstreamRing;
    upstreamRing = new element*[4];
    for(int i = 0; i < 4; i++){
        double alpha1 = (i + 0.5) * 2.0 * M_PI / 4.0;
        double alpha2 = (i + 1.5) * 2.0 * M_PI / 4.0;

        upstreamRing[i] = 
            new expandingCylinder
            (
                r0,
                R,
                restrictionRadius,
                R,
                alpha1,
                alpha2,
                initialZ,
                l1
            );
    }

    pipe::oTypeExpanding expandingSectionCore
        (
            l3,
            restrictionRadius,
            r0,
            initialZ + l1 + l2,
            innerA,
            innerR
        );

    element ** expandingSectionRing;
    expandingSectionRing = new element*[4];
    for(int i = 0; i < 4; i++){
        double alpha1 = (i + 0.5) * 2.0 * M_PI / 4.0;
        double alpha2 = (i + 1.5) * 2.0 * M_PI / 4.0;
        expandingSectionRing[i] = 
            new expandingCylinder
            (
                restrictionRadius,
                R,
                r0,
                R,
                alpha1,
                alpha2,
                initialZ + l1 + l2,
                l3
            );
    }


    //create restriction section
    pipe::oType restriction
        (
            l2,
            restrictionRadius,
            l1 + initialZ,
            innerA,
            innerR
        );

    //create downstream section
    pipe::oType downstreamPipeCore
        (
            l4,
            r0,
            l1 + l2 + l3 + initialZ,
            innerA,
            innerR
        );

    element ** downstreamRing;
    downstreamRing = new element*[4];
    for(int i = 0; i < 4; i++){
        double alpha1 = (i + 0.5) * 2.0 * M_PI / 4.0;
        double alpha2 = (i + 1.5) * 2.0 * M_PI / 4.0;
        downstreamRing[i] = 
            new cylinder
            (
                r0,
                R,
                alpha1,
                alpha2,
                initialZ + l1 + l2 + l3,
                l4
            );
    }

    //create mesh object
    mesh M;
    upstreamCore.nCell(nRestrictionR, nRestrictionTheta * 4, nUpstreamZ);
    restriction.nCell(nRestrictionR, nRestrictionTheta * 4, nRestrictionZ);
    expandingSectionCore.nCell(nRestrictionR, nRestrictionTheta * 4, nDownstreamZ1);
    downstreamPipeCore.nCell(nRestrictionR, nRestrictionTheta * 4, nDownstreamZ2);

    for(int i=0; i<4; i++)
    {
        upstreamRing[i] -> nCell(nRingsR, nRestrictionTheta, nUpstreamZ);
        expandingSectionRing[i] -> nCell(nRingsR, nRestrictionTheta, nDownstreamZ1);
        downstreamRing[i] -> nCell(nRingsR, nRestrictionTheta, nDownstreamZ2);
    }

    //set convertToMeters (1.0 is the default value)
    M.scale() = 1.0;

    //mesh tolerance can be set (1e-05 is the default value)
    constant::tolerance = 1e-05;

    M.addElement(upstreamCore);
    M.addElement(expandingSectionCore);
    M.addElement(downstreamPipeCore);
    for(int i=0; i<4; i++)
    {
        M.addElement(*upstreamRing[i]);
        M.addElement(*expandingSectionRing[i]);
        M.addElement(*downstreamRing[i]);
    }
    M.addElement(restriction);

    M.addPatch(z, initialZ, "inlet", p);
    M.addPatch(z, initialZ + l1 + l2 + l3 + l4, "outlet", p);

    M.addPatch(r, R, "walls", w);
    M.addToPatch(r, restrictionRadius, "walls");
    M.addToPatch(z, initialZ + l1, "walls");
    M.addToPatch(z, initialZ + l1 +l2, "walls");

    M.write();
}
