#include "geometry/vector.hpp"

namespace geometry {

Vector::Vector( float x, float y, float z ) : x_( x ), y_( y ), z_( z ) {}

bool
Vector::Valid() const
{
    return !( std::isnan( x_ ) || std::isnan( y_ ) || std::isnan( z_ ) );
}

float
Vector::GetLen() const
{
    return sqrt( ( x_ * x_ ) + ( y_ * y_ ) + ( z_ * z_ ) );
}

float
Vector::operator,( const Vector& that ) const
{
    return ( this->x_ * that.x_ ) + ( this->y_ * that.y_ ) + ( this->z_ * that.z_ );
}

Vector
Vector::operator+( const Vector& that ) const
{
    return { this->x_ + that.x_, this->y_ + that.y_, this->z_ + that.z_ };
}

Vector
Vector::operator-( const Vector& that ) const
{
    return { this->x_ - that.x_, this->y_ - that.y_, this->z_ - that.z_ };
}

void
Vector::operator+=( const Vector& that )
{
    this->x_ += that.x_;
    this->y_ += that.y_;
    this->z_ += that.z_;
}

void
Vector::operator-=( const Vector& that )
{
    this->x_ -= that.x_;
    this->y_ -= that.y_;
    this->z_ -= that.z_;
}

Vector
Vector::operator+( float scalar ) const
{
    return Vector( this->x_ + scalar, this->y_ + scalar, this->z_ + scalar );
}

Vector
Vector::operator-( float scalar ) const
{
    return Vector( this->x_ - scalar, this->y_ - scalar, this->z_ - scalar );
}

Vector
Vector::operator*( float scalar ) const
{
    return Vector( this->x_ * scalar, this->y_ * scalar, this->z_ * scalar );
}

void
Vector::operator+=( float scalar )
{
    this->x_ += scalar;
    this->y_ += scalar;
    this->z_ += scalar;
}

void
Vector::operator-=( float scalar )
{
    this->x_ -= scalar;
    this->y_ -= scalar;
    this->z_ -= scalar;
}

void
Vector::operator*=( float scalar )
{
    this->x_ *= scalar;
    this->y_ *= scalar;
    this->z_ *= scalar;
}

float
CalcCos( const Vector& v1, const Vector& v2 )
{
    return ( v1, v2 ) / ( v1.GetLen() * v2.GetLen() );
}

float
CalcSin( const Vector& v1, const Vector& v2 )
{
    return sin( acos( CalcCos( v1, v2 ) ) );
}

float
CalcVecMulModule( const Vector& v1, const Vector& v2 )
{
    return v1.GetLen() * v2.GetLen() * CalcSin( v1, v2 );
}

} // namespace geometry
