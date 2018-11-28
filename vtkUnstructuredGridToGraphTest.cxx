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

  vtkSmartPointer<vtkUnstructuredGridToGraph> unstructuredGridToGraphFilter =
      vtkSmartPointer<vtkUnstructuredGridToGraph>::New();
  unstructuredGridToGraphFilter->SetInputConnection(delaunay->GetOutputPort());
  unstructuredGridToGraphFilter->Update();

  if(sphereSource->GetOutput()->GetNumberOfPoints() != unstructuredGridToGraphFilter->GetOutput()->GetNumberOfVertices())
    {
    std::cerr << "Number of points " << sphereSource->GetOutput()->GetNumberOfPoints()
      << " does not match number of vertices " << unstructuredGridToGraphFilter->GetOutput()->GetNumberOfVertices() << " !";
    return EXIT_FAILURE;
    }

  if(unstructuredGridToGraphFilter->GetOutput()->GetNumberOfEdges() != 234)
    {
    std::cerr << "Number of edges " << unstructuredGridToGraphFilter->GetOutput()->GetNumberOfEdges()
      << " is not correct (should be 234)!" << std::endl;
    return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}
