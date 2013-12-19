#include "cylinder.H"

//trapezoid element in a ring between two radii (and two andgles)
cylinder::cylinder
(
    double r1, //lower radious
    double r2, //greater radious
    double alpha1, //smaller angle
    double alpha2, //bigger angle
    double initialZ, //length in z-direction
    double zLength, //length in z-direction
    std::string name
):
    element(1,name,2)
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

    point arc23
    (
        r2 * cos( (alpha2 + alpha1) / 2.0 ),
        r2 * sin( (alpha2 + alpha1) / 2.0 ),
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
    
    point arc67
    (
        r2 * cos( (alpha2 + alpha1) / 2.0 ),
        r2 * sin( (alpha2 + alpha1) / 2.0 ),
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

    arcList_[0] = arc(p2, p3, arc23);
    arcList_[1] = arc(p6, p7, arc67);
};

