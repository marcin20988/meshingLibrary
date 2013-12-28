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
};



class ring:public multiElement
{
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
};



class restrictedPipe: public multiElement
{
 public:
  restrictedPipe 
      (
          double length,
          double radious,
          double pipeRadious,
          double restrictionLocation,
          double restrictionLength,
          double initialZ = 0.0,
          double squareSize = 0.22,
          double squareRadious = 0.2,
          rounding = twoSided,
          std::string name = "oType-pipe"
      );
};


}//end namespace pipe


#endif
