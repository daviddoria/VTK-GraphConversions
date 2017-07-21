#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkImageData.h>
#include <vtkSphereSource.h>
#include <vtkGraphToPolyData.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkXMLUnstructuredGridWriter.h>
#include <vtkDelaunay3D.h>

#include "vtkUnstructuredGridToGraph.h"

int main (int argc, char *argv[])
{
  
  vtkSmartPointer<vtkSphereSource> sphereSource =
      vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

  vtkSmartPointer<vtkDelaunay3D> delaunay =
    vtkSmartPointer<vtkDelaunay3D>::New();
  delaunay->SetInputConnection(sphereSource->GetOutputPort());
  delaunay->Update();

  vtkSmartPointer<vtkXMLUnstructuredGridWriter> ugWriter =
    vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
  ugWriter->SetFileName("ug.vtu");
  ugWriter->SetInputConnection(delaunay->GetOutputPort());
  ugWriter->Write();
  
  vtkSmartPointer<vtkUnstructuredGridToGraph> unstructuredGridToGraphFilter = 
      vtkSmartPointer<vtkUnstructuredGridToGraph>::New();
  unstructuredGridToGraphFilter->SetInputConnection(delaunay->GetOutputPort());
  unstructuredGridToGraphFilter->Update();
  
  vtkSmartPointer<vtkGraphToPolyData> graphToPolyDataFilter = 
      vtkSmartPointer<vtkGraphToPolyData>::New();
  graphToPolyDataFilter->SetInputConnection(unstructuredGridToGraphFilter->GetOutputPort());
  graphToPolyDataFilter->Update();
  
  vtkSmartPointer<vtkXMLPolyDataWriter> pdWriter =
      vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  pdWriter->SetFileName("ugGraph.vtp");
  pdWriter->SetInputConnection(graphToPolyDataFilter->GetOutputPort());
  pdWriter->Write();
  
  return EXIT_SUCCESS;
}
