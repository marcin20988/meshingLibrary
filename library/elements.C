#include "elements.H"

element::element(const int N, const std::string name, const int Narc):
nrOfHexes_(N),
hexList_( new hex[N] ),
nrOfArcs_(Narc),
arcList_( new arc[Narc] ),
name_(name)
{
};
  

int element::assignLabels(point *& pList, int &pListLength)
{
    std::cout << "Asigning labels for element: " << name_ << std::endl;
    int counter = 0;


    for(int i=0; i< nrOfHexes_; i++){
        counter += hexList_[i].assignLabels(pList, pListLength);
    }
    

    std::cout << "assigned " << counter << " new labels\n";

    return counter;
};

std::string element::write()
{
    std::string blocks="";
    for(int i=0; i< nrOfHexes_; i++){
        blocks += hexList_[i].write();
    }
    return blocks;
};

void element::labelArcs(const point *pList, const int pListLength)
{
    for(int i=0; i< nrOfArcs_; i++)
    {
        arcList_[i].label(pList, pListLength);
    }
}

int element::addArcsToList(arc *&aList, int & arcListLength)
{
    int counter = 0;

    //point addedPoint[8];
    bool isOnList = false;

    for(int i=0; i<nrOfArcs_; i++){
        isOnList = false;
        arc &currentArc = arcList_[i];
        
        for(int j=0; j< arcListLength; j++){
            arc &listArc = aList[j];

            if(currentArc == listArc){
                isOnList = true;
            }
        }

        if(!isOnList){
            counter ++;
            arc *aTempList = new arc[arcListLength + 1];

            for(int iter = 0; iter < arcListLength; iter++){
                aTempList[iter] = aList[iter];
            }
            aTempList[arcListLength++] = currentArc;

            delete[] aList;
            aList = aTempList;
        }
    }

    return counter;

}
