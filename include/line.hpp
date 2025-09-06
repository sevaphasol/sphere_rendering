#pragma once

#include "vector.hpp"

namespace linal {

class Line {
  public:
    Line( const Vector& direction, const Vector& base_point )
        : direction_( direction ), base_point_( base_point )
    {
    }

    float
    getDistance( const Vector& point ) const
    {
        return ( direction_ && point ) / direction_.getLen();
    }

  private:
    Vector direction_;
    Vector base_point_;
};

} // namespace linal
