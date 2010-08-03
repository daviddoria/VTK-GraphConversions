#include "vtkDirectedGraphToMutableDirectedGraph.h"

#include <vtkIdList.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkDoubleArray.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkGraph.h>
#include <vtkMutableDirectedGraph.h>
#include <vtkMutableUndirectedGraph.h>
#include <vtkEdgeListIterator.h>

#include <vtkExecutive.h>
#include <vtkInformation.h>
#include <vtkInformationVector.h>
#include <vtkObjectFactory.h> //for new() macro

vtkCxxRevisionMacro(vtkDirectedGraphToMutableDirectedGraph, "$Revision: 1.70 $");
vtkStandardNewMacro(vtkDirectedGraphToMutableDirectedGraph);

int vtkDirectedGraphToMutableDirectedGraph::RequestDataObject(vtkInformation *vtkNotUsed(request),
                                         vtkInformationVector **inputVector,
                                         vtkInformationVector *outputVector)
{
  
  vtkMutableDirectedGraph* output = 0;
  output = vtkMutableDirectedGraph::New();
    
  this->GetExecutive()->SetOutputData(0, output);
  output->Delete();

  return 1;
}

int vtkDirectedGraphToMutableDirectedGraph::RequestData(vtkInformation *vtkNotUsed(request),
                                         vtkInformationVector **inputVector,
                                         vtkInformationVector *outputVector)
{
  // get the info objects
  vtkInformation *inInfo = inputVector[0]->GetInformationObject(0);
  vtkInformation *outInfo = outputVector->GetInformationObject(0);

  // get the input and ouptut
  vtkDirectedGraph* input = vtkDirectedGraph::SafeDownCast(
      inInfo->Get(vtkDataObject::DATA_OBJECT()));
  
  vtkMutableDirectedGraph* output = vtkMutableDirectedGraph::SafeDownCast(outInfo->Get(vtkDataObject::DATA_OBJECT()));
  
  //add vertices to MDG
  for(vtkIdType i = 0; i < input->GetNumberOfVertices(); i++)
    {
    output->AddVertex();
    }
  
  output->GetVertexData()->PassData(input->GetVertexData());
  
  vtkSmartPointer<vtkEdgeListIterator> edgeIterator = 
      vtkSmartPointer<vtkEdgeListIterator>::New();
  input->GetEdges(edgeIterator);
  while(edgeIterator->HasNext())
    {
    vtkEdgeType edge = edgeIterator->Next();
    output->AddEdge(edge.Source, edge.Target);
    }
  
  if(input->GetPoints())
    {
    output->SetPoints(input->GetPoints());
    }
    
  /*
  //TODO: must ensure are in the right order because the edge order could be changed via the edgeIterator above
  vtkSmartPointer<vtkDoubleArray> weights = 
      vtkDoubleArray::SafeDownCast(input->GetEdgeData()->GetArray("Weights"));
  if(weights)
    {
    output->GetEdgeData()->AddArray(weights);
    }
  */
  return 1;
}
