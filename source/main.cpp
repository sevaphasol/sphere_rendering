#include <SFML/Graphics/Color.hpp>
#include "render/renderer.hpp"

int
main()
{
    render::Renderer renderer;

    renderer.AddLight( 3, 3, 3, 0.5 );
    renderer.AddSphere( 0, 0, 5, 2, sf::Color( 152, 32, 32 ) );

    // renderer.AddSphere( -1, -1.5, 5, 0.5, sf::Color( 175, 128, 79 ) );
    // renderer.AddSphere( 0, -1.5, 5, 0.5, sf::Color( 175, 128, 79 ) );
    // renderer.AddSphere( 1, -1.5, 5, 0.5, sf::Color( 175, 128, 79 ) );
    // renderer.AddSphere( 0, -0.5, 5, 0.5, sf::Color( 175, 128, 79 ) );
    // renderer.AddSphere( 0, 0.5, 5, 0.5, sf::Color( 175, 128, 79 ) );
    // renderer.AddSphere( 0, 1.5, 5, 0.5, sf::Color( 152, 51, 102 ) );

    renderer.Run();

    return 0;
}
