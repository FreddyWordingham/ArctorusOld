/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   07/01/2018.
 */



//  == HEADER ==
#include "utl/string.hpp"



//  == INCLUDES ==
//  -- System --
#include <ctime>
#include <iomanip>
#include <sstream>



//  == NAMESPACE ==
namespace arc
{
    namespace utl
    {



        //  == FUNCTIONS ==
        //  -- Timestamp --
        /**
         *  Create a timestamp of the current time.
         *  Get the current time and then convert it to a human readable string.
         *
         *  @return The current time as a string.
         */
        std::string create_timestamp()
        {
            std::time_t t = std::time(nullptr);

            std::stringstream time_stream;
            time_stream << std::put_time(std::localtime(&t), "%d-%m-%Y %H:%M:%S");

            return (time_stream.str());
        }

        /**
         *  Convert a given number of seconds into a sexidecimal time string.
         *
         *  @param  sec Number of seconds to convert to a time string.
         *
         *  @return A sexidecimal string representing the given number of seconds.
         */
        std::string create_timestring(int sec)
        {
            const int hrs = sec / 3600;
            sec %= 3600;

            const int min = sec / 60;
            sec %= 60;

            return (std::to_string(hrs) + "h " + std::to_string(min) + "m " + std::to_string(sec) + "s");
        }



    } // namespace utl
} // namespace arc
