 

#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <iostream>

#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>
#include <glm/glm.hpp>  
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <memory>

#include "cones.h"
#include "shader.h"
#include "shape.h"
#include "setup.h"
#include "texture.h"

std::shared_ptr<Shape> base ;
std::shared_ptr<Texture> texture ;

// ----------------------------------------------------------
// Initial foldup rotation
// ----------------------------------------------------------
float rotate_fold=0.f ;  // rotation is 0..1.0  (scale later)  

float fold_delta = -0.005f ;

// Handle rotating the cone side curl rate
void fold_rotate() {
    rotate_fold += fold_delta ;
    if( rotate_fold >= 1.f ) {
      rotate_fold = 1.f ;
      fold_delta = -0.005f ;
    }
    if( rotate_fold <= 0.f ) {
      rotate_fold = 0.f ;
      fold_delta = 0.005f ;
    }
}


// ----------------------------------------------------------
// makeBase() function
// 
// vertices should hold ( num_triangles + 2 ) points
// each point is 3 floats (x,y,z)
//
// e.g.
//  float vertices [ 3*(num_triangles+2) ] ;
//
// ----------------------------------------------------------
void make_base( float *vertices, int num_triangles ) {

  // clear buffer
  for (size_t i=0; i< BASE_NUM_VERTICES*Shape::FloatsPerVertex; i++) {
    vertices[i] = 0.f;
  }
  vertices[2] = base_height ;  // 1st point at [0,0,10]
  // 1st vertex texture is at 0.0

  float angle = 0.0 ;
  int xIndex = 0 ;
  int nIndex = 3 ;  // normal offset
  int sIndex = 6 ;  // texture S,T offset
  float vChange = 1.f / (num_triangles+1) ;
  float vValue = 0.0f ;

  float x1 = base_radius * std::cos( angle ) ;
  float y1 = base_radius * std::sin( angle ) ;
  glm::vec3 v0( 0, 0, base_height ) ;

  for( int i=0 ; i<num_triangles ; i++ ) {

    angle = angle + base_angle_step ;

    float x2 = base_radius * std::cos( angle ) ;
    float y2 = base_radius * std::sin( angle ) ;

    glm::vec3 v1( x1, y1, 0 ) ;
    glm::vec3 v2( x2, y2, 0 ) ;

    x1 = x2 ;
    y1 = y2 ;

    glm::vec3 a = v0 - v1 ;
    glm::vec3 b = v0 - v2 ;
    // normal is cross product of any two (non-colinear) vectors in a plane
    glm::vec3 normal = glm::normalize( glm::cross( a, b ) ) ;

    // Center of the circle
    vertices[xIndex] = v0.x ;
    vertices[xIndex + 1] = v0.y ;
    vertices[xIndex + 2] = v0.z ;

    vValue += vChange ;
    vertices[sIndex] = vValue ;
    vertices[sIndex + 1] = 0.f ;

    vertices[nIndex] = normal.x ;
    vertices[nIndex + 1] = normal.y ;
    vertices[nIndex + 2] = normal.z ;

    xIndex += Shape::FloatsPerVertex ;
    nIndex += Shape::FloatsPerVertex ;
    sIndex += Shape::FloatsPerVertex ;

    // Bottom Left
    vertices[xIndex] = v1.x ;
    vertices[xIndex + 1] = v1.y ;
    vertices[xIndex + 2] = v1.z ;

    vValue -= vChange ;
    vertices[sIndex] = vValue ;
    vertices[sIndex + 1] = 1.f ;

    vertices[nIndex] = normal.x ;
    vertices[nIndex + 1] = normal.y ;
    vertices[nIndex + 2] = normal.z ;

    xIndex += Shape::FloatsPerVertex ;
    nIndex += Shape::FloatsPerVertex ;
    sIndex += Shape::FloatsPerVertex ;

    // Bottom Right
    vertices[xIndex] = v2.x ;
    vertices[xIndex + 1] = v2.y ;
    vertices[xIndex + 2] = v2.z ;

    vValue += vChange + vChange ;
    vertices[sIndex] = vValue ;
    vertices[sIndex + 1] = 1.f ;

    vertices[nIndex] = normal.x ;
    vertices[nIndex + 1] = normal.y ;
    vertices[nIndex + 2] = normal.z ;

    xIndex += Shape::FloatsPerVertex ;
    nIndex += Shape::FloatsPerVertex ;
    sIndex += Shape::FloatsPerVertex ;
  }
}

// ----------------------------------------------------------
// display() Callback function
// ----------------------------------------------------------
void display(){

  if( !freeze ) { 
 // Rotate scene
    rotate_x += 0.002f ;
    rotate_y += 0.003f ;
    rotate_z += 0.005f ;
  }
// update fold - if at either end of fold
// pause fold effects temporarily
  if( !pause_clock ) {
    fold_rotate() ;
  } 
  
  //  Clear screen ard Z-buffer
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
 
  // Model rotation
  glm::mat4 matrixModel = glm::rotate( glm::mat4(1.0), -rotate_y, glm::vec3(0.0, 1.0, 0.0) );
  matrixModel = glm::rotate( matrixModel, -rotate_z, glm::vec3(0.0, 0.0, 1.0) );
  matrixModel = glm::rotate( matrixModel, -rotate_x, glm::vec3(1.0, 0.0, 0.0) );

  base->draw( matrixCamera, matrixModel ) ;
  // -----------------------------
  // S I D E S
  float fan_angle = 0.0 ;
  float curl_angle = 0.0 ;


  glFlush();
  glutSwapBuffers();

  glutPostRedisplay();
}
 

 
// ----------------------------------------------------------
// main() function
// ----------------------------------------------------------
int main(int argc, char* argv[]) {
 
  setup( display, argc, argv ) ;

  texture = std::make_shared<Texture>( "textures/bark.jpg" ) ;
  glm::vec3 lightPos( -2.f, 1.f, 0.f ) ;
  std::shared_ptr<Shader> baseShader = std::make_shared<Shader>( "shaders/shader.vs", "shaders/shader.fs" ); 
  baseShader->use() ;
  baseShader->setVec3( "lightPos", glm::value_ptr( lightPos ) ) ;

  float vertices[ Shape::FloatsPerVertex * BASE_NUM_VERTICES ] ; 
  make_base( vertices, BASE_NUM_SIDES ) ;
  
  base = std::make_shared<Shape>( baseShader, &vertices[0], BASE_NUM_VERTICES, texture ) ;

  //  Run display
  glutMainLoop() ;

  //  Return to OS
  return 0;
 
}
