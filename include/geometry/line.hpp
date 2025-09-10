#pragma once

#include "geometry/vector.hpp"

namespace geometry {

class Line {
  public:
    Line( const Vector& dir, const Vector& base_point );

    float
    GetDistance( const Vector& point ) const;

    Vector
    GetDirectionVector() const;

    Vector
    GetBasePoint() const;

  private:
    Vector dir_;
    Vector base_point_;
};

} // namespace geometry
