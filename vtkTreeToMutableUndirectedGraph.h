/*
This class takes in a vtkDataSet, creates a fully connected graph on the points, then computes the Euclidean Minimum Spanning Tree on the fully connected graph.
*/

#ifndef __vtkTreeToMutableUndirectedGraph_h
#define __vtkTreeToMutableUndirectedGraph_h

#include <vtkSmartPointer.h>
#include "vtkGraphAlgorithm.h" //superclass

class vtkGraph;

class vtkTreeToMutableUndirectedGraph : public vtkGraphAlgorithm
{
  public:
    static vtkTreeToMutableUndirectedGraph *New();
    vtkTypeRevisionMacro(vtkTreeToMutableUndirectedGraph, vtkGraphAlgorithm);
    void PrintSelf(ostream &os, vtkIndent indent);
    
  protected:
    vtkTreeToMutableUndirectedGraph(){}
    ~vtkTreeToMutableUndirectedGraph(){}
    
    int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *); //the function that makes this class work with the vtk pipeline
    int RequestDataObject(vtkInformation *, vtkInformationVector **, vtkInformationVector *); //the function that makes this class work with the vtk pipeline
    
  private:
    
};

#endif

