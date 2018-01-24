/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   07/01/2018.
 */



//  == INCLUDES ==
//  -- General --
#include "gen/log.hpp"

//  -- Utility --
#include "utl/vector.hpp"

//  -- Classes --
#include "cls/file/handle.hpp"
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
    LOG("Hello world!");

    arc::data::Histogram hist(0.0, 10.0, 10);

/*    for (size_t i = 0; i < 100; ++i)
    {
        double x = static_cast<double>(rand()) / RAND_MAX;

        hist(x);
    }*/

    std::vector<double> vec({0.0, 1.0, 2.0, 3.0});

    LOG(hist.get_bin_pos(arc::data::Histogram::align::LEFT));


    return (0);
}
