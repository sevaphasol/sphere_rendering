#include "render/camera.hpp"

namespace render {

Camera::Camera( const geometry::Vector& pos, float fov ) : fov( fov ), pos( pos ) {}

geometry::Line
Camera::PixelToViewRay( uint row, uint col, uint height, uint width ) const
{
    float x = ( 2 * ( col + 0.5 ) / (float)width - 1 ) * tan( fov / 2. ) * width / (float)height;
    float y = -( 2 * ( row + 0.5 ) / (float)height - 1 ) * tan( fov / 2. );

    return geometry::Line( { x, y, -1 }, pos );
}

} // namespace render
