cmake_minimum_required(VERSION 2.8)

project(engine)
add_executable(${PROJECT_NAME} ./Engine/main.cpp ./Engine/tinyxml2.cpp ./src/Point.cpp ./src/Point.h ./src/Shape.cpp ./src/Shape.h ./src/Group.cpp ./src/Group.h ./src/Action.cpp ./src/Action.h)
project(generator)
add_executable(${PROJECT_NAME} ./GENERATOR/main.cpp ./GENERATOR/box.cpp ./GENERATOR/bezier.cpp ./GENERATOR/bezier.h ./src/Point.cpp ./src/Shape.cpp GENERATOR/cone.cpp GENERATOR/cone.h GENERATOR/cylinder.cpp GENERATOR/cylinder.h GENERATOR/plane.cpp GENERATOR/plane.h GENERATOR/sphere.cpp GENERATOR/sphere.h GENERATOR/torus.cpp GENERATOR/torus.h src/Group.cpp src/Group.h src/Action.cpp src/Action.h)

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

if  (WIN32)

	message(STATUS "GLUT_DIR set to: " ${GLUT_DIR})
	set(GLUT_DIR "" CACHE PATH "Path to GLUT folder")
	if (NOT EXISTS "${GLUT_DIR}/GL/glut.h" OR NOT EXISTS "${GLUT_DIR}/glut32.lib")
		message(ERROR ": GLUT not found")
	endif (NOT EXISTS "${GLUT_DIR}/GL/glut.h" OR NOT EXISTS "${GLUT_DIR}/glut32.lib")
	include_directories(${GLUT_DIR})
	link_directories(${GLUT_DIR})
	target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_DIR}/glut32.lib )
  target_link_libraries(engine ${OPENGL_LIBRARIES} ${GLUT_DIR}/glut32.lib )
	if (EXISTS "${GLUT_DIR}/glut32.dll")
		file(COPY ${GLUT_DIR}/glut32.dll DESTINATION ${CMAKE_BINARY_DIR})
	endif(EXISTS "${GLUT_DIR}/glut32.dll")
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

else (WIN32) #Linux and Mac

	set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} Wno-deprecated")
	find_package(GLUT REQUIRED)
	include_directories(${GLUT_INCLUDE_DIR})
	link_directories(${GLUT_LIBRARY_DIRS})
	add_definitions(${GLUT_DEFINITIONS})

if (NOT APPLE)
  find_package(GLEW REQUIRED)
  include_directories(${GLEW_INCLUDE_DIRS})
  link_libraries(${GLEW_LIBRARIES})
endif(NOT APPLE)

	target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLEW_LIBRARY} )
	target_link_libraries(engine ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLEW_LIBRARY} )
	if(NOT GLUT_FOUND)
	   message(ERROR ": GLUT not found!")
	endif(NOT GLUT_FOUND)

endif(WIN32)
