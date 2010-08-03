#include <vtkIdList.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkDoubleArray.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkGraph.h>
#include <vtkMutableUndirectedGraph.h>
#include <vtkEdgeListIterator.h>

#include <vtkExecutive.h>
#include <vtkInformation.h>
#include <vtkInformationVector.h>
#include <vtkObjectFactory.h> //for new() macro

#include "vtkTreeToMutableUndirectedGraph.h"

vtkCxxRevisionMacro(vtkTreeToMutableUndirectedGraph, "$Revision: 1.70 $");
vtkStandardNewMacro(vtkTreeToMutableUndirectedGraph);

int vtkTreeToMutableUndirectedGraph::RequestDataObject(vtkInformation *vtkNotUsed(request),
                                         vtkInformationVector **inputVector,
                                         vtkInformationVector *outputVector)
{
  
  vtkMutableUndirectedGraph* output = 0;
  output = vtkMutableUndirectedGraph::New();
    
  this->GetExecutive()->SetOutputData(0, output);
  output->Delete();

  return 1;
}

int vtkTreeToMutableUndirectedGraph::RequestData(vtkInformation *vtkNotUsed(request),
                                         vtkInformationVector **inputVector,
                                         vtkInformationVector *outputVector)
{
  // get the info objects
  vtkInformation *inInfo = inputVector[0]->GetInformationObject(0);
  vtkInformation *outInfo = outputVector->GetInformationObject(0);

  // get the input and ouptut
  vtkGraph* input = vtkGraph::SafeDownCast(
      inInfo->Get(vtkDataObject::DATA_OBJECT()));
  //vtkGraph* output = vtkGraph::SafeDownCast(outInfo->Get(vtkDataObject::DATA_OBJECT()));
  vtkMutableUndirectedGraph* output = vtkMutableUndirectedGraph::SafeDownCast(outInfo->Get(vtkDataObject::DATA_OBJECT()));
  
  //add vertices to MUG
  for(unsigned int i = 0; i < input->GetNumberOfVertices(); i++)
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
  
  output->SetPoints(input->GetPoints());
    
  /*
  vtkSmartPointer<vtkDoubleArray> weights = vtkDoubleArray::SafeDownCast(input->GetEdgeData()->GetArray("Weights"));
  if(weights)
    {
    output->GetEdgeData()->AddArray(weights);
    }
  */
  return 1;
}

void vtkTreeToMutableUndirectedGraph::PrintSelf(ostream &os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
}
