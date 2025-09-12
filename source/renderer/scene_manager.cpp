#include "render/scene_manager.hpp"
#include "geometry/vector.hpp"
#include "render/config.hpp"

namespace render {

SceneManager::SceneManager()
    : width_( Config::WindowWidth ), height_( Config::WindowHeight ),
      camera_( { 0, 0, 0 }, Config::CameraFov ),
      window_( sf::VideoMode( Config::WindowWidth, Config::WindowHeight ),
               Config::Title,
               sf::Style::Close ),
      pixels_( Config::WindowWidth * Config::WindowHeight ),
      background_color_( Config::BackgroundColor )
{
    window_.setFramerateLimit( 60 );
}

void
SceneManager::Run()
{
    while ( window_.isOpen() )
    {
        HandleEvents();
        Render();
        Draw();
    }
}

void
SceneManager::AddLight( float x,
                        float y,
                        float z,
                        float embedded_intensity,
                        float diffuse_intensity,
                        float glare_intensity )
{
    lights_.push_back( Light( geometry::Vector( x, y, z ),
                              embedded_intensity,
                              diffuse_intensity,
                              glare_intensity ) );
}

void
SceneManager::AddSphere( float x, float y, float z, float radius, const sf::Color& color )
{
    spheres_.push_back( geometry::Sphere( geometry::Vector( x, y, z ), radius, color ) );
}

void
SceneManager::MoveLights( const geometry::Vector& delta )
{
    for ( auto& light : lights_ )
    {
        light.Move( delta );
    }
}

void
SceneManager::HandleEvents()
{
    sf::Event event;
    while ( window_.pollEvent( event ) )
    {
        if ( event.type == sf::Event::Closed )
        {
            window_.close();
        }
    }

    bool move_lights = sf::Keyboard::isKeyPressed( sf::Keyboard::LControl );

    int move_left     = int( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) );
    int move_right    = int( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) );
    int move_forward  = int( sf::Keyboard::isKeyPressed( sf::Keyboard::W ) );
    int move_backward = int( sf::Keyboard::isKeyPressed( sf::Keyboard::S ) );
    int move_up       = int( sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) );
    int move_down     = int( sf::Keyboard::isKeyPressed( sf::Keyboard::LShift ) );
    int turn_left     = int( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) );
    int turn_right    = int( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) );
    int turn_up       = int( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) );
    int turn_down     = int( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) );

    geometry::Vector delta( ( move_right - move_left ),
                            ( move_up - move_down ),
                            ( move_forward - move_backward ) );

    delta *= Config::MoveScale;

    if ( move_lights )
    {
        MoveLights( delta );
    } else
    {
        camera_.Move( delta );
    }

    camera_.Rotate( ( turn_right - turn_left ) * Config::RotateScale,
                    ( turn_up - turn_down ) * Config::RotateScale );
}

sf::Color
SceneManager::CalcLights( const geometry::Vector& point,
                          const geometry::Vector& normal,
                          const sf::Color&        color )
{
    geometry::Vector sum_light( 0, 0, 0 );

    for ( const auto& light : lights_ )
    {
        sum_light += light.CalcLight( point - camera_.GetPos(), point, normal, color );
    }

    sum_light.Clamp( 0, 255 );

    return sf::Color( sum_light.GetX(), sum_light.GetY(), sum_light.GetZ() );
}

sf::Color
SceneManager::CalcPixelColor( uint row, uint col )
{
    const geometry::Line view_ray = camera_.TraceRay( row, col, height_, width_ );

    sf::Color pixel_color = background_color_;

    for ( const auto& sphere : spheres_ )
    {
        const geometry::Vector point = sphere.GetIntersectionWithDirectedLine( view_ray );

        if ( point.Valid() )
        {
            pixel_color = CalcLights( point, point - sphere.GetCenter(), sphere.GetColor() );
            break;
        }
    }

    return pixel_color;
}

void
SceneManager::Render()
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
SceneManager::Draw()
{
    window_.clear();
    window_.draw( pixels_.data(), pixels_.size(), sf::Points );
    window_.display();
}

} // namespace render
