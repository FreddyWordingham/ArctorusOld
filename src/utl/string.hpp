/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   07/01/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_UTL_STRING_HPP
#define ARCTORUS_SRC_UTL_STRING_HPP



//  == INCLUDES ==
//  -- System --
#include <string>



//  == NAMESPACE ==
namespace arc
{
    namespace utl
    {



        //  == FUNCTION PROTOTYPES ==
        //  -- Timestamp --
        std::string create_timestamp();
        std::string create_timestring(int sec);



    } // namespace utl
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_UTL_STRING_HPP
