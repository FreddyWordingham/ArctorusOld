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

    rng::seed(130);

/*
    arc::data::Histogram hist(0.0, 10.0, 10);

    VAL(hist.get_bin_width());
    VAL(hist.get_num_bin());
    VAL(hist.get_bin_pos(arc::data::Histogram::align::LEFT));
    VAL(hist.get_bin_pos(arc::data::Histogram::align::CENTER));
    VAL(hist.get_bin_pos(arc::data::Histogram::align::RIGHT));

    for (size_t i = 0; i < 100; ++i)
    {
        double x = 10.0 * (static_cast<double>(rand()) / RAND_MAX);

        hist(x);
    }

    LOG(hist);

    hist.save("hist.dat", false, arc::data::Histogram::align::LEFT);
*/


    return (0);
}
