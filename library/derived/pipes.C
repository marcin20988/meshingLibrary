#include "pipes.H"

namespace pipe
{

oType::oType
(
    double length,
    double radious,
    double squareSize,
    double squareRadious,
    rounding,
    std::string name
):
multiElement(1,name)
{
    double r = squareRadious * radious;

    elements_[0] = 
        new cylinder
        (
            point( - squareSize / 2.0 , - squareSize / 2.0 , 0 ),
            squareSize,
            length,
            squareRadious
        );


};

};//end namespace pipe
