/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   07/01/2018.
 */



//  == INCLUDES ==
//  -- System --
#include <vector>
#include <gen/math.hpp>
#include <cls/phys/material.hpp>
#include <cls/equip/entity.hpp>

//  -- General --

//  -- Classes --
#include "cls/file/handle.hpp"
#include "cls/data/histogram.hpp"
#include "cls/data/table.hpp"
#include "cls/equip/entity.hpp"
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
    equip::Entity monkey(geom::Mesh(file::read("../test/monkey.obj")), phys::Material(file::read("../test/intralipid_10.mat")));

    LOG("Hello world!");

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

    scene.add_entity(monkey);

    while (!scene.should_close())
    {
        scene.handle_input();
        scene.render();
    }

    return (0);
}
