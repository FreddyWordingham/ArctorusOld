/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   07/01/2018.
 */



//  == INCLUDES ==
//  -- General --
#include "gen/config.hpp"
#include "gen/log.hpp"

#include "utl/array.hpp"


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
    VERB("Arctorus directory:\n" << ARCTORUS_DIR);

    for (int i = 0; i < 10; ++i)
    {
        term::Logger::get_instance().temp("This is temporary: ", i);
        usleep(900000);
    }

    return (0);
}
