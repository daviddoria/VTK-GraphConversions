#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkImageData.h>
#include <vtkSphereSource.h>
#include <vtkGraphToPolyData.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkExtractEdges.h>

#include "vtkPolyDataToGraph.h"

void ExampleWithMesh();
void ExampleWithEdges();

int main (int argc, char *argv[])
{
  ExampleWithMesh();
  ExampleWithEdges();
  
  return EXIT_SUCCESS;
}

void ExampleWithMesh()
{
 vtkSmartPointer<vtkSphereSource> sphereSource =
      vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

  vtkSmartPointer<vtkPolyData> input = sphereSource->GetOutput();

  vtkSmartPointer<vtkXMLPolyDataWriter> inputWriter =
    vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  inputWriter->SetFileName("meshInput.vtp");
  inputWriter->SetInputData(input);
  inputWriter->Write();

  vtkSmartPointer<vtkPolyDataToGraph> polyDataToGraphFilter =
      vtkSmartPointer<vtkPolyDataToGraph>::New();
  polyDataToGraphFilter->SetInputData(input);
  polyDataToGraphFilter->Update();

  vtkSmartPointer<vtkGraphToPolyData> graphToPolyDataFilter =
      vtkSmartPointer<vtkGraphToPolyData>::New();
  graphToPolyDataFilter->SetInputConnection(polyDataToGraphFilter->GetOutputPort());
  graphToPolyDataFilter->Update();

  vtkSmartPointer<vtkXMLPolyDataWriter> writer =
      vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  writer->SetFileName("meshGraph.vtp");
  writer->SetInputConnection(graphToPolyDataFilter->GetOutputPort());
  writer->Write();
}

void ExampleWithEdges()
{
 vtkSmartPointer<vtkSphereSource> sphereSource =
      vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

  vtkSmartPointer<vtkExtractEdges> extractEdges =
      vtkSmartPointer<vtkExtractEdges>::New();
  extractEdges->SetInputConnection(sphereSource->GetOutputPort());
  extractEdges->Update();

  vtkSmartPointer<vtkPolyData> input = extractEdges->GetOutput();

  vtkSmartPointer<vtkXMLPolyDataWriter> inputWriter =
    vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  inputWriter->SetFileName("edgesInput.vtp");
  inputWriter->SetInputData(input);
  inputWriter->Write();

  vtkSmartPointer<vtkPolyDataToGraph> polyDataToGraphFilter =
      vtkSmartPointer<vtkPolyDataToGraph>::New();
  polyDataToGraphFilter->SetInputData(input);
  polyDataToGraphFilter->Update();

  vtkSmartPointer<vtkGraphToPolyData> graphToPolyDataFilter =
      vtkSmartPointer<vtkGraphToPolyData>::New();
  graphToPolyDataFilter->SetInputConnection(polyDataToGraphFilter->GetOutputPort());
  graphToPolyDataFilter->Update();

  vtkSmartPointer<vtkXMLPolyDataWriter> writer =
      vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  writer->SetFileName("edgesGraph.vtp");
  writer->SetInputConnection(graphToPolyDataFilter->GetOutputPort());
  writer->Write();
}
