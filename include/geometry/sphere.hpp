#pragma once

#include <SFML/Graphics/Color.hpp>

#include "geometry/vector.hpp"
#include "geometry/line.hpp"

namespace geometry {

class Sphere {
  public:
    Sphere( const Vector& center, float radius );

    bool
    lineDoesIntersect( const Line& line ) const;

    // Call only if raIntersect == true
    Vector
    getIntersectionWithRay( const Line& line ) const;

    const sf::Color color = { 32, 4, 4 };
    Vector          center;
    float           radius;
};

} // namespace geometry
