#ifndef blocks_H
#define blocks_H
#include "elements.H"
#include "mesh.H"
#include <math.h>

namespace meshing
{

/**
 * \brief
 * simple block-like elements defined in cartesian coordinate system
 */
class block:public element{
 public:
  /**
   * \brief
   * cube with given point and edge length 
   *
   * Point given in constructor is a closest point to origin ot the coordinate
   * system. It means that other point are created by adition of the edge length
   * to one of the initial-point coordinates
   */
  block
      (
          point p1, //starting point
          double a, //cube width
          std::string name="cube"
      );
  
  /**
   * \brief
   * cuboid with given point and edge length 
   *
   * Point given in constructor is a closest point to origin ot the coordinate
   * system. It means that other point are created by adition of a,b or c
   * parameter to one of the initial-point coordinates
   */
  block
      (
          point p1, //starting point
          double a, //cube x-width
          double b, //cube y-width
          double c, //cube z-width
          std::string name="box"
      );

  /**
   * \brief
   * hexahedron created between two radii and angles
   *
   * parameters given in the constructor are:
   * - smaller radius
   * - bigger radius
   * - smaller angle (in the cylindrical coordinate system)
   * - bigger angle (in the cylindrical coordinate system)
   * - initial z-coordinate of the element
   * - z-length of the element
   * - name
   */
  block
      (
          double r1, //lower radius
          double r2, //greater radius
          double alpha1, //smaller angle
          double alpha2, //bigger angle
          double initialZ, //length in z-direction
          double zLength, //length in z-direction
          std::string name="trapezoid"
      );


};

}//end namespace meshing
#endif

