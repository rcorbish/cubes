 

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
#include "setup.h"
#include "texture.h"

#include "shapes/cone.h"

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

  texture = std::make_shared<Texture>( "textures/gold.jpg" ) ;

  glm::vec3 lightPos( -2.f, 1.f, 0.f ) ;
  std::shared_ptr<Shader> baseShader = std::make_shared<Shader>( "shaders/shader.vs", "shaders/shader.fs" ); 
  baseShader->use() ;
  baseShader->setVec3( "lightPos", glm::value_ptr( lightPos ) ) ;
  
  base = std::make_shared<Cone>( baseShader, 12, texture ) ;
  base->initVertexData() ;
  //  Run display
  glutMainLoop() ;

  //  Return to OS
  return 0;
 
}
