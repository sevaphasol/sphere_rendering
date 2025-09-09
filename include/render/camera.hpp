#pragma once

#include <SFML/Graphics.hpp>

#include "geometry/vector.hpp"
#include "geometry/line.hpp"

namespace render {

class Camera {
  public:
    Camera( const geometry::Vector& pos, float fov );

    geometry::Line
    TraceRay( uint px_y, uint px_x, uint scr_height, uint scr_width ) const;

    geometry::Vector pos;
    float            fov;
};

} // namespace render
