#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkImageData.h>
#include <vtkSphereSource.h>
#include <vtkGraphToPolyData.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkExtractEdges.h>

#include "vtkPolyDataToGraph.h"

int main (int argc, char *argv[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource = 
      vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();
    
  vtkSmartPointer<vtkExtractEdges> extractEdges = 
      vtkSmartPointer<vtkExtractEdges>::New();
  extractEdges->SetInputConnection(sphereSource->GetOutputPort());
  extractEdges->Update();
  
  vtkSmartPointer<vtkPolyData> input = extractEdges->GetOutput();
  
  {
  vtkSmartPointer<vtkXMLPolyDataWriter> writer = 
    vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  writer->SetFileName("Sphere.vtp");
  writer->SetInputConnection(input->GetProducerPort());
  writer->Write();
  }
  
  vtkSmartPointer<vtkPolyDataToGraph> polyDataToGraphFilter = 
      vtkSmartPointer<vtkPolyDataToGraph>::New();
  polyDataToGraphFilter->SetInputConnection(input->GetProducerPort());
  polyDataToGraphFilter->Update();
  
  vtkSmartPointer<vtkGraphToPolyData> graphToPolyDataFilter = 
      vtkSmartPointer<vtkGraphToPolyData>::New();
  graphToPolyDataFilter->SetInputConnection(polyDataToGraphFilter->GetOutputPort());
  graphToPolyDataFilter->Update();
  
  vtkSmartPointer<vtkXMLPolyDataWriter> writer = 
      vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  writer->SetFileName("Graph.vtp");
  writer->SetInputConnection(graphToPolyDataFilter->GetOutputPort());
  writer->Write();
  
  return EXIT_SUCCESS;
}
