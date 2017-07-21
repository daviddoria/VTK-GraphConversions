/*=========================================================================

  Program:   Visualization Toolkit
  Module:    TestTriangle.cxx

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

// .NAME 
// .SECTION Description
// This program tests vtkGraph and subclasses

#include "vtkGraph.h"
#include "vtkMutableUndirectedGraph.h"
#include "vtkUndirectedGraph.h"
#include "vtkMutableDirectedGraph.h"
#include "vtkDirectedGraph.h"
#include <vtkstd/limits>
#include "vtkSmartPointer.h"
#include "vtkPoints.h"
#include "vtkTree.h"

namespace //anonymous
{
  bool MUGtoMDG()
  {
    //create a graph
    vtkSmartPointer<vtkMutableUndirectedGraph> mug =
      vtkSmartPointer<vtkMutableUndirectedGraph>::New();

    //add 4 vertices to the graph
    vtkIdType v1 = mug->AddVertex();
    vtkIdType v2 = mug->AddVertex();
    vtkIdType v3 = mug->AddVertex();
    vtkIdType v4 = mug->AddVertex();

    //add 3 edges to the graph
    mug->AddEdge ( v1, v2 );
    mug->AddEdge ( v1, v3 );
    mug->AddEdge ( v1, v4 );

    //create 4 points - one for each vertex
    vtkSmartPointer<vtkPoints> points =
        vtkSmartPointer<vtkPoints>::New();
    points->InsertNextPoint(0.0, 0.0, 0.0);
    points->InsertNextPoint(1.0, 0.0, 0.0);
    points->InsertNextPoint(0.0, 1.0, 0.0);
    points->InsertNextPoint(0.0, 0.0, 2.0);

    //add the coordinates of the points to the graph
    mug->SetPoints(points);

    vtkSmartPointer<vtkMutableDirectedGraph> mdg =
        vtkSmartPointer<vtkMutableDirectedGraph>::New();
    mug->ToDirectedGraph(mdg);

    if(mdg->GetNumberOfVertices() != mug->GetNumberOfVertices())
      {
      std::cerr << "MUGtoMDG: number of vertices does not match!" << std::endl;
      return false;
      }
    if(mdg->GetNumberOfEdges() != mug->GetNumberOfEdges())
      {
      std::cerr << "MUGtoMDG: number of vertices does not match!" << std::endl;
      return false;
      }
    return true;
  }

  bool MDGtoMUG()
  {
    //create a graph
    vtkSmartPointer<vtkMutableDirectedGraph> mdg =
      vtkSmartPointer<vtkMutableDirectedGraph>::New();

    //add 4 vertices to the graph
    vtkIdType v1 = mdg->AddVertex();
    vtkIdType v2 = mdg->AddVertex();
    vtkIdType v3 = mdg->AddVertex();
    vtkIdType v4 = mdg->AddVertex();

    //add 3 edges to the graph
    mdg->AddEdge ( v1, v2 );
    mdg->AddEdge ( v1, v3 );
    mdg->AddEdge ( v1, v4 );

    //create 4 points - one for each vertex
    vtkSmartPointer<vtkPoints> points =
        vtkSmartPointer<vtkPoints>::New();
    points->InsertNextPoint(0.0, 0.0, 0.0);
    points->InsertNextPoint(1.0, 0.0, 0.0);
    points->InsertNextPoint(0.0, 1.0, 0.0);
    points->InsertNextPoint(0.0, 0.0, 2.0);

    //add the coordinates of the points to the graph
    mdg->SetPoints(points);

    vtkSmartPointer<vtkMutableUndirectedGraph> mug =
        vtkSmartPointer<vtkMutableUndirectedGraph>::New();
    mdg->ToUndirectedGraph(mug);

    if(mdg->GetNumberOfVertices() != mug->GetNumberOfVertices())
      {
      std::cerr << "MUGtoMDG: number of vertices does not match!" << std::endl;
      return false;
      }
    if(mdg->GetNumberOfEdges() != mug->GetNumberOfEdges())
      {
      std::cerr << "MUGtoMDG: number of vertices does not match!" << std::endl;
      return false;
      }
    return true;
  }


  bool TreetoMUG()
  {
    //create a graph
    vtkSmartPointer<vtkMutableDirectedGraph> mdg =
      vtkSmartPointer<vtkMutableDirectedGraph>::New();

    //add 4 vertices to the graph
    vtkIdType v1 = mdg->AddVertex();
    vtkIdType v2 = mdg->AddVertex();
    vtkIdType v3 = mdg->AddVertex();
    vtkIdType v4 = mdg->AddVertex();

    //add 3 edges to the graph
    mdg->AddEdge ( v1, v2 );
    mdg->AddEdge ( v1, v3 );
    mdg->AddEdge ( v1, v4 );

    //create 4 points - one for each vertex
    vtkSmartPointer<vtkPoints> points =
        vtkSmartPointer<vtkPoints>::New();
    points->InsertNextPoint(0.0, 0.0, 0.0);
    points->InsertNextPoint(1.0, 0.0, 0.0);
    points->InsertNextPoint(0.0, 1.0, 0.0);
    points->InsertNextPoint(0.0, 0.0, 2.0);

    //add the coordinates of the points to the graph
    mdg->SetPoints(points);

    vtkSmartPointer<vtkTree> tree =
      vtkSmartPointer<vtkTree>::New();
    tree->CheckedShallowCopy(mdg);

    vtkSmartPointer<vtkMutableUndirectedGraph> mug =
        vtkSmartPointer<vtkMutableUndirectedGraph>::New();
    tree->ToUndirectedGraph(mug);

    if(mdg->GetNumberOfVertices() != mug->GetNumberOfVertices())
      {
      std::cerr << "MUGtoMDG: number of vertices does not match!" << std::endl;
      return false;
      }
    if(mdg->GetNumberOfEdges() != mug->GetNumberOfEdges())
      {
      std::cerr << "MUGtoMDG: number of vertices does not match!" << std::endl;
      return false;
      }
    return true;
  }
} //end anonymous namespace

int TestGraph(int,char *[])
{
  if(MUGtoMDG() && MDGtoMUG() && TreetoMUG())
    {
    return EXIT_SUCCESS;
    }

  return EXIT_FAILURE;
}
