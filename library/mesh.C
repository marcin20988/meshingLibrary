#ifndef block_H
#define block_H
#include "mesh.H"
#include <iostream>

mesh::mesh():
    numberOfVertices_(0),
    verticesList_(NULL),
    numberOfElements_(0),
    elementList_(NULL),
    numberOfArcs_(0),
    arcList_(NULL),
    convertToMeters_(1.0)
{
    blockMeshFile_.open("blockMeshDict",std::fstream::trunc);
};

void mesh::addElement(element& target){
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

    //TODO:complete arc-writing function
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

    //-----------write boundaries TODO
    std::string boundaries = "";
    /*for(int i=0; i<numberOfElements_; i++){
        blocks += elementList_[i].write();
    }*/
    blockMeshFile_ << "boundary\n(\n" << boundaries << ");\n\n";
}

std::string mesh::header(){
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
#endif
