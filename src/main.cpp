/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   07/01/2018.
 */



//  == INCLUDES ==
//  -- System --

//  -- General --
#include "gen/log.hpp"
#include "gen/rng.hpp"

//  -- Classes --
#include "cls/graphical/scene.hpp"



//  == NAMESPACE ==
using namespace arc;



//  == MAIN ==
/**
 *  Main function of the Arctorus program.
 *
 *  @return Zero upon a successful run.
 */
int main()
{
    LOG("Hello world!");
    rng::seed();

    graphical::Scene scene;

    scene.add_light(math::Vec<3>({{+5.0, -5.0, +5.0}}), math::Vec<3>({{-1.0, +1.0, -1.0}}), 0.5, M_PI / 8.0, 5.0);

    while (!scene.should_close())
    {
        scene.handle_input();
        scene.render();
    }

    return (0);
}
