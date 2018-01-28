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
#include "cls/random/linear.hpp"



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

    std::vector<double> x, p;
    for (int            i = -5; i <= 5; ++i)
    {
        x.push_back(i);
        p.push_back(i * i);
    }

    random::Linear lin(x, p);


    for (size_t i = 0; i < 10; ++i)
    {
        LOG(lin());
    }

    return (0);
}
