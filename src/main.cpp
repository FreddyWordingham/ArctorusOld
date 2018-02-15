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
#include "cls/setup/sim.hpp"



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

    setup::Sim pdt(file::read("parameters.json"));

    pdt.render();

    return (0);
}
