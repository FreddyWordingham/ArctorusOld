/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   07/01/2018.
 */



//  == INCLUDES ==
//  -- General --
#include "gen/log.hpp"
#include "gen/rng.hpp"

//  -- Classes --



//  == NAMESPACE ==
using namespace arc;


int count()
{
    int    count = 0;
    double total = 0.0;
    while (total < 1.0)
    {
        total += rng::random();
        ++count;
    }

    return (count);
}



//  == MAIN ==
/**
 *  Main function of the Arctorus program.
 *
 *  @return Zero upon a successful run.
 */
int main()
{
    LOG("Hello world!");

    const size_t samples = 1E8;

    int         total_count = 0;
    for (size_t i           = 0; i < samples; ++i)
    {
        TEMP("Norm gen", 100.0 * i / samples);

        total_count += count();
    }

    VAL(static_cast<double>(total_count) / samples);

    return (0);
}
