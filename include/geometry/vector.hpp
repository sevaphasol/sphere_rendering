#pragma once

#include <cmath>

namespace geometry {

class Vector {
  public:
    Vector( float x, float y, float z );

    bool
    isValid() const;

    float
    getLen() const;

    float
    getCos( const Vector& that ) const;

    float
    operator&&( const Vector& that ) const;

    Vector
    operator+( const Vector& that ) const;

    Vector
    operator-( const Vector& that ) const;

    float
    operator*( const Vector& that ) const;

    Vector
    operator+( float scalar ) const;

    Vector
    operator-( float scalar ) const;

    Vector
    operator*( float scalar ) const;

    void
    operator+=( float scalar );

    float x;
    float y;
    float z;
};

} // namespace geometry
