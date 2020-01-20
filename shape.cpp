 
#include "shape.h"

Shape::Shape( std::shared_ptr<Shader> program, float *vertices, int numVertices, std::shared_ptr<Texture> texture ) {

    this->numVertices = numVertices ;
    size_t verticesSize = numVertices * BytesPerVertex ;

    glGenVertexArrays( 1, &VAO ) ;
    glGenBuffers( 1, &VBO ) ;
    
    glBindVertexArray( VAO ) ;
    glBindBuffer( GL_ARRAY_BUFFER, VBO ) ;
    glBufferData( GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW ) ;

    glEnableVertexAttribArray( 0 ) ;  // location(0) = aPos
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, BytesPerVertex, PositionOffset ) ;

    glEnableVertexAttribArray( 1 ) ;  // location(1) = normal
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, BytesPerVertex, NormalOffset ) ;

    glEnableVertexAttribArray( 2 ) ;  // location(2) = texture
    glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, BytesPerVertex, TextureOffset ) ;

    this->program = program ;
    this->texture = texture ;
    this->indices = new unsigned short[ numVertices ] ;

    for( unsigned short i=0 ; i<numVertices ; i++ ) {
        this->indices[i] = i ;
    }
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
