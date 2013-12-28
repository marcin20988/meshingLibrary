#ifndef elements_H
#define elements_H
#include <string>
#include <iostream>
#include "primitives.H"
namespace meshing
{


//abstract class for element objects (simple geometric objects)
//this class is used inside mesh to write all vertices, hexes and edges
class element
{
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

  virtual void nCell(int nX, int nY, int nZ)
  {
      for(int i = 0; i <  nrOfHexes_; i++){
          hexList_[i].nCell(nX,nY,nZ);
      }
  };
  
  virtual void nGrading(int nX, int nY, int nZ)
  {
      for(int i = 0; i <  nrOfHexes_; i++){
          hexList_[i].nGrading(nX,nY,nZ);
      }
  };


  virtual void setArcsN(const int n)
  {
      nrOfArcs_ = n;
      delete[] arcList_;
      arcList_ = new arc[n];
  }

  virtual ~element(){};

  virtual int addArcsToList(arc *&aList, int & arcListLength);

  virtual void findFace(coordinate axis, double value, patch& targetPatch) const
  {
      for(int i=0; i< nrOfHexes_; i++)
      {
          targetPatch.addFace
              (
                  hexList_[i].findFace(axis, value)
              );
      }
  };
};


//abstract class inheriting from element class
//it contains multiple element objects and all functions from element class
//are overwritten with functions calling appropriate methods on each instance of
//the element class created inside multiElement class
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
      int n = 0;
      for(int i=0; i< nrOfElements_; i++){
          n += elements_[i] -> assignLabels(pList, pListLength);
      }

      return n;
  };

  virtual void labelArcs(const point *pList, const int pListLength)
  {
      for(int i=0; i< nrOfElements_; i++){
          elements_[i] -> labelArcs(pList, pListLength);
      }
  };

  virtual std::string write()
  {
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

  virtual void nGrading(int nX, int nY, int nZ)
  {
      for(int i=0; i< nrOfElements_; i++){
          elements_[i] -> nGrading(nX, nY, nZ);
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
      int n = 0;
      for(int i=0; i< nrOfElements_; i++){
          n += elements_[i] -> addArcsToList(aList, arcListLength);
      }
      return n;
  };

  virtual void findFace(coordinate axis, double value, patch& targetPatch) const
  {
      for(int i=0; i< nrOfElements_; i++){
          elements_[i] -> findFace(axis, value, targetPatch);
      }
  }
};

}//end namespace meshing
#endif


