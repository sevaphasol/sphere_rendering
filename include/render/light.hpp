#pragma once

#include <SFML/Graphics.hpp>
#include "geometry/vector.hpp"

namespace render {

class Light {
  public:
    Light( geometry::Vector position, float intensity );

    geometry::Vector position;
    float            intensity;
};

} // namespace render
