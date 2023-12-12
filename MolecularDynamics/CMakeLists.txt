cmake_minimum_required(VERSION 3.17)

project(SimpleMolecularDynamics
	VERSION 1.0
	LANGUAGES CXX
	)
SET( CMAKE_EXPORT_COMPILE_COMMANDS ON )
include(FetchContent)

IF( EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json" )
  EXECUTE_PROCESS( COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
    ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
  )
ENDIF()
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O0 -Wall -Wpedantic -Wextra")
SET(CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-undefined")

find_package(OpenGL REQUIRED)
find_package(Eigen3 REQUIRED)
set(GLUT_INCLUDE_PATH "/usr/include/GL/" )
set(GLUT_LIBRARY "/usr/lib/x86_64-linux-gnu/libglut.so" )

link_directories(${Eigen_INCLUDE_DIRS})
add_executable(md	
	${PROJECT_SOURCE_DIR}/src/AndersonThermostat.cpp
	${PROJECT_SOURCE_DIR}/src/CalculatorFactory.cpp
	${PROJECT_SOURCE_DIR}/src/LJCalculator.cpp
	${PROJECT_SOURCE_DIR}/src/MDParticle.cpp
	${PROJECT_SOURCE_DIR}/src/MDSimulation.cpp
	${PROJECT_SOURCE_DIR}/src/glutSetup2d.cpp
	${PROJECT_SOURCE_DIR}/src/utility.cpp
	${PROJECT_SOURCE_DIR}/src/StructureLogger.cpp
	${PROJECT_SOURCE_DIR}/src/main.cpp)

#target_compile_options(md PUBLIC -DNDEBUG)
target_include_directories(md PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(md PUBLIC ${Eigen_LIBRARIES} ${OPENGL_LIBRARY} ${GLUT_LIBRARY})
