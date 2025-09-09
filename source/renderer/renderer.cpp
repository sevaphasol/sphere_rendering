#include "render/renderer.hpp"
#include "render/config.hpp"

namespace render {

Renderer::Renderer()
    : width_( Config::WindowWidth ), height_( Config::WindowHeight ),
      camera_( { 0, 0, 0 }, Config::CameraFov ),
      window_( sf::VideoMode( Config::WindowWidth, Config::WindowHeight ),
               Config::Title,
               sf::Style::Close ),
      pixels_( Config::WindowWidth * Config::WindowHeight ),
      backgorund_color_( Config::BackgroundColor ) {};

void
Renderer::Run()
{
    while ( window_.isOpen() )
    {
        HandleEvents();
        Render();
        Draw();
    }
}

void
Renderer::AddLight( float x, float y, float z, float intensity )
{
    lights_.push_back( Light( geometry::Vector( x, y, z ), intensity ) );
}

void
Renderer::AddSphere( float x, float y, float z, float radius, const sf::Color& color )
{
    spheres_.push_back( geometry::Sphere( geometry::Vector( x, y, z ), radius, color ) );
}

void
Renderer::HandleEvents()
{
    sf::Event event;
    while ( window_.pollEvent( event ) )
    {
        if ( event.type == sf::Event::Closed )
        {
            window_.close();
        }
    }

    int left     = int( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) );
    int right    = int( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) );
    int forward  = int( sf::Keyboard::isKeyPressed( sf::Keyboard::W ) );
    int backward = int( sf::Keyboard::isKeyPressed( sf::Keyboard::S ) );

    camera_.pos.x += ( left - right ) * Config::WasdScale;
    camera_.pos.z += ( forward - backward ) * Config::WasdScale;
}

sf::Color
Renderer::GetLightsDep( const geometry::Vector& point )
{
    geometry::Vector lights_dep = { 0, 0, 0 };
    geometry::Vector normal     = point - spheres_[0].center;

    for ( const auto& light : lights_ )
    {
        lights_dep += light.CalcLumacy( point - camera_.pos, point, normal );
    }

    return { sf::Uint8( std::clamp( lights_dep.x * 255.f, 0.f, 255.f ) ),
             sf::Uint8( std::clamp( lights_dep.y * 255.f, 0.f, 255.f ) ),
             sf::Uint8( std::clamp( lights_dep.z * 255.f, 0.f, 255.f ) ) };
}

sf::Color
Renderer::CalcPixelColor( uint row, uint col )
{
    const geometry::Line view_ray = camera_.TraceRay( row, col, height_, width_ );

    const geometry::Vector point = spheres_[0].GetIntersectionWithLine( view_ray );

    if ( !point.Valid() )
    {
        return backgorund_color_;
    }

    sf::Color diffuse_color = GetLightsDep( point );

    return spheres_[0].color + diffuse_color;
}

void
Renderer::Render()
{
#pragma omp parallel for
    for ( uint row = 0; row < height_; row++ )
    {
        for ( uint col = 0; col < width_; col++ )
        {
            sf::Vector2f pos   = sf::Vector2f( col, row );
            sf::Color    color = CalcPixelColor( row, col );

            pixels_[row * width_ + col] = sf::Vertex( pos, color );
        }
    }
}

void
Renderer::Draw()
{
    window_.clear();
    window_.draw( pixels_.data(), pixels_.size(), sf::Points );
    window_.display();
}

} // namespace render
