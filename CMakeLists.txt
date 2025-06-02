cmake_minimum_required(VERSION "3.12") 

project("GL3DModeler")

set(CMAKE_CXX_STANDARD 17)

if (MSVC)
set(CMAKE_CXX_FLAGS "/permissive- /EHsc /WX")
add_definitions(-D_WIN32_WINNT=0x0A00)
elseif(APPLE)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
endif()

include_directories(
"${CMAKE_SOURCE_DIR}"
"$ENV{X_INCL_DIR}"
"$ENV{BOOST_INCL_DIR}"
"$ENV{FREEGLUT_INCL_DIR}"
)

link_directories(
"$ENV{X_LINK_DIR}"
"$ENV{BOOST_LINK_DIR}" 
"$ENV{FREEGLUT_LINK_BIN}"
"$ENV{FREEGLUT_LINK_LIB}"
)

add_executable("${PROJECT_NAME}" 
"main.cpp" 
"gl/GLBackend.cpp" 
"gl/GLBackendEmitters.h" "gl/GLBackendEmitters.cpp" 
"gl/GLBackendWindow.h" "gl/GLBackendWindow.cpp"
"gl/GLEntity.cpp" 
"gl/GLEntityTask.cpp"
"modeler/Modeler.cpp"
"modeler/Grid.cpp" "modeler/Grid.h"   
"modeler/PointLight.cpp" "modeler/PointLight.h" 
"modeler/UserInterface.cpp" "modeler/UserInterface.h" 
"modeler/ModelerConsumers.h" "modeler/ModelerConsumers.cpp" 
)

if (MSVC)
target_link_libraries("${PROJECT_NAME}" 
"DatabaseAdapters"
"Entities" 
"Events"
"FilesystemAdapters" 
"Resources" 
"bcrypt"
"boost_filesystem$ENV{BOOST_LIB_SUFFIX}"
"freeglutd"
)
elseif (APPLE)
target_link_libraries("${PROJECT_NAME}" 
"DatabaseAdapters"
"Entities" 
"Events"
"FilesystemAdapters" 
"GLUT::GLUT" 
"OpenGL::GL"
"Resources" 
"boost_filesystem$ENV{BOOST_LIB_SUFFIX}"
)
endif()

