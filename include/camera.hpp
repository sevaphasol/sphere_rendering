#pragma once

#include "vector.hpp"

namespace objects {

class Camera {
  public:
    Camera( const linal::Vector& pos, float fov ) : fov( fov ), pos( pos ) {}

    linal::Vector
    screenToWorld( uint row, uint col, uint height, uint width ) const
    {
        float x =
            ( 2 * ( col + 0.5 ) / (float)width - 1 ) * tan( fov / 2. ) * width / (float)height;
        float y = -( 2 * ( row + 0.5 ) / (float)height - 1 ) * tan( fov / 2. );

        return { x, y, -1 };
    }

    float         fov;
    linal::Vector pos;
};

} // namespace objects
