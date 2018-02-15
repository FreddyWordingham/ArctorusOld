/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   07/01/2018.
 */



//  == INCLUDES ==
//  -- System --
#include <vector>
#include <cls/data/histogram.hpp>

//  -- General --
#include "gen/math.hpp"

//  -- Classes --
#include "cls/equip/entity.hpp"
#include "cls/equip/light.hpp"
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
/*
    std::vector<double> x({-4.0, -2.0, -1.0, 0.0, +1.0, +2.0, +4.0});
    std::vector<double> y({15.0, 10.0, 8.0, 7.5, 7.0, 5.0, 0.0});

    random::Linear lin(x, y);

    data::Histogram hist(-5.0, +5.0, 100);

    for (size_t i = 0; i < 1e6; ++i)
    {
        hist(lin(-2.0, +2.0));
//        hist(lin());
    }

    hist.save("hist.dat");*/




    equip::Light laser(geom::Mesh(file::read("../test/circle.obj"), math::Vec<3>({{3.0, 3.0, -3.0}}), math::Vec<3>({{0.0, 0.0, 1.0}}), 0.0,
                     math::Vec<3>({{1.0, 1.0, 1.0}})), phys::Material(file::read("../test/mat.mat")),
                     phys::Spectrum(file::read("../test/laser.spc")), 1.0);

    std::vector<phys::particle::Photon> phots;

    const int N = 1E4;
    for (int  i = 0; i < N; ++i)
    {
//        phys::particle::Photon phot(pos_norm[0], pos_norm[1], 0.0, w, 1.0, 1.5, 0.99, 1.0, 1.0);
        phys::particle::Photon phot = laser.gen_photon();

        for (int j = 0; j < 100; ++j)
        {
            phot.move(-std::log(rng::random(0.0, 1.0)) / phot.get_interaction());
            phot.scatter();
        }

        phots.push_back(phot);
    }

    graphical::Scene scene;

    equip::Entity surfaceOne(
        geom::Mesh(file::read("../test/planeSquare.obj"), math::Vec<3>({{-0.0, 4.0, -2.0}}), math::Vec<3>({{0.0, 0.0, 1.0}}), 0.0,
                   math::Vec<3>({{1.0, 1.0, 1.0}})), phys::Material(file::read("../test/mat1.mat")));
    equip::Entity surfaceTwo(
        geom::Mesh(file::read("../test/planeSquare.obj"), math::Vec<3>({{-0.0, 6.0, -2.0}}), math::Vec<3>({{0.0, 0.0, 1.0}}), 0.0,
                   math::Vec<3>({{1.0, 1.0, 1.0}})), phys::Material(file::read("../test/mat2.mat")));
    equip::Entity surfaceThree(
        geom::Mesh(file::read("../test/planeSquare.obj"), math::Vec<3>({{-0.0, 9.0, -2.0}}), math::Vec<3>({{0.0, 0.0, 1.0}}), 0.0,
               math::Vec<3>({{1.0, 1.0, 1.0}})), phys::Material(file::read("../test/mat3.mat")));

    scene.add_entity(surfaceOne);
    scene.add_entity(surfaceTwo);
    scene.add_entity(surfaceThree);

    scene.add_light(laser);

    for (size_t i = 0; i < phots.size(); ++i)
    {
        scene.add_photon(phots[i].get_path());
    }

    while (!scene.should_close())
    {
        scene.handle_input();
        scene.render();
    }

    return (0);
}
