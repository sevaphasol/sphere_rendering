#include "render/camera.hpp"

namespace render {

Camera::Camera( const geometry::Vector& pos, float fov )
    : fov_( fov ), pos_( pos ), hor_ort_( 1, 0, 0 ), ver_ort_( 0, 1, 0 ), fwd_ort_( 0, 0, -1 ) {};

void
Camera::Rotate( float hor_angle, float ver_angle )
{
    Rotate( hor_angle, hor_ort_ );
    Rotate( ver_angle, ver_ort_ );
}

void
Camera::Rotate( float angle, geometry::Vector& ort )
{
    float cos_angle = std::cos( angle );
    float sin_angle = std::sin( angle );

    geometry::Vector old_fwd_ort = fwd_ort_;
    geometry::Vector old_ort     = ort;

    fwd_ort_ = old_fwd_ort * cos_angle - old_ort * sin_angle;
    ort      = old_fwd_ort * sin_angle + old_ort * cos_angle;
}

geometry::Line
Camera::TraceRay( uint px_y, uint px_x, uint scr_height, uint scr_width ) const
{
    float aspect_ratio = float( scr_height ) / scr_width;

    float x = ( 2 * ( ( px_x + 0.5 ) / scr_width ) - 1 );
    float y = ( 2 * ( ( px_y + 0.5 ) / scr_height ) - 1 ) * aspect_ratio;

    geometry::Vector ray_dir = hor_ort_ * ( -x ) + ver_ort_ * y + fwd_ort_;

    return geometry::Line( ray_dir, pos_ );
}

void
Camera::Move( const geometry::Vector& delta )
{
    pos_ += delta;
}

geometry::Vector
Camera::GetPos() const
{
    return pos_;
}

geometry::Vector
Camera::GetHorOrt() const
{
    return hor_ort_;
}

geometry::Vector
Camera::GetVerOrt() const
{
    return ver_ort_;
}

geometry::Vector
Camera::GetFwdOrt() const
{
    return fwd_ort_;
}

float
Camera::GetFov() const
{
    return fov_;
}

} // namespace render
