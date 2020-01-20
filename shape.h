#pragma once 

#include <glm/gtc/matrix_transform.hpp>

#include <memory>

#include "shader.h"
#include "texture.h"

class Shape {

 private:
  GLuint  VBO ;  // it's static so won't need this again
  GLuint  VAO ;
  std::shared_ptr<Shader> program ;
  std::shared_ptr<Texture> texture ;
  int numVertices ;
  unsigned short *indices ;

 public:
  ~Shape() ;
  Shape( std::shared_ptr<Shader> program, float *vertices, int numVertices, std::shared_ptr<Texture> texture ) ;
  void draw( glm::mat4 &matrixCamera, glm::mat4 &matrixModel ) ;

  static constexpr int FloatsPerVertex = 3 + 3 + 2 ;   // position + normal + texture coord
  static constexpr size_t BytesPerVertex = sizeof(float) * FloatsPerVertex ;

  static const float* PositionOffset ;
  static const float* NormalOffset ;
  static const float* TextureOffset ;
} ;


