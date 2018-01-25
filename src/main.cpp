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

#include "cls/data/histogram.hpp"
#include "gen/rng.hpp"


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

    arc::data::Histogram hist(0.0, 10.0, 10);

    for (size_t i = 0; i < 1E9; ++i)
    {
        TEMP("test", i / 1e7);

        double x = RANDOM(0.0, 10.0);

        hist(x);
    }

    LOG(hist);

    hist.save("hist.dat", false, arc::data::Histogram::align::LEFT);



    return (0);
}
