 

#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <iostream>

#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>
#include <glm/glm.hpp>  
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"

#define SHOW_HINTS

constexpr float SCREEN_WIDTH = 15.f ;
constexpr float SCREEN_HEIGHT = 15.f ;
constexpr float SCREEN_DEPTH = 15.f ;
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

float tmpx = 0.00001 ;
float tmpy = 0 ;

// ----------------------------------------------------------
// Circle data
// ----------------------------------------------------------
constexpr int BASE_N = 30 ;
constexpr int SIDES_N = 3 ;
constexpr double circle_fraction = 0.3333333 ;
constexpr double side_fan_angle_step = circle_fraction * 2.0 * M_PI / SIDES_N ;
constexpr double side_curl_angle_step = 2.0 * M_PI / SIDES_N ;
constexpr double base_radius = 2.0 ;
constexpr double radius = 4.0 ;
constexpr double cx = -radius ;
constexpr double cy = 0 ;
constexpr float base_angle_step = M_PI * 2.0 / BASE_N ;

// ----------------------------------------------------------
// Initial foldup rotation
// ----------------------------------------------------------
float rotate_fold=0.f ;  // rotation is 0..1.0  (scale later)  

float fold_delta = -0.005f ;
bool pause_clock = false ;
bool freeze = false ;

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

// What to do in case of key press
void keypress_func( unsigned char key, int x, int y ) {
  if( key == 'x' ) {
    pause_clock = !pause_clock ;
  }
  if( key == 'f' ) {
    freeze = !freeze ;
  }
  if( key == 'w' ) {
    tmpy += 0.01 ;
    std::cout << tmpx << "," << tmpy << std::endl ;
  }
  if( key == 's' ) {
    tmpy -= 0.01 ;
    std::cout << tmpx << "," << tmpy << std::endl ;
  }
  if( key == 'a' ) {
    tmpx -= 0.01 ;
    std::cout << tmpx << "," << tmpy << std::endl ;
  }
  if( key == 'd' ) {
    tmpx += 0.01 ;
    std::cout << tmpx << "," << tmpy << std::endl ;
  }

  if( key == '1' ) {
    rotate_y=0 ; 
    rotate_x=0 ;
    rotate_z=0 ;
  }
  if( key == '2' ) {
    rotate_y=0 ; 
    rotate_x=M_PI_4 ;
    rotate_z=0 ;
  }
  if( key == '3' ) {
    rotate_y=M_PI_4 ; 
    rotate_x=M_PI_4 ;
    rotate_z=0 ;
  }
  if( key == '4' ) {
    rotate_y=M_PI_4 ; 
    rotate_x=0 ;
    rotate_z=0 ;
  }
  if( key == 'q' ) {
    exit( 0 ) ;
  }
  if( key == ' ' ) {
    fold_rotate() ;
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
  glMultMatrixf( glm::value_ptr(matrixModel) );

  float angle = 0.0 ;

  glColor3f(0.75,0.4,0.2);
  glBegin(GL_TRIANGLE_FAN);

  glVertex3f( 0.f , 0.f , 0.00 );  // Centre

  // define triangle base points
  for( int i=0 ; i<=BASE_N ; i++ ) {
    float x = base_radius * std::cos( angle ) ;
    float y = base_radius * std::sin( angle ) ;
    angle = angle + base_angle_step ;
    glVertex3f( x, y, 0.00 ) ;
  }
  glEnd();

  // -----------------------------
  // S I D E S

  float fan_angle = 0.0 ;
  float curl_angle = 0.0 ;

  glColor3f( 0.2, 0.5, 0.5 );
  glBegin(GL_TRIANGLE_FAN);

  glVertex3f( 0-radius-base_radius , 0.f , 0.00 );  // Centre

  // define triangle base points
  for( int i=0 ; i<=SIDES_N ; i++ ) {
    float x = radius * std::cos( fan_angle / circle_fraction ) ;
    float y = radius * std::sin( fan_angle / circle_fraction ) ;
    float z = base_radius * std::cos( curl_angle ) ;
    fan_angle += side_fan_angle_step ;
    curl_angle += side_curl_angle_step ;
    glVertex3f( x-radius-base_radius, y, 5 ) ;
  }
  glEnd();


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
 
  Shader theShader("shader.vs", "shader.fs"); // you can name your shader files however you like

  // Create window
  glutCreateWindow("Orientation");
  glutReshapeWindow( 400, 400 );

  // Add keypress listener for current window
  glutKeyboardFunc( keypress_func ) ;

  //  Enable Z-buffer depth test
  glEnable(GL_DEPTH_TEST);

  glEnable(GL_TEXTURE_2D) ;

  glViewport( 0.f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT ); // specifies the part of the window to which OpenGL will draw (in pixels), convert from normalised to pixels
  glMatrixMode( GL_PROJECTION ); // projection matrix defines the properties of the camera that views the objects in the world coordinate frame. Here you typically set the zoom factor, aspect ratio and the near and far clipping planes
  glLoadIdentity( ); // replace the current matrix with the identity matrix and starts us a fresh because matrix transforms such as glOrpho and glRotate cumulate, basically puts us at (0, 0, 0)
  glOrtho( -SCREEN_WIDTH/2.f, SCREEN_WIDTH/2.f, -SCREEN_HEIGHT/2.f, SCREEN_HEIGHT/2.f, -SCREEN_DEPTH/2.f, SCREEN_DEPTH/2.f ); // essentially set coordinate system
  glMatrixMode( GL_MODELVIEW ); // (default matrix mode) modelview matrix defines how your objects are transformed (meaning translation, rotation and scaling) in your world

  // Callback functions
  glutDisplayFunc(display);

  theShader.use() ;
  
  //  Pass control to GLUT for events
  glutMainLoop();
 
  //  Return to OS
  return 0;
 
}
