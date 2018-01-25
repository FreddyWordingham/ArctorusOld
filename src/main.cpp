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
#include "cls/interpolator/linear.hpp"



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

    interpolator::Linear lin({0.0, 1.0, 2.0, 4.0}, {0.0, 1.0, 4.0, -4.0});


    for (double x = 0.0; x <= 4.0; x += 0.01)
    {
        LOG(x << "\t" << lin(x));
    }

    LOG(lin);


    lin.save("interpolated.dat");

    return (0);
}
