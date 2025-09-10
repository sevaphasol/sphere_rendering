#pragma once

#include <cmath>

namespace geometry {

class Vector {
  public:
    Vector( float x, float y, float z );

    bool
    Valid() const;

    float
    GetLen() const;

    float
    operator,( const Vector& that ) const;

    Vector
    operator+( const Vector& that ) const;

    Vector
    operator-( const Vector& that ) const;

    void
    operator+=( const Vector& that );

    void
    operator-=( const Vector& that );

    Vector
    operator+( float scalar ) const;

    Vector
    operator-( float scalar ) const;

    Vector
    operator*( float scalar ) const;

    void
    operator+=( float scalar );

    void
    operator-=( float scalar );

    void
    operator*=( float scalar );

  private:
    float x_;
    float y_;
    float z_;
};

float
CalcCos( const Vector& v1, const Vector& v2 );

float
CalcSin( const Vector& v1, const Vector& v2 );

float
CalcVecMulModule( const Vector& v1, const Vector& v2 );

} // namespace geometry
