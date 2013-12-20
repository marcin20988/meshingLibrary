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

  virtual const std::string name() const{
      return name_;
  }

  virtual int assignLabels(point *& pList, int &pListLength);

  virtual void labelArcs(const point *pList, const int pListLength);

  virtual std::string write();

  virtual void nCell(int nX, int nY, int nZ){
      for(int i = 0; i <  nrOfHexes_; i++){
          hexList_[i].nCell(nX,nY,nZ);
      }
  };

  virtual void setArcsN(const int n){
      nrOfArcs_ = n;
      delete[] arcList_;
      arcList_ = new arc[n];
  }

  virtual ~element(){};

  virtual int addArcsToList(arc *&aList, int & arcListLength);
};


class multiElement: public element
{
 protected:
  element **elements_;
  int nrOfElements_;

 public:
  multiElement
      (
          const int n = 0,
          const std::string name = "multi-element"
      ):element(0,name,0)
      {
          nrOfElements_ = n;
          elements_ = new element * [n];
      };
 
  virtual int assignLabels(point *& pList, int &pListLength)
  {
      std::cout << "multi-element object\n";
      int n = 0;
      for(int i=0; i< nrOfElements_; i++){
          n += elements_[i] -> assignLabels(pList, pListLength);
      }

      return n;
  };

  virtual void labelArcs(const point *pList, const int pListLength)
  {
      std::cout << "multi-element object\n";
      for(int i=0; i< nrOfElements_; i++){
          elements_[i] -> labelArcs(pList, pListLength);
      }
  };

  virtual std::string write()
  {
      std::cout << "multi-element object\n";
      std::string s="";
      for(int i=0; i< nrOfElements_; i++){
          s += elements_[i] -> write();
      }
      return s;
  };

  virtual void nCell(int nX, int nY, int nZ)
  {
      for(int i=0; i< nrOfElements_; i++){
          elements_[i] -> nCell(nX, nY, nZ);
      }
  };

  virtual void setArcsN(const int n)
  {
      for(int i=0; i< nrOfElements_; i++){
          elements_[i] -> setArcsN(n);
      }
  };

  virtual ~multiElement(){};

  virtual int addArcsToList(arc *&aList, int & arcListLength)
  {
      std::cout << "multi-element object\n";
      int n = 0;
      for(int i=0; i< nrOfElements_; i++){
          n += elements_[i] -> addArcsToList(aList, arcListLength);
      }
      return n;
  };


};
#endif
