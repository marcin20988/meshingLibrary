#ifndef meshing_h
#define meshing_h

/*! \mainpage blockMeshDict preprocessing library
 * \author Marcin Traczyk <marcin.traczyk.88@gmail.com>
 *
 * \section intro_sec Introduction
 *
 * This library is aimed at significant reduction of time needed to prepare
 * blockMeshDict file for OpenFOAM through autmoatisation of basic (and most
 * time-consuming) steps during blockMeshDict preparation and reusability of
 * previously prepared geometries.
 *
 * \section features_sec Features
 * - automatic creation of vertice, hex, edge entries for every element
 * - automatic creation of global lists of vertice, hex, edge from created
 *   elements
 * - easy patch adding
 * - provision of basic elements needed to create more advanced geometries
 *
 * \section codeStructure_sec Code structure
 *
 * - in primitives.H classes for most basic components of mesh like points
 *   or hexes are defined
 * - in elements.H a base class meshing::element for simple geometrical elements
 *   is defined and a base class meshing::multiElement for more elements
 *   containing multiple other elements is defined
 * - in mesh.H mesh object that contains all global lists (arcs, vertices, hexes
 *   etc.) is defined
 * - directory derived/ contains actual elements inheriting from meshing::element
 *   or meshing::multiElement
 * - meshing.H contains all necessary includes
 *
 * \section howTo_sec How to use
 * - include meshing.H file
 * - create empty mesh object
 * - create elements
 * - add elements to mesh
 * - create patches
 * - write blockMeshDict file
 *
 * For more details see one of the examples provided with the source code.
 * 
 * \section contribute_sec Contribution
 *
 * If you not only use this library but also create new functionalities please
 * contribute so others also can benefit from your work.
 *
 */

#include "mesh.H"
#include "cylinder.H"
#include "block.H"
#include "pipes.H"


#endif
