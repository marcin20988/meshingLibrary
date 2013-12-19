#ifndef elements_H
#define elements_H
#include <string>
#include <iostream>
#include "primitives.H"

class element{
 protected:
  int nrOfHexes_;
  hex *hexList_;

  int nrOfArcs_;
  arc *arcList_;

  std::string name_;
  std::string regionName_;

 public:
  element
      (
          const int=0,
          const std::string="unnamed",
          const int =0
      );

  const std::string name() const{
      return name_;
  }

  int assignLabels(point *& pList, int &pListLength);

  void labelArcs(const point *pList, const int pListLength);

  std::string write();

  virtual void nCell(int nX, int nY, int nZ){
      for(int i = 0; i <  nrOfHexes_; i++){
          hexList_[i].nCell(nX,nY,nZ);
      }
  };

  virtual ~element(){};

  int addArcsToList(arc *&aList, int & arcListLength);
};

#endif
