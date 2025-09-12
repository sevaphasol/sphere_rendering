#include <SFML/Graphics/Color.hpp>
#include "render/scene_manager.hpp"

int
main()
{
    render::SceneManager manager;

    manager.AddLight( -15, -5, 10, 0.2, 0.3, 0.5 );
    manager.AddLight( 0, 3, 3, 0.2, 0.3, 0.5 );
    manager.AddSphere( -2, 0, 5, 1.5, sf::Color( 255, 8, 8 ) );
    manager.AddSphere( 2, 0, 5, 1.5, sf::Color( 8, 255, 8 ) );

    // manager.AddSphere( -1, -1.5, 5, 0.5, sf::Color( 175, 128, 79 ) );
    // manager.AddSphere( 0, -1.5, 5, 0.5, sf::Color( 175, 128, 79 ) );
    // manager.AddSphere( 1, -1.5, 5, 0.5, sf::Color( 175, 128, 79 ) );
    // manager.AddSphere( 0, -0.5, 5, 0.5, sf::Color( 175, 128, 79 ) );
    // manager.AddSphere( 0, 0.5, 5, 0.5, sf::Color( 175, 128, 79 ) );
    // manager.AddSphere( 0, 1.5, 5, 0.5, sf::Color( 152, 51, 102 ) );

    manager.Run();

    return 0;
}
