#include "pipes.H"

namespace meshing
{
namespace pipe
{

oType::oType
(
    double length,
    double radius,
    double initialZ,
    double squareSize, //relative to the pipe radius!
    double squareRadius, //relative to the pipe radius
    rounding,
    std::string name
):
    multiElement(5,name)
{
    double r = 2.0 / sqrt(2.0) * squareRadius * radius;
    double a = 2.0 / sqrt(2.0) * squareSize * radius;


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
                radius,
                alpha1,
                alpha2,
                initialZ,
                length
            );
        //elements_[i+1] = new element;
    }


};

segmentedRing::segmentedRing
(
    double length,
    double innerRadius,
    double outerRadius,
    int nSegmentsZ,
    double * segmentEnds,
    double initialZ,
    int numberOfSegments,
    double deltaAlpha,
    std::string name
):
    multiElement(nSegmentsZ),
    nSegmentsZ_(nSegmentsZ),
    l_(length)
{
    segmentEnds_ = new double[nSegmentsZ];
    for(int i=0; i< nSegmentsZ; i++)
    {
        segmentEnds_[i] = segmentEnds[i];
    }

    double iZ = initialZ;
    double prevL = 0;
    for( int i=0; i< nSegmentsZ; i++)
    {
        if(i > 0)
        {
            prevL = segmentEnds[i - 1];
        }
        elements_[i] = new ring
            (
                segmentEnds[i] - prevL,
                innerRadius,
                outerRadius,
                iZ,
                numberOfSegments,
                deltaAlpha,
                name
            );
        iZ += segmentEnds[i];
    }

};

segmentedOType::segmentedOType
(
    double length,
    double radius,
    int segmentsN,
    double * segmentsZ,
    double initialZ,
    double squareSize, //relative to the pipe radius!
    double squareRadius, //relative to the pipe radius
    rounding rnd,
    std::string name
):
    multiElement(segmentsN,name),
    l_(length)
{
    segmentsZ_ = new double[segmentsN];
    for(int i=0; i< segmentsN; i++)
    {
        segmentsZ_[i] = segmentsZ[i];
    }

    double iZ = initialZ;

    double prevL = 0;
    for( int i=0; i< segmentsN; i++)
    {
        if(i > 0)
        {
            prevL = segmentsZ[i - 1];
        }
        elements_[i] = new oType
            (
                segmentsZ[i] - prevL,
                radius,
                iZ,
                squareSize,
                squareRadius,
                rnd,
                name
            );
        iZ += segmentsZ[i];
    }
};


//----------------------------------------
ring::ring
(
    double length,
    double innerRadius,
    double outerRadius,
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
                innerRadius,
                outerRadius,
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
    double radius,
    double pipeRadius,
    double restrictionLocation, //from the begining of pipe
    double restrictionLength,
    double initialZ,
    double squareSize, //relative to the pipe radius!
    double squareRadius, //relative to the pipe radius
    rounding rnd,
    std::string name
):
multiElement(5,name)
{
    l_ = length;
    r_ = radius;
    R_ = pipeRadius;
    z1_ = restrictionLocation;
    z2_ = restrictionLength;
    a_ = squareSize;

    elements_[0] = new oType
        (
            restrictionLocation,
            radius,
            initialZ,
            squareSize,
            squareRadius,
            rnd,
            "oType1"
        );

    elements_[1] = new ring
        (
            restrictionLocation,
            radius,
            pipeRadius,
            initialZ,
            4,
            M_PI / 4.0,
            "ring1" 
        );

    elements_[2] = new oType
        (
            restrictionLength,
            radius,
            initialZ + restrictionLocation,
            squareSize,
            squareRadius,
            rnd,
            "oType2"
        );
    double z = restrictionLocation + restrictionLength;
    double l = length - z;
    double iZ = initialZ + z;

    elements_[3] = new oType
        (
            l,
            radius,
            iZ,
            squareSize,
            squareRadius,
            rnd,
            "oType2"
        );

    elements_[4] = new ring
        (
            l,
            radius,
            pipeRadius,
            iZ,
            4,
            M_PI / 4.0,
            "ring2" 
        );

};


pig::pig
(
    double length,
    double radius,
    double pipeRadius,
    double restrictionLocation, //from the begining of pipe
    double restrictionLength,
    double waxInletLength,
    double initialZ,
    double squareSize, //relative to the pipe radius!
    double squareRadius, //relative to the pipe radius
    rounding rnd,
    std::string name
):
    restrictedPipe
    (
        length,
        radius,
        pipeRadius,
        restrictionLocation,
        restrictionLength,
        initialZ,
        squareSize,
        squareRadius,
        rnd,
        name
    )
{
    double z = restrictionLocation + restrictionLength;
    double l = length - z;
    double iZ = initialZ + z;

    double zPipe[2] = {waxInletLength, l};
    elements_[3] = new segmentedOType
        (
            l,
            radius,
            2,
            zPipe,
            iZ,
            squareSize,
            squareRadius,
            rnd,
            "oType2"
        );

    elements_[4] = new segmentedRing
        (
            l,
            radius,
            pipeRadius,
            2,
            zPipe,
            iZ,
            4,
            M_PI / 4.0,
            "ring2" 
        );
}

};//end namespace pipe
}//end namespace meshing
