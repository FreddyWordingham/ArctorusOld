/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   28/02/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_UTL_FILE_HPP
#define ARCTORUS_SRC_UTL_FILE_HPP



//  == INCLUDES ==
//  -- Classes --
#include "cls/file/handle.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace utl
    {



        //  == FUNCTION PROTOTYPES ==
        //  -- Reading --
        std::string read(const std::string& t_file_path, bool t_filter = true);



    } // namespace utl
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_UTL_FILE_HPP
