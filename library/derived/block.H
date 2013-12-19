#ifndef blocks_H
#define blocks_H
#include "elements.H"
#include "mesh.H"
#include <math.h>

class block:public element{
 public:
  //create a cube
  block
      (
          point p1, //starting point
          double a, //cube width
          std::string name="cube"
      );
  
  //create a box
  block
      (
          point p1, //starting point
          double a, //cube x-width
          double b, //cube y-width
          double c, //cube z-width
          std::string name="box"
      );

  //create a trapezoid
  block
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
