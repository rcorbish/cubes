#pragma once 

#include <glm/gtc/matrix_transform.hpp>

#include <memory>

#include <shader.h>
#include <texture.h>

class Shape {

private:
  std::shared_ptr<Shader> program ;
  std::shared_ptr<Texture> texture ;

protected:
  GLuint  VBO ;
  GLuint  VAO ;
  int numVertices ;
  unsigned short *indices ;


 public:
  virtual ~Shape() ;
  Shape( std::shared_ptr<Shader> program, int numVertices, std::shared_ptr<Texture> texture ) ;
  void draw( glm::mat4 &matrixCamera, glm::mat4 &matrixModel ) ;

  virtual void initVertexData() = 0 ;

  static constexpr int FloatsPerVertex = 3 + 3 + 2 ;   // position + normal + texture coord
  static constexpr size_t BytesPerVertex = sizeof(float) * FloatsPerVertex ;

  static const float* PositionOffset ;
  static const float* NormalOffset ;
  static const float* TextureOffset ;
} ;


