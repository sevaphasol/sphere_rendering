#pragma once

#include <SFML/Graphics/Color.hpp>

#include "geometry/vector.hpp"
#include "geometry/line.hpp"

namespace geometry {

class Sphere {
  public:
    Sphere( const Vector& center, float radius, const sf::Color& color );

    Vector
    GetIntersectionWithLine( const Line& line ) const;

  private:
    bool
    LineDoesIntersect( const Line& line ) const;

  public:
    sf::Color color;
    Vector    center;
    float     radius;
};

} // namespace geometry
