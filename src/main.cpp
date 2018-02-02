/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   07/01/2018.
 */



//  == INCLUDES ==
//  -- General --
#include "gen/log.hpp"

//  -- Classes --
#include "cls/file/handle.hpp"
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

    graphical::Scene scene;


    geom::Mesh mesh(file::read("test/torus.obj"));
    scene.add_light(mesh);

    while (!scene.should_close())
    {
        scene.handle_input();
        scene.render();
    }

    return (0);
}
