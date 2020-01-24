
#include "cone.h"

// ----------------------------------------------------------
// Base Circle data
// ----------------------------------------------------------
constexpr int BASE_NUM_SIDES = 32 ;
constexpr int BASE_NUM_VERTICES = ( BASE_NUM_SIDES * 3 ) ;
constexpr double base_radius = 8.0 ;
constexpr double base_height = 8.0 ;

// ----------------------------------------------------------
// Sides data
// ----------------------------------------------------------
constexpr int SIDES_N = 3 ;
constexpr double circle_fraction = 0.3333333 ;
// constexpr double side_fan_angle_step = circle_fraction * 2.0 * M_PI / SIDES_N ;
constexpr double side_curl_angle_step = 2.0 * M_PI / SIDES_N ;
constexpr double radius = 4.0 ;
constexpr double cx = -radius ;
constexpr double cy = 0 ;


void Cone::initVertexData() {
    size_t verticesSize = numVertices * BytesPerVertex ;

    float vertexData[ numVertices * FloatsPerVertex ] ;
    makeVertexData( vertexData ) ;
    glGenVertexArrays( 1, &VAO ) ;
    glGenBuffers( 1, &VBO ) ;
    
    glBindVertexArray( VAO ) ;
    glBindBuffer( GL_ARRAY_BUFFER, VBO ) ;
    glBufferData( GL_ARRAY_BUFFER, verticesSize, vertexData, GL_STATIC_DRAW ) ;

    glEnableVertexAttribArray( 0 ) ;  // location(0) = aPos
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, BytesPerVertex, PositionOffset ) ;

    glEnableVertexAttribArray( 1 ) ;  // location(1) = normal
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, BytesPerVertex, NormalOffset ) ;

    glEnableVertexAttribArray( 2 ) ;  // location(2) = texture
    glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, BytesPerVertex, TextureOffset ) ;

    this->indices = new unsigned short[ numVertices ] ;

    for( unsigned short i=0 ; i<numVertices ; i++ ) {
        this->indices[i] = i ;
    }
}
// ----------------------------------------------------------
// makeBase() function
// 
// vertices should hold ( num_triangles + 2 ) points
// each point is 3 floats (x,y,z)
//
// e.g.
//  float vertices [ 3*num_triangles ] ;
//
// ----------------------------------------------------------
void Cone::makeVertexData( float *vertices ) {

  float base_angle_step = M_PI * 2.0 / ( numVertices / 3 ) ;

  // clear buffer
  for (size_t i=0; i< numVertices*Shape::FloatsPerVertex; i++) {
    vertices[i] = 0.f;
  }
  vertices[2] = base_height ;  // 1st point at [0,0,10]
  // 1st vertex texture is at 0.0

  float angle = 0.0 ;
  int xIndex = 0 ;
  int nIndex = 3 ;  // normal offset
  int sIndex = 6 ;  // texture S,T offset
  float vChange = .2f  ;
  float vValue = 0.0f ;

  float x1 = base_radius * std::cos( angle ) ;
  float y1 = base_radius * std::sin( angle ) ;
  glm::vec3 v0( 0, 0, base_height ) ;

  for( int i=0 ; i<numVertices ; i+=3 ) {

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
