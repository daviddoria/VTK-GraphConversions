#include <vtkSmartPointer.h>
#include <vtkDoubleArray.h>
#include <vtkDataSetAttributes.h>
#include <vtkPoints.h>
#include <vtkMutableDirectedGraph.h>
#include <vtkMutableUndirectedGraph.h>
#include <vtkTree.h>

void MUGtoMDG();
void MDGtoMUG();

void TreetoMUG();

int main (int, char *[])
{
  MUGtoMDG();
  
  MDGtoMUG();
  
  TreetoMUG();
  
  return EXIT_SUCCESS;
}

void MUGtoMDG()
{
  std::cout << "Testing MUG to MDG" << std::endl;
  
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
  
  std::cout << "Output Type: " << mdg->GetClassName() << std::endl;
  std::cout << "MDG has " << mdg->GetNumberOfVertices() << " vertices." << std::endl;
  std::cout << "MDG has " << mdg->GetNumberOfEdges() << " edges." << std::endl;
  
}

void MDGtoMUG()
{
  std::cout << "Testing MDG to MUG" << std::endl;
  
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
  
  std::cout << "Output Type: " << mug->GetClassName() << std::endl;
  std::cout << "MDG has " << mug->GetNumberOfVertices() << " vertices." << std::endl;
  std::cout << "MDG has " << mug->GetNumberOfEdges() << " edges." << std::endl;
  
}


void TreetoMUG()
{
  std::cout << "Testing Tree to MUG" << std::endl;
  
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
  
  
  std::cout << "Output Type: " << mug->GetClassName() << std::endl;
  std::cout << "MDG has " << mug->GetNumberOfVertices() << " vertices." << std::endl;
  std::cout << "MDG has " << mug->GetNumberOfEdges() << " edges." << std::endl;
  
}
