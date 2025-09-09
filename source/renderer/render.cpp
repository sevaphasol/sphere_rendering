#include "render/render.hpp"
#include "render/config.hpp"

namespace render {

Screen::Screen()
    : width_( config::WindowWidth ), height_( config::WindowHeight ),
      camera_( { 0, 0, 0 }, config::CameraFov ),
      window_( sf::VideoMode( config::WindowWidth, config::WindowHeight ),
               config::Title,
               sf::Style::Close ),
      pixels_( config::WindowWidth * config::WindowHeight ),
      backgorund_color_( config::BackgroundColor ) {};

void
Screen::Run()
{
    while ( window_.isOpen() )
    {
        HandleEvents();
        Render();
        Draw();
    }
}

void
Screen::AddLight( const Light& light )
{
    lights_.push_back( light );
}

void
Screen::AddSphere( const geometry::Sphere& sphere )
{
    spheres_.push_back( sphere );
}

void
Screen::HandleEvents()
{
    sf::Event event;
    while ( window_.pollEvent( event ) )
    {
        if ( event.type == sf::Event::Closed )
        {
            window_.close();
        }
    }
}

float
Screen::getDiffuseLightDep( geometry::Vector& normal, geometry::Vector& light_ray, float intensity )
{
    return std::max( 0.0F, intensity * -normal.getCos( light_ray ) );
}

float
Screen::getGlareLightDep( geometry::Vector& normal,
                          geometry::Vector& view,
                          geometry::Vector& light_ray,
                          float             intensity )
{
    geometry::Vector reflect_ray = light_ray + normal * 2;

    return std::max( 0.0F, intensity * -view.getCos( reflect_ray ) );
}

sf::Color
Screen::getLightsDep( const geometry::Vector& point )
{
    geometry::Vector lights_dep = { 0, 0, 0 };
    geometry::Vector normal     = point - spheres_[0].center;

    for ( const auto& light : lights_ )
    {
        geometry::Vector light_ray = point - light.position;
        geometry::Vector view      = point - camera_.pos;

        lights_dep += getDiffuseLightDep( normal, light_ray, light.intensity );
        lights_dep += getGlareLightDep( normal, view, light_ray, light.intensity );
    }

    return { static_cast<sf::Uint8>( std::clamp( lights_dep.x * 255.F, 0.F, 255.F ) ),
             static_cast<sf::Uint8>( std::clamp( lights_dep.y * 255.F, 0.F, 255.F ) ),
             static_cast<sf::Uint8>( std::clamp( lights_dep.z * 255.F, 0.F, 255.F ) ) };
}

sf::Color
Screen::calcPixelColor( uint row, uint col )
{
    const geometry::Line view_ray = camera_.PixelToViewRay( row, col, height_, width_ );

    const geometry::Vector point = spheres_[0].getIntersectionWithRay( view_ray );

    if ( !point.isValid() )
    {
        return backgorund_color_;
    }

    sf::Color diffuse_color = getLightsDep( point );

    return spheres_[0].color + diffuse_color;
}

void
Screen::Render()
{
    for ( uint row = 0; row < height_; row++ )
    {
        for ( uint col = 0; col < width_; col++ )
        {
            sf::Vector2f pos   = sf::Vector2f( col, row );
            sf::Color    color = calcPixelColor( row, col );

            pixels_[row * width_ + col] = sf::Vertex( pos, color );
        }
    }
}

void
Screen::Draw()
{
    window_.clear();
    window_.draw( pixels_.data(), pixels_.size(), sf::Points );
    window_.display();
}

} // namespace render
