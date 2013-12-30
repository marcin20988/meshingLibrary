#ifndef pipes_H
#define pipes_H
#include "cylinder.H"
namespace meshing
{

/**
 * \brief
 * namespace gathering pipe-like elements
 */
namespace pipe
{
/**
 * \brief
 * O-Type pipe
 */
class oType: public multiElement
{
 public:
  /**
   * \brief
   * create O-Type pipe element (pipe will be aligned along z-axis in the
   * cylindrical coordinate system)
   *
   * parameters given in the constructor:
   * - length of pipe (in the z-direction)
   * - pipe radious
   * - initial z coordinate of the element
   * - size of the square-based hexahedron in the center (this is relative to
   *   the pipe radious so choose between 0 and 1!)
   * - radious of above square's rounding (also relative to the pipe radious)
   * - rounding of the elements around inner hexahedron (should be 'twoSided')
   * - name
   */
    oType
        (
            double length,
            double radious,
            double initialZ = 0.0,
            double squareSize = 0.2,
            double squareRadious = 0.22,
            rounding = twoSided,
            std::string name = "oType-pipe"
        );
  
    /**
     * \brief
     * number of cells in r, theta and z directions
     *
     * Inner hexahedron is given nTheta / 4 cells in x and y directions to be
     * consistent with sorounding elements.
     * Cells in radial direction are distributed to the elements around inner
     * hex. 
     */
    void nCell(int nR, int nTheta, int nZ)
    {
        elements_[0] -> nCell(nTheta / 4, nTheta / 4, nZ);
        for(int i=0; i<4; i++)
        {
            elements_[i+1] -> nCell(nR, nTheta / 4, nZ);
        }
    };

};


/**
 * \brief
 * ring element
 */
class ring : public multiElement
{
 protected: 
  int nSegments_;
 public:
  /**
   * \brief
   * create a ring element (will be aligned along z-axis in the
   * cylindrical coordinate system)
   *
   * parameters given in the constructor:
   * - length of the ring (in the z-direction)
   * - ring inner radious
   * - ring outer radious
   * - initial z coordinate of the element
   * - number of elements constituting to the ring (from how many rounded hexes
   *   ring is actualy created)
   * - initial theta-coordinate of the first hex 
   * - name
   */
  ring
      (
          double length,
          double innerRadious,
          double outerRadious,
          double initialZ = 0.0,
          int numberOfSegments = 4,
          double deltaAlpha = 0,
          std::string name = "ring"
      );
    
  /**
   * \brief
   *
   * number of cells in r, theta and z direction
   */
  void nCell(int nR, int nTheta, int nZ)
    {
        for(int i=0; i<4; i++)
        {
            elements_[i] -> nCell(nR, nTheta / nSegments_, nZ);
        }
    };

};


/**
 * \brief
 * pipe with an orifice section
 */
class restrictedPipe: public multiElement
{
 protected:
  double l_;
  double r_;
  double R_;
  double z1_;
  double z2_;
  double a_;

 public:
  /**
   * \brief
   * create a restricted pipe element
   *
   * Element constitute from 3 oType pipe sections (one preceeding the orifice,
   * orifice section and one succeeding the orifice) and two ring elements
   * located around oType pipes in the pre- and succeeding sections
   * parameters given in the constructor:
   * - length of pipe (in the z-direction)
   * - orifice radious
   * - pipe radious
   * - z-coordinate of the restriction (relative to the pipe inlet)
   * - lenght of the restriction (in the z-direction)
   * - initial z coordinate of the whole element
   * - size of the square-based hexahedron in the center (this is relative to
   *   the orifice radious so choose between 0 and 1!)
   * - radious of above square's rounding (also relative to the orifice radious)
   * - rounding of the elements around inner hexahedron (should be 'twoSided')
   * - name
   */
  restrictedPipe 
      (
          double length,
          double radious,
          double pipeRadious,
          double restrictionLocation,
          double restrictionLength,
          double initialZ = 0.0,
          double squareSize = 0.2,
          double squareRadious = 0.22,
          rounding = twoSided,
          std::string name = "restrictedPipe"
      );
  
  /**
   * \brief
   * set mesh grading in z direction for 3 segments of the pipe
   *
   * Element constitute from pipe sections one preceeding the orifice,
   * orifice section and one succeeding the orifice
   */
  void nGrading(double n1, double n2, double n3)
    {
        //first oType
        elements_[0] -> nGrading(1, 1, n1);
        //ring around first oType
        elements_[1] -> nGrading(1, 1, n1);
        //restriction section (oType)
        elements_[2] -> nGrading(1, 1, n2);
        //second oType
        elements_[3] -> nGrading(1, 1, n3);
        //ring around second oType
        elements_[4] -> nGrading(1, 1, n3);
    };

  /**
   * \brief
   * set number of cells in r, theta, and z direction
   */
  void nCell(int nR, int nTheta, int nZ)
    {
        int nz1 = nZ * z1_ / l_;
        int nz2 = nZ * z2_ / l_;
        int nz3 = nZ * (l_ - z1_ - z2_) / l_;

        int nR1 = nR * r_ / R_;
        int nR2 = nR * (R_ - r_) / R_;

        //first oType
        elements_[0] -> nCell(nR1, nTheta , nz1);
        //ring around first oType
        elements_[1] -> nCell(nR2, nTheta , nz1);
        //restriction section (oType)
        elements_[2] -> nCell(nR1, nTheta , nz2);
        //second oType
        elements_[3] -> nCell(nR1, nTheta , nz3);
        //ring around second oType
        elements_[4] -> nCell(nR2, nTheta , nz3);
    };

  /**
   * \brief
   * set number of cells in r,theta and z direction for 3 segments of the pipe
   *
   * Element constitute from pipe sections one preceeding the orifice,
   * orifice section and one succeeding the orifice
   */
  void nCell(int nR, int nTheta, int nZ1, int nZ2, int nZ3)
  {
        double r2 = (1 - a_) * r_;
        double R2 = R_ - a_ * r_;
        int nR1 = nR * r2 / R2;
        int nR2 = ceil ( nR * (R2 - r2) / R2 );

        std::cout << "Desired number of cells in radial direction: " << nR << std::endl;
        std::cout << "number of cells for restriction part " << nR1 << std::endl;
        std::cout << "number of cells for rings around restriction part " << nR2 << std::endl;

        //first oType
        elements_[0] -> nCell(nR1, nTheta , nZ1);
        //ring around first oType
        elements_[1] -> nCell(nR2, nTheta , nZ1);
        //restriction section (oType)
        elements_[2] -> nCell(nR1, nTheta , nZ2);
        //second oType
        elements_[3] -> nCell(nR1, nTheta , nZ3);
        //ring around second oType
        elements_[4] -> nCell(nR2, nTheta , nZ3);
  };

};


}//end namespace pipe

}//end namespace meshing
#endif

