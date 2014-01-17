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
    
    //remove internal faces from all patches
    std::cout << removeInternalFaces();

    std::string boundaries = "";
    for(int i=0; i<numberOfPatches_; i++){
        boundaries += patchList_[i].write();
    }
    //blockMeshFile_ << "patches\n(\n" << boundaries << ");\n\n";
    blockMeshFile_ << "boundary\n(\n" << boundaries << ");\n\n";
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
    std::cout << "\n\ncurrent number of patches: " << numberOfPatches_ << std::endl;
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

std::string mesh::removeInternalFaces()
{
    std::ostringstream ss;
    int counter;

    ss << "removing internal faces from patches: \n";

    for(int i = 0; i < numberOfPatches_; i++) 
    {
        counter = patchList_[i].removeInternalFaces();
        ss << "\t" << counter << " faces removed from patch: " << patchList_[i].name() << "\n";
    }

    return ss.str();
}


void mesh::separateFromPatch
(
    std::string target,
    coordinate axis,
    double minValue,
    double maxValue,
    std::string name,
    patchType pType
)
{
    removeInternalFaces();
    int patchID = findPatchID(target);
    std::cout << "\n\nSeparating patch from patch with label: " << patchID << std::endl;
    std::cout << "current number of patches: " << numberOfPatches_ << std::endl;
    std::cout << "Adding new patch: " << name << "\t..." << std::flush;
    patch * pList = new patch[numberOfPatches_ + 1];

    for(int i=0; i<numberOfPatches_; i++)
    {
        pList[i] = patchList_[i];
    }

    pList[numberOfPatches_++] = patch(name, pType);
    delete[] patchList_;

    patchList_ = pList;
    std::cout << "\tdone" << std::endl;


    const face * fList = patchList_[patchID].faceList();
    int n = patchList_[patchID].faceN();

    point p;
    int pLabel;

    face * faceToMove = new face[n];

    //how many faces were moved
    int counter = 0;
    //if all four vetices of a face are in correct region then move it
    int verts;

    double rho, angle;
    for(int i = 0; i< n; i++)
    {
        verts = 0;
        faceToMove[i] = face(-1,-1,-1,-1);
        for(int j = 0; j < 4; j++)
        {
            pLabel = fList[i].label(j);
            p = verticesList_[pLabel];

            switch (axis)
            {

                case x:
                    if
                    ( 
                        p.x() > minValue - constant::tolerance 
                        && p.x() < maxValue + constant::tolerance 
                    )
                    {
                        verts++;
                    }
                    break;
                    //-------------------------------------------

                case y:
                    if
                    ( 
                        p.y() > minValue - constant::tolerance 
                        && p.y() < maxValue + constant::tolerance 
                    )
                    {
                        verts++;
                    }
                    break;
                    //-------------------------------------------

                case z:
                    if
                    ( 
                        p.z() > minValue - constant::tolerance 
                        && p.z() < maxValue + constant::tolerance 
                    )
                    {
                        verts++;
                    }
                    break;
                    //-------------------------------------------

                case r:
                    rho = sqrt 
                        ( 
                            pow( p.x() , 2)
                            + pow( p.y() , 2)
                        );

                    if
                    ( 
                        rho > minValue - constant::tolerance 
                        && rho < maxValue + constant::tolerance 
                    )
                    {
                        verts++;
                    }
                    break;
                    //-------------------------------------------

                case theta:
                    angle = 0;
                    rho = sqrt 
                        ( 
                            pow( p.x() , 2)
                            + pow( p.y() , 2)
                        );
                    if( p.x() >= 0 ){
                        if(p.x() == 0 && p.y() == 0)
                        {
                            angle = 0;
                        }else
                        {
                            angle = asin( p.y() / rho);
                        }
                    }else if( p.x() < 0 )
                    {
                        angle = - asin( p.y() / rho ) + M_PI;
                    }

                    if
                    ( 
                        angle > minValue - constant::tolerance 
                        && angle < maxValue + constant::tolerance 
                    )
                    {
                        verts++;
                    }
                    break;
                    //-------------------------------------------
            }

            if(verts == 4)
            {
                faceToMove[i] = fList[i];
                counter++;
            }
        }

    }
    std::cout << "number of faces marked to move: " << counter << "\n";

    for(int i = 0; i < n; i++)
    {
        if(faceToMove[i].label(0) >= 0)
        {
            patchList_[numberOfPatches_ - 1].addFace(faceToMove[i]);
            patchList_[patchID].removeFace(faceToMove[i]);
        }
    }

}


}//end namespace meshing

