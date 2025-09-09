#include <SFML/Graphics/Color.hpp>
#include "render/renderer.hpp"

int
main()
{
    render::Renderer renderer;

    renderer.AddLight( 3, 3, 5, 0.2f );
    renderer.AddSphere( 0, 0, 10, 2, sf::Color( 32, 32, 32 ) );

    renderer.Run();

    return 0;
}
