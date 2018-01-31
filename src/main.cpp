/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   07/01/2018.
 */



//  == INCLUDES ==
//  -- System --

//  -- General --
#include <cls/geom/mesh.hpp>
#include <cls/file/handle.hpp>
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

//    geom::Mesh cube(file::read("cube.obj"));


    return (0);
}
