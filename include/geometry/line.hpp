#pragma once

#include "geometry/vector.hpp"

namespace geometry {

class Line {
  public:
    Line( const Vector& direction, const Vector& base_point );

    float
    getDistance( const Vector& point ) const;

    Vector direction;
    Vector base_point;
};

} // namespace geometry
