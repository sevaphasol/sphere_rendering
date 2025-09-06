#pragma once

#include "vector.hpp"
#include "line.hpp"
#include <SFML/Graphics/Color.hpp>

namespace objects {

class Sphere {
  public:
    Sphere( const linal::Vector& center, float radius ) : center_( center ), radius_( radius ) {}

    bool
    rayIntersect( const linal::Line& line ) const
    {
        return line.getDistance( center_ ) <= radius_;
    }

    const sf::Color color = { 32, 32, 32 };

  private:
    linal::Vector center_;
    float         radius_;
};

} // namespace objects
