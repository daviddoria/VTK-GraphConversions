//This class converts all of the points in a vtkPolyData into vertices in a vtkGraph, and all
// "edges" in a vtkPolyData (borders of polygons and vtkLines) into edges in a vtkGraph

#ifndef __vtkPolyDataToGraph_h
#define __vtkPolyDataToGraph_h

#include "vtkGraphAlgorithm.h"
#include "vtkSmartPointer.h"

class vtkPolyData;
class vtkIdList;

class vtkPolyDataToGraph : public vtkGraphAlgorithm  
{
public:
  
  vtkTypeMacro(vtkPolyDataToGraph, vtkGraphAlgorithm);
  static vtkPolyDataToGraph *New();
  
protected:
  vtkPolyDataToGraph(){}
  ~vtkPolyDataToGraph(){}
  
  virtual int FillInputPortInformation( int port, vtkInformation* info );
  
  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);
  
  int RequestDataObject(vtkInformation *vtkNotUsed(request),
                                         vtkInformationVector **inputVector,
                                         vtkInformationVector *outputVector);
  
  
private:
  vtkPolyDataToGraph(const vtkPolyDataToGraph&);  // Not implemented.
  void operator=(const vtkPolyDataToGraph&);  // Not implemented.
  
  //should not be part of this class
  bool EdgeExists(vtkSmartPointer<vtkGraph> g, int pointID, int neighborID);  
  void GetConnectedVertices(vtkSmartPointer<vtkPolyData> mesh, int seed, vtkSmartPointer<vtkIdList> connectedVertices);
};


#endif
