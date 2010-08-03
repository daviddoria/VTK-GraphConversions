/*
This class takes in a vtkDataSet, creates a fully connected graph on the points, then computes the Euclidean Minimum Spanning Tree on the fully connected graph.
*/

#ifndef __vtkMutableDirectedGraphToMutableUndirectedGraph_h
#define __vtkMutableDirectedGraphToMutableUndirectedGraph_h

#include <vtkSmartPointer.h>
#include "vtkGraphAlgorithm.h" //superclass

class vtkGraph;

class vtkMutableDirectedGraphToMutableUndirectedGraph : public vtkGraphAlgorithm
{
  public:
    static vtkMutableDirectedGraphToMutableUndirectedGraph *New();
    vtkTypeRevisionMacro(vtkMutableDirectedGraphToMutableUndirectedGraph, vtkGraphAlgorithm);
    
  protected:
    vtkMutableDirectedGraphToMutableUndirectedGraph(){}
    ~vtkMutableDirectedGraphToMutableUndirectedGraph(){}
    
    int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *); //the function that makes this class work with the vtk pipeline
    int RequestDataObject(vtkInformation *, vtkInformationVector **, vtkInformationVector *); //the function that makes this class work with the vtk pipeline
    
  private:
    
};

#endif

