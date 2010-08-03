/*
This class takes in a vtkDataSet, creates a fully connected graph on the points, then computes the Euclidean Minimum Spanning Tree on the fully connected graph.
*/

#ifndef __vtkTreeToMutableDirectedGraph_h
#define __vtkTreeToMutableDirectedGraph_h

#include <vtkSmartPointer.h>
#include "vtkGraphAlgorithm.h" //superclass

class vtkGraph;

class vtkTreeToMutableDirectedGraph : public vtkGraphAlgorithm
{
  public:
    static vtkTreeToMutableDirectedGraph *New();
    vtkTypeRevisionMacro(vtkTreeToMutableDirectedGraph, vtkGraphAlgorithm);
    void PrintSelf(ostream &os, vtkIndent indent);
    
  protected:
    vtkTreeToMutableDirectedGraph(){}
    ~vtkTreeToMutableDirectedGraph(){}
    
    int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *); //the function that makes this class work with the vtk pipeline
    int RequestDataObject(vtkInformation *, vtkInformationVector **, vtkInformationVector *); //the function that makes this class work with the vtk pipeline
    
  private:
    
};

#endif

