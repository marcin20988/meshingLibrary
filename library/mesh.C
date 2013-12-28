#ifndef block_H
#define block_H
#include "mesh.H"
#include <iostream>

namespace meshing
{
mesh::mesh():
    numberOfVertices_(0),
    verticesList_(NULL),
    numberOfElements_(0),
    elementList_(NULL),
    numberOfPatches_(0),
    patchList_(NULL),
    numberOfArcs_(0),
    arcList_(NULL),
    convertToMeters_(1.0)
{
    blockMeshFile_.open("blockMeshDict",std::fstream::trunc);
};

void mesh::addElement(element& target)
{
    //create temporary list of elements and then repalce original list with the new one
    numberOfElements_++;
    element **elementListTemp = new element*[numberOfElements_];

    if(numberOfElements_ > 1){
        for(int i=0; i<numberOfElements_-1; i++){
            elementListTemp[i] = elementList_[i];
        }
        elementListTemp[numberOfElements_ - 1] = &target;
    }else{
        elementListTemp[0] = &target;
    }

    delete[] elementList_;
    elementList_ = elementListTemp;

    target.assignLabels(verticesList_,numberOfVertices_);

};

void mesh::write()
{

    std::cout << "Labeling arcs \n" << std::endl;
    for(int i=0; i < numberOfElements_; i++){
        elementList_[i] -> labelArcs(verticesList_,numberOfVertices_);
    }
    std::cout << "adding arcs to global list" << std::endl;
    int arcCount = 0;
    for(int i=0; i < numberOfElements_; i++){
        arcCount += elementList_[i] -> addArcsToList(arcList_, numberOfArcs_);
    }
    std::cout << "added " << arcCount << " arcs\n\n";

    std::cout << "Writing blockMeshDict:" << std::endl;
    std::cout << "number of elements in the mesh:" << numberOfElements_ << std::endl;
    std::cout << "\n{\n ";
    for(int i=0; i<numberOfElements_;  i++){
        std::cout << elementList_[i] -> name() << std::endl;
    }
    std::cout << "}\n\n";
    
    //-----------write header lines
    blockMeshFile_ << header();

    //-----------write convertToMeters
    blockMeshFile_ << "convertToMeters " << convertToMeters_ << ";\n";

    //-----------write vertices
    std::cout << "number of vertices in the mesh: " << numberOfVertices_ << std::endl;

    blockMeshFile_ << "\nvertices\n(\n";
    for(int i=0; i<numberOfVertices_;  i++){
        blockMeshFile_ << "\t(" << verticesList_[i].x() << " ";
        blockMeshFile_ << verticesList_[i].y() << " ";
        blockMeshFile_ << verticesList_[i].z() << " )\n";
    }
    blockMeshFile_ << ");\n\n";


    //-----------write edges
    std::cout << "number of edges in the mesh: " << numberOfArcs_ << std::endl;

    blockMeshFile_ << "\nedges\n(\n";
    std::string arcs = "";
    for(int i=0; i<numberOfArcs_;  i++){
        arcs += arcList_[i].write();
    }
    blockMeshFile_ << arcs;
    blockMeshFile_ << ");\n\n";

    //-----------write blocks
    std::string blocks = "";
    for(int i=0; i<numberOfElements_; i++){
        blocks += elementList_[i] -> write();
    }
    blockMeshFile_ << "blocks\n(\n" << blocks << ");\n\n";

    //-----------write boundaries
    std::string boundaries = "";
    for(int i=0; i<numberOfPatches_; i++){
        boundaries += patchList_[i].write();
    }
    blockMeshFile_ << "patches\n(\n" << boundaries << ");\n\n";
}

std::string mesh::header()
{
    std::string header_ = "/*--------------------------------*- C++ -*----------------------------------*\n";
    header_ +="| =========                 |                                                 |\n";
    header_ +="| \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox           |\n";
    header_ +="|  \\    /   O peration     | Version:  2.0.0                                 |\n";
    header_ +="|   \\  /    A nd           | Web:      www.OpenFOAM.com                      |\n";
    header_ +="|    \\/     M anipulation  |                                                 |\n";
    header_ +="*---------------------------------------------------------------------------*/\n";
    header_ +="FoamFile\n";
    header_ +="{\n";
    header_ +="    version     2.0;\n";
    header_ +="    format      ascii;\n";
    header_ +="    class       dictionary;\n";
    header_ +="    object      blockMeshDict;\n";
    header_ +="}\n";
    header_ +="// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //\n";

    return header_;
}

void mesh::addPatch(coordinate axis, double value, std::string name, patchType pType)
{
    std::cout << "current number of patches: " << numberOfPatches_ << std::endl;
    std::cout << "Adding new patch: " << name << "\t..." << std::flush;
    patch * pList = new patch[numberOfPatches_ + 1];

    for(int i=0; i<numberOfPatches_; i++)
    {
        pList[i] = patchList_[i];
    }

    pList[numberOfPatches_++] = patch(name,pType);
    delete[] patchList_;

    patchList_ = pList;
    std::cout << "\tdone" << std::endl;

    std::cout << "Adding faces to patch: " << name << "\t..." << std::flush;
    for(int i=0; i< numberOfElements_; i++)
    {
        elementList_[i] -> findFace(axis,value,patchList_[numberOfPatches_ - 1]);
    }
    std::cout << "\tdone" << std::endl;

};

int mesh::findPatchID(std::string name) const
{
    int i = 0;
    int label = -1;

    while(i < numberOfPatches_ && label < 0)
    {
        if(patchList_[i].name() == name) label = i;
        i++;
    }

    return label;

}

void mesh::addToPatch(coordinate axis, double value, std::string name)
{
    int label = findPatchID(name);

    //-1 returned if patch not found
    if(label <0) return;

    std::cout << "Adding faces to patch: " << name << "\t..." << std::flush;
    for(int i=0; i< numberOfElements_; i++)
    {
        elementList_[i] -> findFace(axis,value,patchList_[label]);
    }
    std::cout << "\tdone" << std::endl;

}

}//end namespace meshing
#endif

