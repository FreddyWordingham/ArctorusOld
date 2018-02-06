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

//  -- Classes --
#include "cls/file/handle.hpp"
#include "cls/graphical/scene.hpp"
#include "cls/geom/vertex.hpp"


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

/*    std::vector<graphical::point::Photon> path;
    path.push_back(graphical::point::Photon({0.0f, 0.0f, 0.0f}, 400E-9f, 1.0f, 0.0));
    path.push_back(graphical::point::Photon({0.0f, 0.0f, 1.0f}, 400E-9f, 1.0f, 1.0));
    path.push_back(graphical::point::Photon({0.0f, 1.0f, 1.0f}, 400E-9f, 1.0f, 2.0));
    path.push_back(graphical::point::Photon({2.0f, 1.0f, 1.0f}, 400E-9f, 1.0f, 4.0));
    path.push_back(graphical::point::Photon({2.0f, 1.0f, 5.0f}, 400E-9f, 1.0f, 8.0));*/

    graphical::Scene scene;

    geom::Mesh mesh(file::read("test/monkey.obj"));

    const math::Mat<4, 4> pos_mat = math::create_pos_mat(math::Vec<3>({{-2.0, -2.0, -2.0}}), math::Vec<3>({{0.0, 0.0, -1.0}}), M_PI/2.0, math::Vec<3>({{1.0, 2.0, 0.1}}));
    const math::Mat<4, 4> dir_mat = math::create_dir_mat(math::Vec<3>({{0.0, 0.0, -1.0}}), M_PI/2.0, math::Vec<3>({{1.0, 2.0, 0.1}}));

    mesh.transform(pos_mat, dir_mat);


//    scene.add_light(mesh, 2.0, {1.0f, 1.0f, 1.0f, 1.0f});
    scene.add_entity(mesh, {0.9f, 0.0f, 0.0f, 1.0f});

    while (!scene.should_close())
    {
        scene.handle_input();
        scene.render();
    }

    return (0);
}
