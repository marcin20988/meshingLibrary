#ifndef cylinders_H
#define cylinders_H

#include "elements.H"
#include <math.h>

namespace meshing
{


class cylinder: public element
{
    //create a rounded trapezoid (rounded on outer side only or both sides)
 public:
  cylinder 
      (
          double r1, //lower radious
          double r2, //greater radious
          double alpha1, //smaller angle
          double alpha2, //bigger angle
          double initialZ, //length in z-direction
          double zLength, //length in z-direction
          rounding rnd = oneSided,
          double innerR = -1,
          std::string name = "roundedTrapezoid"
      );

  //create a rounded box
  cylinder 
      (
          point p1, //starting point
          double a, //cube x-width
          double c, //cube z-width
          double r, //rounding radious
          std::string name="box"
      );

};

}//end namespace meshing
#endif

