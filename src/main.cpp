/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   07/01/2018.
 */



//  == INCLUDES ==
//  -- System --
#include <vector>

//  -- General --
#include "gen/log.hpp"
#include "gen/math.hpp"
#include "gen/rng.hpp"

//  -- Classes --
#include "cls/file/handle.hpp"
#include "cls/graphical/scene.hpp"

#include "cls/data/histogram.hpp"



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

    data::Histogram hist(-4.0, +4.0, 80);

    for (unsigned long int i=0; i<10; ++i)
    {
        double x = rng::henyey_greenstein(0.0);
        VAL(x);

        hist(x);
    }

    hist.save("henyey.dat", true);


/*    LOG("Hello world!");

    graphical::Scene scene;

    std::vector<graphical::point::Photon> path_x;
    path_x.push_back(graphical::point::Photon({0.0f, 0.0f, 0.0f}, 400E-9f, 1.0f, 0.0));
    path_x.push_back(graphical::point::Photon({1.0f, 0.0f, 0.0f}, 400E-9f, 1.0f, 1.0));
    scene.add_photon(path_x);

    std::vector<graphical::point::Photon> path_y;
    path_y.push_back(graphical::point::Photon({0.0f, 0.0f, 0.0f}, 400E-9f, 1.0f, 0.0));
    path_y.push_back(graphical::point::Photon({0.0f, 1.0f, 0.0f}, 400E-9f, 1.0f, 1.0));
    scene.add_photon(path_y);

    std::vector<graphical::point::Photon> path_z;
    path_z.push_back(graphical::point::Photon({0.0f, 0.0f, 0.0f}, 400E-9f, 1.0f, 0.0));
    path_z.push_back(graphical::point::Photon({0.0f, 0.0f, 1.0f}, 400E-9f, 1.0f, 1.0));
    scene.add_photon(path_z);

    const geom::Mesh mesh(file::read("test/monkey.obj"), math::Vec<3>({{2.0, 2.0, 2.0}}), math::Vec<3>({{0.0, 0.0, -1.0}}), 0.0,
                          math::Vec<3>({{0.1, 0.1, 0.1}}));
    scene.add_light(mesh, 2.0, {1.0f, 1.0f, 0.0f, 1.0f});

    while (!scene.should_close())
    {
        scene.handle_input();
        scene.render();
    }*/

    return (0);
}
