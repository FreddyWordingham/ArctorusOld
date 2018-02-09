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
#include "cls/data/table.hpp"
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

    graphical::Scene scene;

    equip::Entity monkey(geom::Mesh(file::read("../test/monkey.obj")), phys::Material(file::read("../test/intralipid_10.mat")));
    scene.add_entity(monkey);

    equip::Light led(geom::Mesh(file::read("../test/circle.obj")), phys::Spectrum(file::read("../test/laser.spc")), 1.0);
    scene.add_light(led);

    while (!scene.should_close())
    {
        scene.handle_input();
        scene.render();
    }

    return (0);
}
