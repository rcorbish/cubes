 

#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <iostream>

#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>
#include <glm/glm.hpp>  
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>

// extern unsigned int VBO, VAO, EBO;

// ----------------------------------------------------------
// Function Prototypes
// ----------------------------------------------------------
void display();
 
// ----------------------------------------------------------
// Global Variables
// ----------------------------------------------------------
float rotate_y=0; 
float rotate_x=0;
float rotate_z=0;
float rotate_fold=0;
float fold_delta = 0.005f ;
// ----------------------------------------------------------
// display() Callback function
// ----------------------------------------------------------
void display(){
 
  float x,y,z ;
  rotate_x += 0.003f ;
  rotate_y += 0.005f ;
  rotate_z += 0.002f ;
  rotate_fold += fold_delta ;
  
  if( rotate_fold >= (float)M_PI_2 || rotate_fold <= 0.f ) {
    fold_delta = -fold_delta ;
  }
  
  // std::cout << rotate_fold << std::endl ;

  //  Clear screen and Z-buffer
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
 
  // Reset transformations
  glLoadIdentity(); 

  glm::mat4 matrixModelL = glm::lookAt( glm::vec3(0, 0, 0.4 ), glm::vec3(0, 0.0, 0.0), glm::vec3(0, 1, 0) ) ;
  glm::mat4 matrixModelY = glm::rotate( glm::mat4(1.0f), -rotate_y, glm::vec3(0.0, 1.0, 0.0) );
  glm::mat4 matrixModelZ = glm::rotate( glm::mat4(1.0f), -rotate_z, glm::vec3(0.0, 0.0, 1.0) );
  glm::mat4 matrixModelX = glm::rotate( glm::mat4(1.0f), -rotate_x, glm::vec3(1.0, 0.0, 0.0) );
  glm::mat4 matrixModel = matrixModelL  * matrixModelZ * matrixModelX * matrixModelY ;

  glMultMatrixf( glm::value_ptr(matrixModel) );

  constexpr double LEN = 0.25 ;
  constexpr double WID = 0.25 ;
  constexpr double HEI = 0.25 ;

  // RHS  ***************************  

  glPushMatrix() ;
  // glLoadIdentity(); 

  glm::mat4 matrixModelY1 = glm::rotate( glm::mat4(1.0f), rotate_fold, glm::vec3(0.0, 1.0, 0.0) );
  glm::mat4 matrixModelT1 = glm::translate( glm::mat4(1.0f), glm::vec3( WID/2.0, 0.0, HEI) );
  glm::mat4 matrixModel1 = matrixModelT1 * matrixModelY1 ;

  glMultMatrixf( glm::value_ptr(matrixModel1) );

  glBegin(GL_POLYGON);
  glColor3f(   0.3,  0.1,  0.1 );  
  glVertex3f(  0.0, -HEI/2.0,  0 );
  glVertex3f(  0.0,  HEI/2.0,  0 );      
  glVertex3f(  WID,  HEI/2.0,  0 );      
  glVertex3f(  WID, -HEI/2.0,  0 );      
  glEnd();
  glPopMatrix() ;

  // LHS  ***************************  

  // glLoadIdentity(); 
  glPushMatrix() ;

  glm::mat4 matrixModelY2 = glm::rotate( glm::mat4(1.0f), -rotate_fold, glm::vec3(0.0, 1.0, 0.0) );
  glm::mat4 matrixModelT2 = glm::translate( glm::mat4(1.0f), glm::vec3( -WID/2.0, 0.0, HEI) );
  glm::mat4 matrixModel2 =  matrixModelT2 * matrixModelY2 ;

  glMultMatrixf( glm::value_ptr(matrixModel2) );

  glBegin(GL_POLYGON);
  glColor3f(   0.3,  0.3,  0.1 );  
  glVertex3f(  0.0, -HEI/2.0,  0 );
  glVertex3f(  0.0,  HEI/2.0,  0 );      
  glVertex3f(  -WID,  HEI/2.0,  0 );      
  glVertex3f(  -WID, -HEI/2.0,  0 );      
  glEnd();
  glPopMatrix() ;

  // TOP  ***************************  

  // glLoadIdentity(); 
  glPushMatrix() ;

  glm::mat4 matrixModelX3 = glm::rotate( glm::mat4(1.0f), -rotate_fold, glm::vec3(1.0, 0.0, 0.0) );
  glm::mat4 matrixModelT3 = glm::translate( glm::mat4(1.0f), glm::vec3( 0.0, HEI/2.0, LEN) );
  glm::mat4 matrixModel3 = matrixModelT3 * matrixModelX3 ;

  glMultMatrixf( glm::value_ptr(matrixModel3) );

  glBegin(GL_POLYGON);
  glColor3f(   0.1,  0.3,  0.1 );  
  glVertex3f( -WID/2.0, 0.0,  0 );
  glVertex3f( -WID/2.0, HEI,  0 );      
  glVertex3f(  WID/2.0, HEI,  0 );      
  glVertex3f(  WID/2.0, 0.0,  0 );      
  glEnd();
  glPopMatrix() ;

  // BOT  ***************************  

  // glLoadIdentity(); 
  glPushMatrix() ;

  glm::mat4 matrixModelX4 = glm::rotate( glm::mat4(1.0f), rotate_fold, glm::vec3(1.0, 0.0, 0.0) );
  glm::mat4 matrixModelT4 = glm::translate( glm::mat4(1.0f), glm::vec3( 0.0, -HEI/2.0, LEN) );
  glm::mat4 matrixModel4 = matrixModelT4 * matrixModelX4 ;

  glMultMatrixf( glm::value_ptr(matrixModel4) );

  glBegin(GL_POLYGON);
  glColor3f(   0.1,  0.2,  0.5 );  
  glVertex3f( -WID/2.0, 0.0,  0 );
  glVertex3f( -WID/2.0, -HEI,  0 );      
  glVertex3f(  WID/2.0, -HEI,  0 );      
  glVertex3f(  WID/2.0, 0.0,  0 );      
  glEnd();
  glPopMatrix() ;

  // BAK  ***************************  

  // glLoadIdentity(); 
  glPushMatrix() ;

  glm::mat4 matrixModelX5 = glm::rotate( glm::mat4(1.0f), 0.f, glm::vec3(1.0, 0.0, 0.0) );
  glm::mat4 matrixModelT5 = glm::translate( glm::mat4(1.0f), glm::vec3( 0.0, 0.0, 0.0) );
  glm::mat4 matrixModel5 =  matrixModelT5 * matrixModelX5 ;

  glMultMatrixf( glm::value_ptr(matrixModel5) );

  glBegin(GL_POLYGON);
  glColor3f(   0.5,  0.5,  0.5 );  
  glVertex3f( -WID/2.0, -HEI/2.0,  0 );
  glVertex3f( -WID/2.0,  HEI/2.0,  0 );      
  glVertex3f(  WID/2.0,  HEI/2.0,  0 );      
  glVertex3f(  WID/2.0, -HEI/2.0,  0 );      
  glEnd();
  glPopMatrix() ;

  // FRO  ***************************  

  // glLoadIdentity(); 
  glPushMatrix() ;

  glm::mat4 matrixModelX6 = glm::rotate( glm::mat4(1.0f), 0.f, glm::vec3(1.0, 0.0, 0.0) );
  glm::mat4 matrixModelT6 = glm::translate( glm::mat4(1.0f), glm::vec3( 0.0, 0.0, LEN) );
  glm::mat4 matrixModel6 = matrixModelT6 * matrixModelX6 ;

  glMultMatrixf( glm::value_ptr(matrixModel6) );

  glBegin(GL_POLYGON);
  glColor3f(   0.2,  0.3,  0.5 );  
  glVertex3f( -WID/2.0, -HEI/2.0,  0 );
  glVertex3f( -WID/2.0,  HEI/2.0,  0 );      
  glVertex3f(  WID/2.0,  HEI/2.0,  0 );      
  glVertex3f(  WID/2.0, -HEI/2.0,  0 );      
  glEnd();
  glPopMatrix() ;

  glFlush();
  glutSwapBuffers();

  glutPostRedisplay();
}
 

 
// ----------------------------------------------------------
// main() function
// ----------------------------------------------------------
int main(int argc, char* argv[]){
 
  //  Initialize GLUT and process user parameters
  glutInit(&argc,argv);
 
  //  Request double buffered true color window with Z-buffer
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
 
  // Create window
  glutCreateWindow("Orientation");
  glutReshapeWindow( 400, 400 );
  
  //  Enable Z-buffer depth test
  glEnable(GL_DEPTH_TEST);

  glEnable(GL_TEXTURE_2D) ;

  // Callback functions
  glutDisplayFunc(display);

  //  Pass control to GLUT for events
  glutMainLoop();
 
  //  Return to OS
  return 0;
 
}
