#ifndef cylinders_H
#define cylinder_H

#include "elements.H"
#include "mesh.H"
#include <math.h>

class cylinder: public element
{
  //create a trapezoid
 public:
    cylinder 
        (
            double r1, //lower radious
            double r2, //greater radious
            double alpha1, //smaller angle
            double alpha2, //bigger angle
            double initialZ, //length in z-direction
            double zLength, //length in z-direction
            std::string name="trapezoid"
        );
};


#endif
