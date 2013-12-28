#include "primitives.H"
#include "math.h"

//points--------------------------------------------------------------

point::point(double x, double y, double z){
    x_ = x;
    y_ = y;
    z_ = z;
}

point::point(){
    x_ = 0.0;
    y_ = 0.0;
    z_ = 0.0;
}

double point::x() const {
    return x_;
} 

double point::y() const {
    return y_;
}


double point::z() const {
    return z_;
}

point& point::operator=(const point& P){
    x_ = P.x();
    y_ = P.y();
    z_ = P.z();

    return *this;
}

bool point::operator==(const point& P){
    //TODO: define tolerance in some better way
    double tolerance = 1e-04;
    bool same = false;
    if
    (
        //x_ == P.x()
        //&& y_ == P.y()
        //&& z_ == P.z()
        fabs( (x_ - P.x()) ) < tolerance
        && fabs( (y_ - P.y()) )< tolerance
        && fabs( (z_ - P.z()) ) < tolerance
    ){
        same = true;
    }

    return same;
};
//faces --------------------------------------------------------------
face::face(
    const point p1, 
    const point p2, 
    const point p3, 
    const point p4
){
    point1_ = p1;
    point2_ = p2;
    point3_ = p3;
    point4_ = p4;
}

face::face(){};

//arcs ---------------------------------------------------------------

arc::arc(){};

arc::arc(int label1, int label2, point p)
{
    pointLabel1_ = label1;
    pointLabel2_ = label2;
    arcPoint_ = p;
};

arc::arc(point p1, point p2, point arcP)
{
    p1_ = p1;
    p2_ = p2;
    arcPoint_ = arcP;
}

bool arc::operator==(const arc A) const
{
    //Info << "test : \n" << "LHS: 
    bool isSame = false;
    if(pointLabel1_ == A.label1() || pointLabel1_ == A.label2()){
        if(pointLabel2_ == A.label1() || pointLabel2_ == A.label2()){
            isSame = true;
        }
    }

    return isSame;
}
  
void arc::label(const point *pList,const int pListLength)
{
    int l1 = -1;
    int l2 = -1;
    for(int i = 0; i < pListLength; i++){
        const point &currentPoint = pList[i];
        if( p1_ == currentPoint ) l1 = i;
        if( p2_ == currentPoint ) l2 = i;
    }

    pointLabel1_ = l1;
    pointLabel2_ = l2;
};

std::string arc::write()
{
    std::string a = "";
    a += "\t\tarc ";
    
    std::ostringstream ss;
    ss << pointLabel1_ << " " << pointLabel2_ << " ";
    ss <<"(" << arcPoint_.x() << " " << arcPoint_.y() << " " << arcPoint_.z() << ")\n";

    std::string s(ss.str());
    a += s;
    return a;
}

//hexes --------------------------------------------------------------

hex::hex()
{
    nCell(1,1,1);
    nGrading(1,1,1);
};
    
hex::hex(point p1, point p2,point p3, point p4, point p5, point p6, point p7, point p8){
    pointList_[0] = p1;
    pointList_[1] = p2;
    pointList_[2] = p3;
    pointList_[3] = p4;
    pointList_[4] = p5;
    pointList_[5] = p6;
    pointList_[6] = p7;
    pointList_[7] = p8;

    nCell(1,1,1);
    nGrading(1,1,1);
}

int hex::assignLabels(point *& pList, int &pListLength){
    //number of new vertices added to list
    int counter = 0;

    //point addedPoint[8];
    bool isOnList = false;

    for(int i=0; i<8; i++){
        isOnList = false;
        point &currentPoint = pointList_[i];
        int label = -1;
        for(int j=0; j< pListLength; j++){
            point &listPoint = pList[j];

            //std::cout << "(" << currentPoint.x() << " ";
            //std::cout << currentPoint.y() << " ";
            //std::cout << currentPoint.z() << " )\n";

            if(listPoint == currentPoint){
                isOnList = true;
                label = j;
            }
        }

        if(!isOnList){
            counter++;
            
            point *pTempList = new point[pListLength + 1];

            for(int iter = 0; iter < pListLength; iter++){
                pTempList[iter] = pList[iter];
            }
            pTempList[pListLength++] = currentPoint;

            delete[] pList;
            pList = pTempList;
            
            label = pListLength-1;
        }

        labelList_[i] = label;
    }




    return counter;
}

std::string hex::write(){

    std::string block = "";
    block += "\t\thex (";
    for(int i=0; i<8; i++){
        std::ostringstream ss;
        ss << labelList_[i];
        std::string s(ss.str());
        block += s + " ";
    }
    block += ") (";
    for(int i=0; i<3; i++){
        std::ostringstream ss;
        ss << cells[i];
        std::string s(ss.str());
        block += s + " ";
    }
    block += ") simpleGrading (";
    for(int i=0; i<3; i++){
        std::ostringstream ss;
        ss << grading[i];
        std::string s(ss.str());
        block += s + " ";
    }
    block += ")\n";

    return block;
}
