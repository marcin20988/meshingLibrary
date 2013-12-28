#ifndef mesh_H
#define mesh_H
#include <fstream>
#include <iostream>
#include "elements.H"

class mesh{
 protected:
  int numberOfVertices_;
  point *verticesList_;

  int numberOfElements_;
  element **elementList_;

  int numberOfArcs_;
  arc *arcList_;

  float convertToMeters_;

  std::ofstream blockMeshFile_;

 public:
  ~mesh(){}

  mesh();

  void addElement(element&);

  void write();

  float &scale(){
      return convertToMeters_;
  };

  std::string header();

};

#endif
