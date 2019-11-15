 

#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <iostream>

#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>
#include <glm/glm.hpp>  
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>

// ----------------------------------------------------------
// Function Prototypes
// ----------------------------------------------------------
void display();
 
// ----------------------------------------------------------
// Initial scene rotations
// ----------------------------------------------------------
float rotate_y=0; 
float rotate_x=0;
float rotate_z=0;

// ----------------------------------------------------------
// Initial foldup rotation
// ----------------------------------------------------------
float rotate_fold=0.f ;

float fold_delta = rotate_fold <= 0.005f ? 0.005f : -0.0005f ;
constexpr int PAUSE_LEN = 600 ;
int pause_clock = PAUSE_LEN ;

// ----------------------------------------------------------
// display() Callback function
// ----------------------------------------------------------
void display(){
 
 // Rotate scene
  rotate_x += 0.01f ;
  rotate_y += 0.003f ;
  rotate_z += 0.02f ;
// update fold - if at either end of fold
// pause fold effects temporarily
  if( pause_clock < 0 ) {
    rotate_fold += fold_delta ;
    if( rotate_fold >= (float)M_PI_2 || rotate_fold <= 0.f ) {
      fold_delta = -fold_delta ;
      pause_clock = PAUSE_LEN ;
    }
  } else {
    pause_clock-- ;
  }

  //  Clear screen ard Z-buffer
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
 
  // Reset transformations
  glLoadIdentity(); 

  // Handle scene rotation
  glm::mat4 matrixModelL = glm::lookAt( glm::vec3(0, 0, -0.5 ), glm::vec3(0, 0.0, 0.0), glm::vec3(0, 1, 0) ) ;
  glm::mat4 matrixModelY = glm::rotate( glm::mat4(1.0f), -rotate_y, glm::vec3(0.0, 1.0, 0.0) );
  glm::mat4 matrixModelZ = glm::rotate( glm::mat4(1.0f), -rotate_z, glm::vec3(0.0, 0.0, 1.0) );
  glm::mat4 matrixModelX = glm::rotate( glm::mat4(1.0f), -rotate_x, glm::vec3(1.0, 0.0, 0.0) );
  glm::mat4 matrixModel = matrixModelL  * matrixModelZ * matrixModelX * matrixModelY ;

  // radius of full base
  constexpr float base_radius = 2.0 ;

  // -----------------------------
  // B A S E
  glColor3f(   0.1,  0.1,  0.3 );  

  glMultMatrixf( glm::value_ptr(matrixModel) );
  
  glColor3f(0.5,0.5,0.2);
  glBegin(GL_TRIANGLE_FAN);

glVertex3f( 0 , 0 , 0.00 );
glVertex3f( 2.0 , 0.0 , 0.00 );
glVertex3f( 1.902113032590307 , 0.6180339887498948 , 0.00 );
glVertex3f( 1.618033988749895 , 1.1755705045849463 , 0.00 );
glVertex3f( 1.1755705045849463 , 1.618033988749895 , 0.00 );
glVertex3f( 0.6180339887498949 , 1.902113032590307 , 0.00 );
glVertex3f( 1.2246467991473532e-16 , 2.0 , 0.00 );
glVertex3f( -0.6180339887498947 , 1.9021130325903073 , 0.00 );
glVertex3f( -1.175570504584946 , 1.618033988749895 , 0.00 );
glVertex3f( -1.6180339887498947 , 1.1755705045849465 , 0.00 );
glVertex3f( -1.902113032590307 , 0.618033988749895 , 0.00 );
glVertex3f( -2.0 , 2.4492935982947064e-16 , 0.00 );
glVertex3f( -1.9021130325903073 , -0.6180339887498946 , 0.00 );
glVertex3f( -1.6180339887498951 , -1.175570504584946 , 0.00 );
glVertex3f( -1.1755705045849465 , -1.6180339887498947 , 0.00 );
glVertex3f( -0.6180339887498951 , -1.902113032590307 , 0.00 );
glVertex3f( -3.6739403974420594e-16 , -2.0 , 0.00 );
glVertex3f( 0.6180339887498945 , -1.9021130325903073 , 0.00 );
glVertex3f( 1.1755705045849458 , -1.6180339887498951 , 0.00 );
glVertex3f( 1.6180339887498947 , -1.1755705045849467 , 0.00 );
glVertex3f( 1.902113032590307 , -0.6180339887498952 , 0.00 );
glVertex3f( 2.0 , -4.898587196589413e-16 , 0.00 );

  glEnd();

  // -----------------------------
  // S I D E S

  glPushMatrix() ;

  glm::mat4 matrixModelY1 = glm::rotate( glm::mat4(1.0f), rotate_fold, glm::vec3(0.0, 1.0, 0.0) );
  glm::mat4 matrixModelT1 = glm::translate( glm::mat4(1.0f), glm::vec3( -base_radius, 0.0, 0) );
  glm::mat4 matrixModel1 = matrixModelT1 * matrixModelY1 ;

  glMultMatrixf( glm::value_ptr(matrixModel1) );

  glColor3f(0.2,0.2,0.2);
  glBegin(GL_TRIANGLE_FAN);

  glVertex3f( -5 , 0 , 0.00 );
  glVertex3f( 0.0 , 0.0 , 0.00 );
  glVertex3f( -0.17037086855465855 , 1.2940952255126037 , 0.00 );
  glVertex3f( -0.6698729810778064 , 2.4999999999999996 , 0.00 );
  glVertex3f( -1.4644660940672622 , 3.5355339059327373 , 0.00 );
  glVertex3f( -2.4999999999999996 , 4.330127018922193 , 0.00 );
  glVertex3f( -3.7059047744873954 , 4.829629131445341 , 0.00 );
  glVertex3f( -4.999999999999998 , 5.0 , 0.00 );
  glVertex3f( -6.294095225512602 , 4.829629131445342 , 0.00 );
  glVertex3f( -7.499999999999999 , 4.330127018922194 , 0.00 );
  glVertex3f( -8.535533905932738 , 3.5355339059327378 , 0.00 );
  glVertex3f( -9.330127018922195 , 2.4999999999999996 , 0.00 );
  glVertex3f( -9.82962913144534 , 1.2940952255126028 , 0.00 );
  glVertex3f( -10.0 , -1.6081226496766366e-15 , 0.00 );

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

  glViewport( 0.f, 0.0f, 20.f, 20.f ); // specifies the part of the window to which OpenGL will draw (in pixels), convert from normalised to pixels
  glMatrixMode( GL_PROJECTION ); // projection matrix defines the properties of the camera that views the objects in the world coordinate frame. Here you typically set the zoom factor, aspect ratio and the near and far clipping planes
  glLoadIdentity( ); // replace the current matrix with the identity matrix and starts us a fresh because matrix transforms such as glOrpho and glRotate cumulate, basically puts us at (0, 0, 0)
  glOrtho( -10.f, 10.f, -10.f, 10.f, -10.f, 10.f ); // essentially set coordinate system
  glMatrixMode( GL_MODELVIEW ); // (default matrix mode) modelview matrix defines how your objects are transformed (meaning translation, rotation and scaling) in your world

  // Callback functions
  glutDisplayFunc(display);

  //  Pass control to GLUT for events
  glutMainLoop();
 
  //  Return to OS
  return 0;
 
}
