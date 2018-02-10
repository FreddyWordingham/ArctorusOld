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
#include "gen/math.hpp"

//  -- Classes --
#include "cls/equip/entity.hpp"
#include "cls/equip/light.hpp"
#include "cls/file/handle.hpp"
#include "cls/graphical/scene.hpp"
#include "cls/phys/particle/photon.hpp"



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


    phys::particle::Photon phot_a(math::Vec<3>({{0.0, 0.0, 0.0}}), math::Vec<3>({{1.0, 0.0, 0.0}}),
    0.0, 550E-9, 1.0, 1.5, 0.99, 1.0, 0.5);
    phot_a.move(1.0);
    phot_a.rotate(0.1, 0.0);
    phot_a.move(1.0);
    phot_a.rotate(0.1, 0.0);
    phot_a.move(1.0);
    phot_a.rotate(0.1, 0.0);
    phot_a.move(1.0);
    phot_a.rotate(0.1, 0.0);
    phot_a.move(1.0);

    phys::particle::Photon phot_b(math::Vec<3>({{0.0, 0.0, 0.0}}), math::Vec<3>({{-1.0, 0.0, 0.0}}),
    0.0, 550E-9, 1.0, 1.5, 0.99, 1.0, 0.5);
    phot_b.move(1.0);
    phot_b.rotate(0.1, 0.0);
    phot_b.move(1.0);
    phot_b.rotate(0.1, 0.0);
    phot_b.move(1.0);
    phot_b.rotate(0.1, 0.0);
    phot_b.move(1.0);
    phot_b.rotate(0.1, 0.0);
    phot_b.move(1.0);


    graphical::Scene scene;

    equip::Entity monkey(
        geom::Mesh(file::read("../test/monkey.obj"), math::Vec<3>({{3.0, 3.0, -3.0}}), math::Vec<3>({{0.0, 0.0, 1.0}}), 0.0,
                   math::Vec<3>({{1.0, 1.0, 1.0}})), phys::Material(file::read("../test/intralipid_10.mat")));
    scene.add_entity(monkey);

    equip::Light led(geom::Mesh(file::read("../test/circle.obj")), phys::Spectrum(file::read("../test/laser.spc")), 1.0);
    scene.add_light(led);

    scene.add_photon(phot_a.get_path());
    scene.add_photon(phot_b.get_path());

    while (!scene.should_close())
    {
        scene.handle_input();
        scene.render();
    }

    return (0);
}
