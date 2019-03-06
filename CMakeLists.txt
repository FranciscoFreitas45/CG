cmake_minimum_required(VERSION 2.8)

set( CMAKE_CXX_FLAGS "-Wall -O3 -g" )

project(Engine)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(engine ./Engine/main.cpp ./Engine/tinyxml2.cpp ./src/Point.cpp ./src/Shape.cpp)
target_link_libraries(engine ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

project(GENERATOR)


add_executable(generator ./GENERATOR/main.cpp ./GENERATOR/box.cpp ./src/Point.cpp ./src/Shape.cpp GENERATOR/cone.cpp GENERATOR/cone.h GENERATOR/cylinder.cpp GENERATOR/cylinder.h GENERATOR/plane.cpp GENERATOR/plane.h GENERATOR/sphere.cpp GENERATOR/sphere.h GENERATOR/torus.cpp GENERATOR/torus.h)
