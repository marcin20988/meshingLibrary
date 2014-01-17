#include "block.H"

namespace meshing

{

block::block
(
    point p1, //starting point
    double a, //cube width
    std::string name
):
    element(1,name)
{

    double x = p1.x();
    double y = p1.y();
    double z = p1.z();

    hexList_[0] = 
        hex 
        (
            p1,
            point(x+a, y, z),
            point(x+a, y+a, z),
            point(x, y+a, z),
            //
            point(x, y, z+a),
            point(x+a, y, z+a),
            point(x+a, y+a, z+a),
            point(x, y+a, z+a)
        );
};

block::block
(
    point p1, //starting point
    double a, //cube x-width
    double b, //cube y-width
    double c, //cube z-width
    std::string name
):
    element(1,name)
{
    double x = p1.x();
    double y = p1.y();
    double z = p1.z();

    hexList_[0] = 
        hex 
        (
            p1,
            point(x+a, y, z),
            point(x+a, y+b, z),
            point(x, y+b, z),
            //
            point(x, y, z+c),
            point(x+a, y, z+c),
            point(x+a, y+b, z+c),
            point(x, y+b, z+c)
        );
};

//trapezoid element in a ring between two radii (and two andgles)
block::block
(
    double r1, //lower radius
    double r2, //greater radius
    double alpha1, //smaller angle
    double alpha2, //bigger angle
    double initialZ, //length in z-direction
    double zLength, //length in z-direction
    std::string name
):
    element(1,name)
{
    point p1
    (
        r1 * cos(alpha1),
        r1 * sin(alpha1),
        initialZ
    );
    
    point p2
    (
        r2 * cos(alpha1),
        r2 * sin(alpha1),
        initialZ
    );
    
    point p3
    (
        r2 * cos(alpha2),
        r2 * sin(alpha2),
        initialZ
    );
    
    point p4
    (
        r1 * cos(alpha2),
        r1 * sin(alpha2),
        initialZ
    );

    point p5
    (
        r1 * cos(alpha1),
        r1 * sin(alpha1),
        initialZ + zLength
    );
    
    point p6
    (
        r2 * cos(alpha1),
        r2 * sin(alpha1),
        initialZ + zLength
    );
    
    point p7
    (
        r2 * cos(alpha2),
        r2 * sin(alpha2),
        initialZ + zLength
    );
    
    point p8
    (
        r1 * cos(alpha2),
        r1 * sin(alpha2),
        initialZ + zLength
    );
    hexList_[0] = 
        hex 
        (
            p1,
            p2,
            p3,
            p4,
            p5,
            p6,
            p7,
            p8
        );
};

}//end namespace meshing
