cmake_minimum_required (VERSION 3.4)

project (cubes LANGUAGES CXX)

find_package( OpenGL REQUIRED COMPONENTS OpenGL )
find_package( GLUT REQUIRED )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}  )

add_compile_options( -std=c++17 )
add_compile_options( -g )
if( NO_HARDWARE )
    add_compile_options( -D NO_HARDWARE=1 )
endif( NO_HARDWARE )

include_directories( ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} )

add_executable( cubes cubes.cpp )
add_executable( cones cones.cpp )

target_link_libraries( cubes ${OPENGL_LIBRARIES} ${GLUT_glut_LIBRARY} )
target_link_libraries( cones ${OPENGL_LIBRARIES} ${GLUT_glut_LIBRARY} )
