#include "render/camera.hpp"

namespace render {

Camera::Camera( const geometry::Vector& pos, float fov ) : fov( fov ), pos( pos ) {}

geometry::Line
Camera::TraceRay( uint px_y, uint px_x, uint scr_height, uint scr_width ) const
{
    float x = ( 2 * ( ( px_x + 0.5 ) / scr_width ) - 1 );
    float y = ( 2 * ( ( px_y + 0.5 ) / scr_height ) - 1 ) * ( float( scr_height ) / scr_width );

    return geometry::Line( geometry::Vector( x, -y, -1 ) - pos, pos );
}

} // namespace render
