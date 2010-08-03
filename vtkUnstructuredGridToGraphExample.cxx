#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkImageData.h>
#include <vtkSphereSource.h>
#include <vtkGraphToPolyData.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkExtractEdges.h>

#include "vtkUnstructuredGridToGraph.h"

int main (int argc, char *argv[])
{
  
  vtkSmartPointer<vtkSphereSource> sphereSource = 
      vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();
   
  //need to convert sphere to UG before continuing
  
  /*
  vtkSmartPointer<vtkUnstructuredGridToGraph> unstructuredGridToGraphFilter = 
      vtkSmartPointer<vtkUnstructuredGridToGraph>::New();
  unstructuredGridToGraphFilter->SetInputConnection(input->GetProducerPort());
  unstructuredGridToGraphFilter->Update();
  
  vtkSmartPointer<vtkGraphToPolyData> graphToPolyDataFilter = 
      vtkSmartPointer<vtkGraphToPolyData>::New();
  graphToPolyDataFilter->SetInputConnection(unstructuredGridToGraphFilter->GetOutputPort());
  graphToPolyDataFilter->Update();
  
  vtkSmartPointer<vtkXMLPolyDataWriter> writer = 
      vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  writer->SetFileName("Graph.vtp");
  writer->SetInputConnection(graphToPolyDataFilter->GetOutputPort());
  writer->Write();
  */
  
  return EXIT_SUCCESS;
}
