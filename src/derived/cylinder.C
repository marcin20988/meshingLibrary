#include "cylinder.H"
namespace meshing
{
//trapezoid element in a ring between two radii (and two andgles)
cylinder::cylinder
(
    double r1, //lower radious
    double r2, //greater radious
    double alpha1, //smaller angle
    double alpha2, //bigger angle
    double initialZ, //length in z-direction
    double zLength, //length in z-direction
    rounding rnd,
    double innerR,
    std::string name
):
    element(1,name,2)
{

    double R = ( innerR < 0)? r1 : innerR;

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
    
    point arc14
    (
        R * cos( (alpha2 + alpha1) / 2.0 ),
        R * sin( (alpha2 + alpha1) / 2.0 ),
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
    
    point arc58
    (
        R * cos( (alpha2 + alpha1) / 2.0 ),
        R * sin( (alpha2 + alpha1) / 2.0 ),
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

    if(rnd == twoSided){
        setArcsN(4);
    }
    arcList_[0] = arc(p2, p3, arc23);
    arcList_[1] = arc(p6, p7, arc67);
    if(rnd == twoSided){
        arcList_[2] = arc(p1, p4, arc14);
        arcList_[3] = arc(p5, p8, arc58);
    }
};

cylinder::cylinder 
(
    point p1, //starting point
    double a, //cube x-width
    double c, //cube z-width
    double r, //rounding radious
    std::string name
)
    :
    element(1,name,8)
{
    float b = a;
    double x = p1.x();
    double y = p1.y();
    double z = p1.z();

    point p2(x+a, y, z);
    point p3(x+a, y+b, z);
    point p4(x, y+b, z);
    //
    point p5(x, y, z+c);
    point p6(x+a, y, z+c);
    point p7(x+a, y+b, z+c);
    point p8(x, y+b, z+c);

    hexList_[0] = 
        hex 
        (
            p1, p2, p3, p4, p5, p6, p7, p8
        );

    double dr = r - a;

    arcList_[0] = arc
        (
            p1,
            p2,
            point
            (
                x + 0.5 * a,
                p1.y() - dr,
                z
            )
        );

    arcList_[1] = arc
        (
            p2,
            p3,
            point
            (
                x + a + dr,
                y + 0.5 * b,
                z
            )
        );

    arcList_[2] = arc
        (
            p3,
            p4,
            point
            (
                x + 0.5 * a,
                p3.y() + dr,
                z
            )
        );

    arcList_[3] = arc
        (
            p4,
            p1,
            point
            (
                x - dr,
                y + 0.5 * b,
                z
            )
        );

    arcList_[4] = arc
        (
            p5,
            p6,
            point
            (
                x + 0.5 * a,
                p1.y() - dr,
                z + c
            )
        );

    arcList_[5] = arc
        (
            p6,
            p7,
            point
            (
                x + a + dr,
                y + 0.5 * b,
                z + c
            )
        );

    arcList_[6] = arc
        (
            p7,
            p8,
            point
            (
                x + 0.5 * a,
                p3.y() + dr,
                z + c
            )
        );

    arcList_[7] = arc
        (
            p8,
            p5,
            point
            (
                x - dr,
                y + 0.5 * b,
                z + c
            )
        );

};

}//end namespace meshing

