#ifndef pipes_H
#define pipes_H
#include "cylinder.H"

namespace pipe
{
class oType: public multiElement
{
 public:
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
  
    void nCell(int nR, int nTheta, int nZ)
    {
        elements_[0] -> nCell(nTheta / 4, nTheta / 4, nZ);
        for(int i=0; i<4; i++)
        {
            elements_[i+1] -> nCell(nR, nTheta / 4, nZ);
        }
    };

};



class ring : public multiElement
{
 protected: 
  int nSegments_;
 public:
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
    
  void nCell(int nR, int nTheta, int nZ)
    {
        for(int i=0; i<4; i++)
        {
            elements_[i] -> nCell(nR, nTheta / nSegments_, nZ);
        }
    };

};



class restrictedPipe: public multiElement
{
 protected:
  double l_;
  double r_;
  double R_;
  double z1_;
  double z2_;

 public:
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

};


}//end namespace pipe


#endif
