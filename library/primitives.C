#include "primitives.H"
#include "math.h"

namespace meshing
{
double constant::tolerance = 1e-05;

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
    bool same = false;
    if
    (
        fabs( (x_ - P.x()) ) < constant::tolerance
        && fabs( (y_ - P.y()) )< constant::tolerance
        && fabs( (z_ - P.z()) ) < constant::tolerance
    ){
        same = true;
    }

    return same;
};
//faces --------------------------------------------------------------
face::face()
{
    /*label1_= -1;
    label2_= -1;
    label3_= -1;
    label4_= -1;*/
};

face::face(
    const int l1, 
    const int l2, 
    const int l3, 
    const int l4
)
{
   label1_ = l1; 
   label2_ = l2; 
   label3_ = l3; 
   label4_ = l4; 
}

//face::face(){};

face& face::operator=(const face& F){
    label1_ = F.label(0);
    label2_ = F.label(1);
    label3_ = F.label(2);
    label4_ = F.label(3);

    return *this;
}

bool face::operator==(const face& F)
{
    bool result = false;

    if
    (
        label1_ == F.label(0)
        || label1_ == F.label(1)
        || label1_ == F.label(2)
        || label1_ == F.label(3)
    )
    {
        if
        (
            label2_ == F.label(0)
            || label2_ == F.label(1)
            || label2_ == F.label(2)
            || label2_ == F.label(3)
        )
        {
            if
            (
                label3_ == F.label(0)
                || label3_ == F.label(1)
                || label3_ == F.label(2)
                || label3_ == F.label(3)
            )
            {
                if
                (
                    label4_ == F.label(0)
                    || label4_ == F.label(1)
                    || label4_ == F.label(2)
                    || label4_ == F.label(3)
                )
                {
                    result = true;
                }
            }
        }
    }

    return result;
}

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

face hex::findFace(coordinate axis, double value) const
{
    int * pList = new int[4];
    for(int i=0; i<4;i++) pList[i] = -1;

    int iter = 0;
    double rho;
    double angle;

    for(int i=0; i< 8; i++)
    {
        switch (axis)
        {
            case x:
            if( fabs( pointList_[i].x() - value) < constant::tolerance && iter < 4 )
            {
                pList[iter] = labelList_[i];
                iter++;
            }
            break;
            //------------
            case y:
            if( fabs( pointList_[i].y() - value) < constant::tolerance && iter < 4 )
            {
                pList[iter] = labelList_[i];
                iter++;
            }
            break;
            //------------
            case z:
            if( fabs( pointList_[i].z() - value) < constant::tolerance && iter < 4 )
            {
                pList[iter] = labelList_[i];
                iter++;
            }
            break;
            //------------
            case r:
            rho = sqrt 
                ( 
                    pow( pointList_[i].x() , 2)
                    + pow( pointList_[i].y() , 2)
                );

            if( fabs( rho - value) < constant::tolerance && iter < 4 )
            {
                pList[iter] = labelList_[i];
                iter++;
            }
            break;
            //------------
            case theta:
            angle = 0;
            rho = sqrt 
                ( 
                    pow( pointList_[i].x() , 2)
                    + pow( pointList_[i].y() , 2)
                );

            if( pointList_[i].x() >= 0 ){
                if(pointList_[i].x() == 0 && pointList_[i].y() == 0)
                {
                    angle = 0;
                }else
                {
                    angle = asin( pointList_[i].y() / rho);
                }
            }else if( pointList_[i].x() < 0 )
            {
                angle = - asin( pointList_[i].y() / rho ) + M_PI;
            }
            
            if( fabs( angle - value) < constant::tolerance && iter < 4 )
            {
                pList[iter] = labelList_[i];
                iter++;
            }
            break;
        }
    }

    face result;
    
    if(axis == z)
    {
        result = face(pList[0], pList[1], pList[2], pList[3]);
    }
    else
    {
        result = face(pList[0], pList[1], pList[3], pList[2]);
    }

    return result;
};

std::string face::write() const
{
    std::string a = "";
    a += "\t\t";
    
    std::ostringstream ss;
    ss <<"(" << label1_ << " " 
        << label2_ << " " 
        << label3_ << " " 
        << label4_  
        <<")\n";

    std::string s(ss.str());
    a += s;
    return a;
}
//patches:--------------------------------------------------------------------


void patch::addFace(const face F)
{
    //if at least one label is negative skip this face
    for(int i=0; i<4; i++){
        if( F.label(i) < 0) return;
    }


    face * fList = new face[numberOfFaces_ + 1];
    for(int i=0; i<numberOfFaces_; i++)
    {
        fList[i] = faceList_[i];
    }
    fList[numberOfFaces_++] = F;

    delete[] faceList_;
    faceList_ = fList;
    
};

void patch::removeFace(int target)
{
    face * fList = new face[numberOfFaces_ - 1]; 
    int iter = 0;
    for(int i = 0; i < numberOfFaces_; i++)
    {
        if(i != target)
        {
            fList[iter] = faceList_[i];
            iter ++;
        }
    }

    delete[] faceList_;
    faceList_ = fList;
    numberOfFaces_--;
}

void patch::removeFace(const face target)
{
    face * fList = new face[numberOfFaces_ - 1]; 
    int iter = 0;
    for(int i = 0; i < numberOfFaces_; i++)
    {
        if(faceList_[i] == target)
        {
        }else
        {
            fList[iter] = faceList_[i];
            iter++;
        }
    }

    delete[] faceList_;
    faceList_ = fList;
    numberOfFaces_--;
}

std::string patch::write()
{
    std::string a="\t";
    switch (type_)
    {
        case p:
            a += "patch ";
            break;
        case w:
            a+= "wall ";
            break;
    }
    
    a += name_ + "\n\t(\n";

    for(int i=0; i<numberOfFaces_; i++)
    {
        a+= faceList_[i].write();
    }

    a += "\t)\n\n";
    return a;
};

int patch::removeInternalFaces()
{
    int counter = 0;
    //which elements of list should be removed (-1 = stay; +1 remove);
    int *labels = new int[numberOfFaces_];
    for(int i = 0; i < numberOfFaces_; i++)
    {
        labels[i] = -1;
    }

    for(int i = 0; i < numberOfFaces_; i++)
    {
        for(int j = 0; j < numberOfFaces_; j++)
        {
            if( i != j && faceList_[i] == faceList_[j])
            {
                counter++;
                labels[i] = 1;
                labels[j] = 1;
            }
        }
    }

    if(counter > 0)
    {
        face * fList = new face[numberOfFaces_ - counter]; 
        int iter = 0;
        for(int i = 0; i < numberOfFaces_; i++)
        {
            if(labels[i] < 0)
            {
                fList[iter] = faceList_[i];
                iter ++;
            }
        }

        delete[] faceList_;
        faceList_ = fList;
        numberOfFaces_ -= counter;
    }

    return counter;
};




}//end namespace meshing
