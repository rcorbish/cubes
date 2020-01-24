#pragma once

#include "shape.h"

class Cone : public Shape {
protected:
    void makeVertexData( float *vertices ) ;

public:
    Cone( std::shared_ptr<Shader> program, int numSides, std::shared_ptr<Texture> texture ) :
        Shape( program, numSides*3, texture ) {} ;
    void initVertexData() ;
} ;