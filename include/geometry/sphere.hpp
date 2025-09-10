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

    sf::Color
    GetColor() const;

    Vector
    GetCenter() const;

    float
    GetRadius() const;

  private:
    bool
    LineDoesIntersect( const Line& line ) const;

  private:
    sf::Color color_;
    Vector    center_;
    float     radius_;
};

} // namespace geometry
