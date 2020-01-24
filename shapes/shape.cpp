 
#include "shape.h"

Shape::Shape( std::shared_ptr<Shader> program, int numVertices, std::shared_ptr<Texture> texture ) {

    this->numVertices = numVertices ;

    this->program = program ;
    this->texture = texture ;
}

Shape::~Shape() {
    delete this->indices ;
}

void Shape::draw( glm::mat4 &matrixCamera, glm::mat4 &matrixModel ) {
    this->program->use() ;
    this->program->setMatrix( "CAMERA", glm::value_ptr(matrixCamera) ) ;
    this->program->setMatrix( "MODEL", glm::value_ptr(matrixModel) ) ;

    glActiveTexture( GL_TEXTURE0 ) ; 
    glBindTexture(GL_TEXTURE_2D, *texture ) ;
    glBindVertexArray( VAO ) ;
    glDrawElements( GL_TRIANGLES, numVertices,  GL_UNSIGNED_SHORT, indices ) ;
}



const float* Shape::PositionOffset = 0 ;
const float* Shape::NormalOffset = PositionOffset + 3 ;
const float* Shape::TextureOffset = NormalOffset + 3 ;
