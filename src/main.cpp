/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   07/01/2018.
 */



//  == INCLUDES ==
//  -- System --
#include <cmath>

//  -- General --
#include "gen/config.hpp"
#include "gen/log.hpp"

//  -- Classes --
#include "cls/file/handle.hpp"
#include "cls/math/vec.hpp"

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
    VERB("Arctorus directory:\n" << arc::config::ARCTORUS_DIR);

    LOG(READ_FILE("../README.md"));

    arc::math::Vec<5> vec({{0.0, 1.0, -1.0, 7.0, -7.0}});

    VAL(vec);

    vec += 0.7;
    VAL(vec);

    vec -= 0.7;
    VAL(vec);

    vec += vec;
    VAL(vec);

    vec -= vec;
    VAL(vec);

    for (int i = 0; i < 5; ++i)
    {
        vec[i] = std::pow(2.0, static_cast<double>(i));
    }
    VAL(vec);

    vec *= 1.5;
    VAL(vec);

    vec /= 3.0;
    VAL(vec);

    ++vec;
    VAL(vec);

    vec++;
    VAL(vec);

    --vec;
    VAL(vec);

    vec--;
    VAL(vec);


    arc::math::Vec<3> a({{1.0, 0.0, 0.0}});
    arc::math::Vec<3> b({{0.0, 1.0, 0.0}});
    VAL(a ^ b);
    VAL(b ^ a);


    std::vector<double> vect({0.0, 2.0, 5.0});
    std::cout << vect << "\n";


    return (0);
}
