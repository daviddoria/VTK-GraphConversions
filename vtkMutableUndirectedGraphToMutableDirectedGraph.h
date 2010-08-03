/*
This class takes in a vtkDataSet, creates a fully connected graph on the points, then computes the Euclidean Minimum Spanning Tree on the fully connected graph.
*/

#ifndef __vtkMutableUndirectedGraphToMutableDirectedGraph_h
#define __vtkMutableUndirectedGraphToMutableDirectedGraph_h

#include <vtkSmartPointer.h>
#include "vtkGraphAlgorithm.h" //superclass

class vtkGraph;

class vtkMutableUndirectedGraphToMutableDirectedGraph : public vtkGraphAlgorithm
{
  public:
    static vtkMutableUndirectedGraphToMutableDirectedGraph *New();
    vtkTypeRevisionMacro(vtkMutableUndirectedGraphToMutableDirectedGraph, vtkGraphAlgorithm);
    void PrintSelf(ostream &os, vtkIndent indent);
    
  protected:
    vtkMutableUndirectedGraphToMutableDirectedGraph(){}
    ~vtkMutableUndirectedGraphToMutableDirectedGraph(){}
    
    int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *); //the function that makes this class work with the vtk pipeline
    int RequestDataObject(vtkInformation *, vtkInformationVector **, vtkInformationVector *); //the function that makes this class work with the vtk pipeline
    
  private:
    
};

#endif

