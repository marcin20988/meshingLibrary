#ifndef cylinders_H
#define cylinders_H

#include "elements.H"
#include <math.h>

namespace meshing
{

/**
 * \brief
 * simple elements defined in cylindrical coordinate system
 */
class cylinder: public element
{
    //create a rounded trapezoid (rounded on outer side only or both sides)
 public:
  /**
   * \brief
   * hexahedron created between two radii and angles and rounder on one or two
   * sides (element of a ring)
   *
   * parameters given in the constructor are:
   * - smaller radious
   * - bigger radious
   * - smaller angle (in the cylindrical coordinate system)
   * - bigger angle (in the cylindrical coordinate system)
   * - initial z-coordinate of the element
   * - z-length of the element
   * - rounding {oneSided, twoSided}
   * - curvature radious of the inner wall (if negative lower radious wille be
   *   used)
   * - name
   */
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

  /**
   * \brief
   * square-based hexahedron with rounded sides (for pipe::oType)
   *
   * parameters given in the constructor are:
   * - starting point of the element
   * - x-width and y-width (square based element)
   * - z-width
   * - curvature radious
   * - name
   */
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

