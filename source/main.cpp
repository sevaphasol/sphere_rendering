#include "render/render.hpp"
#include "render/config.hpp"

int
main()
{
    render::Screen screen;

    screen.AddLight( render::config::Lights[0] );
    screen.AddSphere( render::config::Spheres[0] );

    screen.Run();

    return 0;
}
