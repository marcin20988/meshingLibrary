#include <iostream>
#include <string>
#include <math.h>
#include "meshing.H"

using namespace meshing;

int main(){
    //create mesh object
    mesh M;

    //set convertToMeters (1.0 is the default value)
    M.scale() = 1.0;

    //mesh tolerance can be set (1e-05 is the default value)
    constant::tolerance = 1e-05;
    
    //create restrictionMesh object
    pipe::pig element1
    (
        1.0,         // length of the whole pipe
        0.0075,      // radius of the restricted section
        0.015,       // pipe radius
        0.4,         // location (from the begining of pipe) of the restriction
        0.005,       // restriction length
        0.01,        // length of the wax-injection area
        //below are argument with default values
        -0.4,        // z-coordinate of the pipe inlet (default is 0.0)
        0.4,         // size of the inner square for the O-Type mesh relative to the restriction radius (default is 0.2) 
        0.44        // radius of the arcs rounding the inner square (default is 0.22)
        //rounding = twoSided   //are the outside element rounded {OneSided, TwoSided}
        //std::string name = "restrictedPipe" //name of the element 
    );

    //set number of cells as follows:
    //nCell(nR, nTheta, nZ) or (nR,nTheta,nZ1, nZ2, nZ3)
    //nZ - total number of cells in z-direction
    //nZ1 - for elements preceeding the restriction
    //nZ2 -  for restriction
    //nZ3 -  for elements succeeding the restriction
    element1.nCell(20, 20, 80, 6, 130);

    //grading (for this element it is only in z-direction for three distinctive
    //parts of the geometry
    //element1.nGrading(0.2, 1, 5);

    //add element to mesh object
    M.addElement(element1);
    //

    //adding new patch to the mesh
    M.addPatch
        (
            z,          // choose coordinate for placing a patch {x,y,z,r,theta}
            -0.4,        //value of the coordinate (all faces with z=0.0 will be added to patch)
            "inlet",    //patch name
            p           // patch type {p for patch, w for wall} // default is p
        );
    
    M.addPatch(z, 0.6, "outlet", p);
    M.addPatch(r, 0.015, "walls", w);

    //will separate part of the patch "walls" and create new patch "waxInlet"
    M.separateFromPatch("walls", z, 0.005, 0.015, "waxInlet",p);

    //add face for existing patch;
    //internal faces will be automaticaly removed from the patch so patch plance
    //can intersect mesh
    M.addToPatch(z, 0.0, "walls");
    M.addToPatch(z, 0.005, "walls");
    M.addToPatch(r, 0.0075, "walls");

    //create blockMeshDict for given geometry
    M.write();

}
