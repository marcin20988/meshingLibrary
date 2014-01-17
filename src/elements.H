#ifndef elements_H
#define elements_H
#include <string>
#include <iostream>
#include "primitives.H"
namespace meshing
{


/**
 * \brief
 * Base class for element objects (simple geometric objects)
 *
 * This class is used inside mesh object to write all vertices, hexes and edges.
 * All methods are virtual because there are very likely to be modified in the
 * inheriting classes.
 */
class element
{
 protected:
  int nrOfHexes_;
  hex *hexList_;

  int nrOfArcs_;
  arc *arcList_;

  std::string name_;
  //TODO: handle region names(e.g hex myRegion (...) )
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

  /**
   * \brief
   * pass the hex::assignLabels command to all of hex objects it contains
   */
  virtual int assignLabels(point *& pList, int &pListLength);

  /**
   * \brief
   * pass the arc::label command to all of arc objects it contains
   */
  virtual void labelArcs(const point *pList, const int pListLength);

  /**
   * \brief
   * gather all hex::write entries and retrun the result
   */
  virtual std::string write();

  /**
   * \brief
   * pass the hex::nCell command to all of hex objects it contains
   */
  virtual void nCell(int nX, int nY, int nZ)
  {
      for(int i = 0; i <  nrOfHexes_; i++){
          hexList_[i].nCell(nX,nY,nZ);
      }
  };
  
  /**
   * \brief
   * pass the hex::nGrading command to all of hex objects it contains
   */
  virtual void nGrading(double nX, double nY, double nZ)
  {
      for(int i = 0; i <  nrOfHexes_; i++){
          hexList_[i].nGrading(nX,nY,nZ);
      }
  };


  /**
   * \brief
   * set number of arcs
   */
  virtual void setArcsN(const int n)
  {
      nrOfArcs_ = n;
      delete[] arcList_;
      arcList_ = new arc[n];
  }

  virtual ~element(){};

  /**
   * \brief
   * append all arcs that are not yet on the list to it
   */
  virtual int addArcsToList(arc *&aList, int & arcListLength);

  /**
   * \brief
   * run the hex::findFace command to all of hex objects it contains and feed the
   * results to patch::addFace method of a targetPatch
   */
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


/**
 * \brief
 * base class for more complex elements that consist of multiple simplier elements
 *
 * This class contains multiple element objects and all functions from element 
 * class are overwritten with functions calling appropriate methods on each 
 * instance of the element class created inside multiElement class.
 * Note: instance of multiElement class can cointain multiElement object as
 * an entry in the element list
 */
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

  virtual void nGrading(double nX, double nY, double nZ)
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


