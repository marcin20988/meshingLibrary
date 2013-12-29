#ifndef mesh_H
#define mesh_H
#include <fstream>
#include <iostream>
#include "elements.H"

namespace meshing
{

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

  int findPatchID(std::string name) const;

  std::string removeInternalFaces();

 public:
  ~mesh(){}

  mesh();

  void addElement(element&);

  void write();

  float &scale(){
      return convertToMeters_;
  };

  std::string header();

  void addPatch(coordinate axis, double value, std::string name, patchType = p);

  void addToPatch(coordinate axis, double value, std::string name);
};

}//end namespace meshing
#endif


