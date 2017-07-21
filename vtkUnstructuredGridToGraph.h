//This class converts all of the points in a vtkUnstructuredGrid into vertices in a vtkGraph, and all
// "edges" in a vtkUnstructuredGrid (borders of cells (volumetric cells, polygons, and vtkLines)) into edges in a vtkGraph

#ifndef __vtkUnstructuredGridToGraph_h
#define __vtkUnstructuredGridToGraph_h

#include "vtkGraphAlgorithm.h"
#include "vtkSmartPointer.h"

class vtkUnstructuredGrid;
class vtkIdList;
class vtkGraph;

class vtkUnstructuredGridToGraph : public vtkGraphAlgorithm
{
public:
  vtkTypeMacro(vtkUnstructuredGridToGraph, vtkGraphAlgorithm);
  static vtkUnstructuredGridToGraph* New();
  
protected:
  vtkUnstructuredGridToGraph(){}
  ~vtkUnstructuredGridToGraph(){}
  
  virtual int FillInputPortInformation( int port, vtkInformation* info );
  
  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);
  
  int RequestDataObject(vtkInformation *vtkNotUsed(request),
                                         vtkInformationVector **inputVector,
                                         vtkInformationVector *outputVector);
  
  static void ProgressFunction(vtkObject* caller, long unsigned int eventId, void* clientData, void* callData);
  
private:
  vtkUnstructuredGridToGraph(const vtkUnstructuredGridToGraph&);  // Not implemented.
  void operator=(const vtkUnstructuredGridToGraph&);  // Not implemented.
  
  //should not be part of this class
  bool EdgeExists(vtkSmartPointer<vtkGraph> g, int pointID, int neighborID);  
  void GetConnectedVertices(vtkSmartPointer<vtkUnstructuredGrid> mesh, int seed, vtkSmartPointer<vtkIdList> connectedVertices);
};


#endif
