#include "pipes.H"

namespace meshing
{
namespace pipe
{

oType::oType
(
    double length,
    double radious,
    double initialZ,
    double squareSize, //relative to the pipe radious!
    double squareRadious, //relative to the pipe radious
    rounding,
    std::string name
):
multiElement(5,name)
{
    double r = 2.0 / sqrt(2.0) * squareRadious * radious;
    double a = 2.0 / sqrt(2.0) * squareSize * radious;


    elements_[0] = 
        new cylinder
        (
            point( - a / 2.0 , - a / 2.0 , initialZ ),
            a,
            length,
            r
        );

    for(int i=0; i<4; i++){
        float alpha1 = (i + 0.5) * 2.0 * M_PI / 4.0;
        float alpha2 = (i+1.5) * 2.0 * M_PI / 4.0;
        elements_[i+1] = new cylinder
            (
                sqrt(2) * 0.5 * a,
                radious,
                alpha1,
                alpha2,
                initialZ,
                length
            );
        //elements_[i+1] = new element;
    }


};

//----------------------------------------
ring::ring
(
    double length,
    double innerRadious,
    double outerRadious,
    double initialZ,
    int numberOfSegments,
    double deltaAlpha,
    std::string name
):
multiElement(numberOfSegments,name)
{
    nSegments_ = numberOfSegments;

    for(int i=0; i<numberOfSegments; i++){
        float alpha1 = deltaAlpha + i * 2.0 * M_PI / numberOfSegments;
        float alpha2 = deltaAlpha + (i+1.0) * 2.0 * M_PI / numberOfSegments;
        elements_[i] = new cylinder
            (
                innerRadious,
                outerRadious,
                alpha1,
                alpha2,
                initialZ,
                length,
                twoSided
            );
    }


};



//----------------------------------------

restrictedPipe::restrictedPipe
(
    double length,
    double radious,
    double pipeRadious,
    double restrictionLocation, //from the begining of pipe
    double restrictionLength,
    double initialZ,
    double squareSize, //relative to the pipe radious!
    double squareRadious, //relative to the pipe radious
    rounding rnd,
    std::string name
):
multiElement(5,name)
{
    l_ = length;
    r_ = radious;
    R_ = pipeRadious;
    z1_ = restrictionLocation;
    z2_ = restrictionLength;
    a_ = squareSize;

    elements_[0] = new oType
        (
            restrictionLocation,
            radious,
            initialZ,
            squareSize,
            squareRadious,
            rnd,
            "oType1"
        );

    elements_[1] = new ring
        (
            restrictionLocation,
            radious,
            pipeRadious,
            initialZ,
            4,
            M_PI / 4.0,
            "ring1" 
        );

    elements_[2] = new oType
        (
            restrictionLength,
            radious,
            initialZ + restrictionLocation,
            squareSize,
            squareRadious,
            rnd,
            "oType2"
        );
    double z = restrictionLocation + restrictionLength;
    double l = length - z;
    double iZ = initialZ + z;

    elements_[3] = new oType
        (
            l,
            radious,
            iZ,
            squareSize,
            squareRadious,
            rnd,
            "oType2"
        );

    elements_[4] = new ring
        (
            l,
            radious,
            pipeRadious,
            iZ,
            4,
            M_PI / 4.0,
            "ring2" 
        );

};



};//end namespace pipe
}//end namespace meshing
