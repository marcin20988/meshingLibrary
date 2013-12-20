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
            double squareSize = 0.22,
            double squareRadious = 0.2,
            rounding = twoSided,
            std::string name = "oType-pipe"
        );
};
}//end namespace pipe


#endif
