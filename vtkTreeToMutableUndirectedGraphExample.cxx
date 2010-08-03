#include <vtkSmartPointer.h>
#include <vtkDoubleArray.h>
#include <vtkDataSetAttributes.h>
#include <vtkPoints.h>
#include <vtkMutableDirectedGraph.h>
#include <vtkTree.h>

#include "vtkTreeToMutableUndirectedGraph.h"

int main (int argc, char *argv[])
{
 //create a graph
  vtkSmartPointer<vtkMutableDirectedGraph> g = 
    vtkSmartPointer<vtkMutableDirectedGraph>::New();
 
  //add 4 vertices to the graph
  vtkIdType v1 = g->AddVertex();
  vtkIdType v2 = g->AddVertex();
  vtkIdType v3 = g->AddVertex();
  vtkIdType v4 = g->AddVertex();
 
  //add 3 edges to the graph
  g->AddEdge ( v1, v2 );
  g->AddEdge ( v1, v3 );
  g->AddEdge ( v1, v4 );
 
  //create 4 points - one for each vertex
  vtkSmartPointer<vtkPoints> points = 
      vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0.0, 0.0, 0.0);
  points->InsertNextPoint(1.0, 0.0, 0.0);
  points->InsertNextPoint(0.0, 1.0, 0.0);
  points->InsertNextPoint(0.0, 0.0, 2.0);
 
  //add the coordinates of the points to the graph
  g->SetPoints(points);
  
  vtkSmartPointer<vtkTree> tree = 
      vtkSmartPointer<vtkTree>::New();
  tree->CheckedShallowCopy(g);
  
  vtkSmartPointer<vtkTreeToMutableUndirectedGraph> treeToGraph = 
      vtkSmartPointer<vtkTreeToMutableUndirectedGraph>::New();
  treeToGraph->SetInput(tree);
  treeToGraph->Update();
  
  cout << "Output Type: " << treeToGraph->GetOutput()->GetClassName() << endl;
  
  return EXIT_SUCCESS;
}
