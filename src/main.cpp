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


    math::Vec<3> vec({{0.0, 0.0, 1.0}});

    VAL(vec);
    VAL(vec.get_rho());
    VAL(vec.get_theta());
    VAL(vec.get_phi());

/*    graphical::Scene scene;


//    scene.add_light(math::Vec<3>({{0.0, 0.0, 4.0}}), math::Vec<3>({{0.75 * M_PI, 0.0, 0.75*M_PI}}), 0.1, 0.01, 5.0);
    scene.add_light(math::Vec<3>({{0.0, 0.0, 0.0}}), math::Vec<3>({{0.0, 0.0, 0.0}}), 1.0, 0.1, 1.0);
    scene.add_light(math::Vec<3>({{0.0, 0.0, 0.0}}), math::Vec<3>({{0.0, 0.0, 0.0}}), 0.1, 0.0, 0.1);
    scene.add_light(math::Vec<3>({{1.0, 1.0, 1.0}}), math::Vec<3>({{0.0, 0.0, 0.0}}), 0.1, 0.0, 0.1);
    scene.add_light(math::Vec<3>({{2.0, 2.0, 2.0}}), math::Vec<3>({{0.0, 0.0, 0.0}}), 0.1, 0.0, 0.1);
    scene.add_light(math::Vec<3>({{3.0, 3.0, 3.0}}), math::Vec<3>({{0.0, 0.0, 0.0}}), 0.1, 0.0, 0.1);



    scene.add_light(math::Vec<3>({{3.0, 3.0, 3.0}}), math::Vec<3>({{-1.0, -1.0, -1.0}}), 0.01, 0.0, 5.0);

    while (!scene.should_close())
    {
        scene.handle_input();
        scene.render();
    }*/

    return (0);
}
