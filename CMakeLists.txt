cmake_minimum_required(VERSION 2.6)

PROJECT(GraphConversions)
ENABLE_TESTING()

FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})

ADD_EXECUTABLE(NewGraphConversions NewGraphConversions.cxx)
TARGET_LINK_LIBRARIES(NewGraphConversions ${VTK_LIBRARIES} )


ADD_EXECUTABLE(vtkUnstructuredGridToGraphExample vtkUnstructuredGridToGraphExample.cxx
vtkUnstructuredGridToGraph.cxx)
TARGET_LINK_LIBRARIES(vtkUnstructuredGridToGraphExample ${VTK_LIBRARIES} )

ADD_EXECUTABLE(vtkPolyDataToGraphExample vtkPolyDataToGraphExample.cxx
vtkPolyDataToGraph.cxx)
TARGET_LINK_LIBRARIES(vtkPolyDataToGraphExample ${VTK_LIBRARIES} )


ADD_EXECUTABLE(vtkUnstructuredGridToGraphTest vtkUnstructuredGridToGraphTest.cxx
vtkUnstructuredGridToGraph.cxx)
TARGET_LINK_LIBRARIES(vtkUnstructuredGridToGraphTest ${VTK_LIBRARIES}  )
ADD_TEST(vtkUnstructuredGridToGraphTest vtkUnstructuredGridToGraphTest)

ADD_EXECUTABLE(vtkPolyDataToGraphTest vtkPolyDataToGraphTest.cxx
vtkPolyDataToGraph.cxx)
TARGET_LINK_LIBRARIES(vtkPolyDataToGraphTest ${VTK_LIBRARIES} )
ADD_TEST(vtkPolyDataToGraphTest vtkPolyDataToGraphTest)