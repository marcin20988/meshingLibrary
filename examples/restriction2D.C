#include <iostream>
#include <string>
#include <math.h>
#include "meshing.H"

using namespace meshing;

int main(){
    int meshMultiplier = 1;

    //initial point coordinates
    double x_ = 0;
    double y_ = 0;
    double z_ = 0;

    //restriction location
    double restriction = 0.4;
    //restriction length
    double restrictionL = 0.005;
    //pipe length after restriction
    double pipeLength = 0.6;
    //restriction radious
    double r = 0.0075;
    //pipe radious
    double R = 0.015;
    //z thicknes
    double zThickness = 0.01;
    //-------------number of cells------------------
    //for centerline blocks
    int nr = meshMultiplier * 20;
    //for outside blocks
    int nR = meshMultiplier * 10;
    //upstream x
    int nX1 = meshMultiplier * 100;
    //restriction x
    int nX2 = meshMultiplier * 6;
    //downstream x
    int nX3 = meshMultiplier * 200;
    //z
    int nz = 1;
    //zGradients
    float grad1 = 0.2; 
    float grad2 = 5; 

    //centerline blocks
    block centralUpstream
        (
            point(x_, y_ - r, z_),
            restriction,
            2.0 * r,
            zThickness
        );
    centralUpstream.nCell(nX1, nr, nz);
    centralUpstream.nGrading(grad1, 1.0, 1.0);

    block centralRestriction
        (
            point(x_ + restriction, y_ - r, z_),
            restrictionL,
            2.0 * r,
            zThickness
        );
    centralRestriction.nCell(nX2, nr, nz);

    block centralDownstream
        (
            point(x_ + restriction + restrictionL, y_ - r, z_),
            pipeLength,
            2.0 * r,
            zThickness
        );
    centralDownstream.nCell(nX3, nr, nz);
    centralDownstream.nGrading(grad2, 1.0, 1.0);

    //side blocks (y >0)
    block topUpstream
        (
            point(x_, y_ + r, z_),
            restriction,
            R-r,
            zThickness
        );
    topUpstream.nCell(nX1, nR, nz);
    topUpstream.nGrading(grad1, 1.0, 1.0);

    block topDownstream
        (
            point(x_ + restriction + restrictionL, y_ + r, z_),
            pipeLength,
            R-r,
            zThickness
        );
    topDownstream.nCell(nX3, nR, nz);
    topDownstream.nGrading(grad2, 1.0, 1.0);

    //side blocks (y < 0)
    block bottomUpstream
        (
            point(x_, y_ -R, z_),
            restriction,
            R-r,
            zThickness
        );
    bottomUpstream.nCell(nX1, nR, nz);
    bottomUpstream.nGrading(grad1, 1.0, 1.0);

    block bottomDownstream
        (
            point(x_ + restriction + restrictionL, y_ - R, z_),
            pipeLength,
            R-r,
            zThickness
        );
    bottomDownstream.nCell(nX3, nR, nz);
    bottomDownstream.nGrading(grad2, 1.0, 1.0);


    //create mesh object
    mesh M;

    M.addElement(centralUpstream);
    M.addElement(centralRestriction);
    M.addElement(centralDownstream);

    M.addElement(topUpstream);
    M.addElement(topDownstream);

    M.addElement(bottomUpstream);
    M.addElement(bottomDownstream);
    //set convertToMeters (1.0 is the default value)
    M.scale() = 1;

    M.addPatch(x, x_ ,"inlet");
    M.addPatch(x, x_ + restriction + restrictionL + pipeLength,"outlet");

    M.addPatch(y, y_ + R, "walls",w);
    M.addToPatch(y, y_ - R, "walls");
    M.addToPatch(x, x_ + restriction, "walls");
    M.addToPatch(x, x_ + restriction + restrictionL, "walls");
    M.addToPatch(y, y_ + r , "walls");
    M.addToPatch(y, y_ - r , "walls");

    M.addPatch(z, z_, "frontAndBack",e);
    M.addToPatch(z, z_ + zThickness, "frontAndBack");

    M.write();

}
