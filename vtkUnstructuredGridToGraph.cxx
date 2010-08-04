#include "vtkUnstructuredGridToGraph.h"

#include "vtkGraphToPolyData.h"
#include "vtkFloatArray.h"
#include "vtkPointData.h"
#include "vtkExtractEdges.h"
#include "vtkLine.h"
#include "vtkObjectFactory.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkInformationVector.h"
#include "vtkInformation.h"
#include "vtkMutableUndirectedGraph.h"
#include "vtkAdjacentVertexIterator.h"
#include "vtkUnstructuredGrid.h"
#include "vtkSmartPointer.h"

vtkCxxRevisionMacro(vtkUnstructuredGridToGraph, "$Revision: 1.70 $");
vtkStandardNewMacro(vtkUnstructuredGridToGraph);

int vtkUnstructuredGridToGraph::RequestDataObject(vtkInformation *vtkNotUsed(request),
                                         vtkInformationVector **inputVector,
                                         vtkInformationVector *outputVector)
{
  vtkMutableUndirectedGraph* output = 0;
  output = vtkMutableUndirectedGraph::New();
    
  this->GetExecutive()->SetOutputData(0, output);
  output->Delete();

  return 1;
}

void vtkUnstructuredGridToGraph::ProgressFunction(vtkObject* caller, long unsigned int eventId, void* clientData, void* callData)
{
  vtkUnstructuredGridToGraph* filter = static_cast<vtkUnstructuredGridToGraph*>(caller);
  cout << "Progress: " << filter->GetProgress() << endl;
}

/*
//it works with or without this re-implementation
int vtkMeshToGraph::FillOutputPortInformation(
  int vtkNotUsed(port), vtkInformation* info)
{
  // now add our info
  info->Set(vtkDataObject::DATA_TYPE_NAME(), "vtkMutableUndirectedGraph");
  return 1;
}
*/

//----------------------------------------------------------------------------
int vtkUnstructuredGridToGraph::FillInputPortInformation(
                                            int vtkNotUsed(port), vtkInformation* info)
{
  info->Set(vtkAlgorithm::INPUT_REQUIRED_DATA_TYPE(), "vtkUnstructuredGrid");
  return 1;
}

int vtkUnstructuredGridToGraph::RequestData(
  vtkInformation *vtkNotUsed(request),
  vtkInformationVector **inputVector,
  vtkInformationVector *outputVector)
{
  // get the input and ouptut
  vtkInformation *inInfo = inputVector[0]->GetInformationObject(0);
  
  vtkUnstructuredGrid* input = vtkUnstructuredGrid::SafeDownCast(
      inInfo->Get(vtkDataObject::DATA_OBJECT()));
  
  std::cout << "vtkUnstructuredGridToGraph: Input has " << input->GetNumberOfPoints() << " points." << std::endl;
  
  vtkInformation *outInfo = outputVector->GetInformationObject(0);
  vtkMutableUndirectedGraph *output = vtkMutableUndirectedGraph::SafeDownCast(
		  outInfo->Get(vtkDataObject::DATA_OBJECT()));
  
  //add a vertex for every point
  for(vtkIdType i = 0; i < input->GetNumberOfPoints(); i++)
    {
    output->AddVertex();
    }
  
  //output->GetVertexData()->ShallowCopy(input->GetPointData());
  output->GetVertexData()->PassData(input->GetPointData());
    
  //add the edge between every point and every point connected to it (do not allow duplicates)
  for(vtkIdType i = 0; i < input->GetNumberOfPoints(); i++)
    {
    vtkSmartPointer<vtkIdList> idList = 
        vtkSmartPointer<vtkIdList>::New();
    this->GetConnectedVertices(input, i, idList);
    
    for(vtkIdType id = 0; id < idList->GetNumberOfIds(); id++)
      {
      if(!EdgeExists(output, i, idList->GetId(id)))
        {
        output->AddEdge(i, idList->GetId(id));
        }
      }  
    if(i%1000 == 0)
      {
      this->UpdateProgress(static_cast<double>(i)/input->GetNumberOfPoints());
      }
    }
  
  output->SetPoints(input->GetPoints());

  return 1;
}

bool vtkUnstructuredGridToGraph::EdgeExists(vtkSmartPointer<vtkGraph> g, int pointID, int neighborID)
{
  //check if the edge already exists
  vtkSmartPointer<vtkAdjacentVertexIterator> iterator = 
      vtkSmartPointer<vtkAdjacentVertexIterator>::New();
  g->GetAdjacentVertices(pointID, iterator);
  
  bool edgeExists = false;
  while(iterator->HasNext())
    {
      if(iterator->Next() == neighborID)
        {
        edgeExists = true;
        break;
        }
    }
  return edgeExists;
}


void vtkUnstructuredGridToGraph::GetConnectedVertices(vtkSmartPointer<vtkUnstructuredGrid> mesh, int seed, vtkSmartPointer<vtkIdList> connectedVertices)
{
  
  //get all cells that vertex 'seed' is a part of
  vtkSmartPointer<vtkIdList> cellIdList = 
      vtkSmartPointer<vtkIdList>::New();
  mesh->GetPointCells(seed, cellIdList);
  
  //cout << "There are " << cellIdList->GetNumberOfIds() << " cells that use point " << seed << endl;
      
  //loop through all the cells that use the seed point
  for(vtkIdType i = 0; i < cellIdList->GetNumberOfIds(); i++)
    {

    vtkCell* cell = mesh->GetCell(cellIdList->GetId(i));
    //cout << "The cell has " << cell->GetNumberOfEdges() << " edges." << endl;
    
    //if the cell doesn't have any edges, it is a line
    if(cell->GetNumberOfEdges() <= 0)
      {      
      //vtkLine* line = vtkLine::SafeDownCast(input->GetCell(i));
      vtkLine* line = vtkLine::SafeDownCast(mesh->GetCell(cellIdList->GetId(i)));

      //if the cell didn't have any edges, and it is not a line, it must be a vertex, so skip it
      if(!line)
        {
        continue;
        }
      else
        {
        int p0 = line->GetPointId(0);
        int p1 = line->GetPointId(1);
        if(p0 == seed)
          {
          connectedVertices->InsertNextId(p1);
          }
        else
          {
          connectedVertices->InsertNextId(p0);
          }
        
        }
        continue;
      }
      
    //if we get to here, the cell is a polygon, so extract its border edges
    for(vtkIdType e = 0; e < cell->GetNumberOfEdges(); e++)
      {
      vtkCell* edge = cell->GetEdge(e);

      vtkIdList* pointIdList = edge->GetPointIds();

      
      if(pointIdList->GetId(0) == seed || pointIdList->GetId(1) == seed)
        {
        if(pointIdList->GetId(0) == seed)
          {
          connectedVertices->InsertNextId(pointIdList->GetId(1));
          }
        else
          {
          connectedVertices->InsertNextId(pointIdList->GetId(0));
          }
        }
      }
    

    }

    //cout << "There are " << connectedVertices->GetNumberOfIds() << " points connected to point " << seed << endl;
}
