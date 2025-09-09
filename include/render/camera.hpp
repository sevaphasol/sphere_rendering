#pragma once

#include "geometry/vector.hpp"
#include "geometry/line.hpp"

namespace render {

class Camera {
  public:
    Camera( const geometry::Vector& pos, float fov );

    geometry::Line
    PixelToViewRay( uint row, uint col, uint height, uint width ) const;

    float            fov;
    geometry::Vector pos;
};

} // namespace render
