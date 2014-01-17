#ifndef mesh_H
#define mesh_H
#include <fstream>
#include <iostream>
#include <math.h>
#include "elements.H"


/**
 * \brief
 * project-wide namespace
 */
namespace meshing
{

/**
 * \brief
 * contains global list of hexes, vertices, arcs etc. and created final
 * blockMeshDict file
 */
class mesh{
 protected:
  int numberOfVertices_;
  point *verticesList_;

  int numberOfElements_;
  element **elementList_;

  int numberOfPatches_;
  patch * patchList_;

  int numberOfArcs_;
  arc *arcList_;

  float convertToMeters_;

  std::ofstream blockMeshFile_;

  /**
   * \brief
   * return number on the list (label) of a patch with a given name
   */
  int findPatchID(std::string name) const;

  /**
   * \brief
   * run patch::removeInternalFaces on all existing patches and message about
   * number of faces removed
   */
  std::string removeInternalFaces();

 public:
  ~mesh(){}

  mesh();

  /**
   * \brief
   * append element to list and execute element::assignLabels on it
   */
  void addElement(element&);

  /**
   * \brief
   * create a blockMeshDictFile based on stored geometry
   */
  void write();

  /**
   * \brief
   * return a reference to convertToMeters parameter
   */
  float &scale(){
      return convertToMeters_;
  };

  /**
   * \brief
   * return a string containing OpenFOAM blockMeshDict header
   */
  std::string header();

  /**
   * \brief
   * create an empty patch and add faces on a given plane to it
   */
  void addPatch(coordinate axis, double value, std::string name, patchType = p);

  /**
   * \brief
   * add faces on a given plane to selected patch
   */
  void addToPatch(coordinate axis, double value, std::string name);

  /**
   * \brief
   * separate part of a patch into new patch
   */
  void separateFromPatch
      (
          std::string target,
          coordinate axis,
          double minValue,
          double maxValue,
          std::string child2,
          patchType = p
      );
};

}//end namespace meshing
#endif


