/*
This class takes in a vtkDataSet, creates a fully connected graph on the points, then computes the Euclidean Minimum Spanning Tree on the fully connected graph.
*/

#ifndef __vtkDirectedGraphToMutableDirectedGraph_h
#define __vtkDirectedGraphToMutableDirectedGraph_h

#include <vtkSmartPointer.h>
#include "vtkGraphAlgorithm.h" //superclass

class vtkGraph;

class vtkDirectedGraphToMutableDirectedGraph: public vtkGraphAlgorithm
{
  public:
    static vtkDirectedGraphToMutableDirectedGraph *New();
    vtkTypeRevisionMacro(vtkDirectedGraphToMutableDirectedGraph, vtkGraphAlgorithm);
    
  protected:
    vtkDirectedGraphToMutableDirectedGraph(){}
    ~vtkDirectedGraphToMutableDirectedGraph(){}
    
    int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *); //the function that makes this class work with the vtk pipeline
    int RequestDataObject(vtkInformation *, vtkInformationVector **, vtkInformationVector *); //the function that makes this class work with the vtk pipeline
    
  private:
    
};

#endif

