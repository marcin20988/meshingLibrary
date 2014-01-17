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
   * - pipe radius
   * - initial z coordinate of the element
   * - size of the square-based hexahedron in the center (this is relative to
   *   the pipe radius so choose between 0 and 1!)
   * - radius of above square's rounding (also relative to the pipe radius)
   * - rounding of the elements around inner hexahedron (should be 'twoSided')
   * - name
   */
    oType
        (
            double length,
            double radius,
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
    * O-Type pipe consisting of multiple segments (also O-Type pipes)
 */
class segmentedOType: public multiElement
{
 protected:
  double * segmentsZ_;
  double l_;
 public:
  /**
   * \brief
   * constructor is similar to meshing::oType
   * byt contains two additional arguments:
   * - segmentsN : how many segments constitute to a full pipe
   * - location of segments ENDS (relative to the pipe inlet)
   *   example:
   *
   * double * zList[2] = {0.5,2.0}
   * segmentedOType pipe1
   * (
   *    2.0,
   *    0.2,
   *    2,
   *    zList
   * );
   * will create pipe of length 2.0 created from two separate O-Type pipe of
   * with z coordinates from 0 to 0.5 and 0.5 to 2.0.
   */
    segmentedOType
        (
            double length,
            double radius,
            int segmentsN,
            double * segmentsZ,
            double initialZ = 0.0,
            double squareSize = 0.2,
            double squareRadious = 0.22,
            rounding = twoSided,
            std::string name = "segmented-oType-pipe"
        );

    /**
     * \brief
     * number of cells in r, theta and z directions (evenly distributed between
     * segments)
     */
    void nCell(int nR, int nTheta, int nZ)
    {
        for(int i=0; i<nrOfElements_; i++)
        {
            elements_[i] -> nCell(nR, nTheta, nZ * (segmentsZ_[i] / l_) ) ;
        }
    };

    /**
     * \brief
     * number of cells in r, theta and z directions (manualy distributed between
     * segments)
     */
    void nCell(int nR, int nTheta, int * nZ)
    {
        for(int i=0; i<nrOfElements_; i++)
        {
            elements_[i] -> nCell(nR, nTheta, nZ[i] ) ;
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
   * - ring inner radius
   * - ring outer radius
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
 * ring segmented in z direction
 */
class segmentedRing: public multiElement
{
 protected: 
  int nSegmentsZ_;
  double l_;
  double * segmentEnds_;
 public:
  /**
   * \brief
   * create a ring element (will be aligned along z-axis in the
   * cylindrical coordinate system) segmented in z direction
   *
   */
  segmentedRing
      (
          double length,
          double innerRadious,
          double outerRadious,
          int nSegmentsZ,
          double * segmentEnds,
          double initialZ = 0.0,
          int numberOfSegments = 4,
          double deltaAlpha = 0,
          std::string name = "ring"
      );

    /**
     * \brief
     * number of cells in r, theta and z directions (evenly distributed between
     * segments)
     */
    void nCell(int nR, int nTheta, int nZ)
    {
        for(int i=0; i<nrOfElements_; i++)
        {
            std::cout << segmentEnds_[i] << std::endl;
            elements_[i] -> nCell(nR, nTheta, nZ * (segmentEnds_[i] / l_) ) ;
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
   * - orifice radius
   * - pipe radius
   * - z-coordinate of the restriction (relative to the pipe inlet)
   * - lenght of the restriction (in the z-direction)
   * - initial z coordinate of the whole element
   * - size of the square-based hexahedron in the center (this is relative to
   *   the orifice radius so choose between 0 and 1!)
   * - radius of above square's rounding (also relative to the orifice radius)
   * - rounding of the elements around inner hexahedron (should be 'twoSided')
   * - name
   */
  restrictedPipe 
      (
          double length,
          double radius,
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


/**
 * \brief
 * similar to restricted pipe but downstream pipe section is divided into two
 * segments (to allow waxInlet from the wall)
 */
class pig: public restrictedPipe
{

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
   * - orifice radius
   * - pipe radius
   * - z-coordinate of the restriction (relative to the pipe inlet)
   * - lenght of the restriction (in the z-direction)
   * - wax inlet length in z direction (will be placed right after the orifice)
   * - initial z coordinate of the whole element
   * - size of the square-based hexahedron in the center (this is relative to
   *   the orifice radius so choose between 0 and 1!)
   * - radius of above square's rounding (also relative to the orifice radius)
   * - rounding of the elements around inner hexahedron (should be 'twoSided')
   * - name
   */
  pig 
      (
          double length,
          double radius,
          double pipeRadious,
          double restrictionLocation,
          double restrictionLength,
          double waxInletLength,
          double initialZ = 0.0,
          double squareSize = 0.2,
          double squareRadious = 0.22,
          rounding = twoSided,
          std::string name = "restrictedPipe"
      );
};

}//end namespace pipe

}//end namespace meshing
#endif

