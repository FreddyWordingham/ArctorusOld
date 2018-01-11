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
        std::string create_time_string(int sec);

        //  -- Manipulation --
        void find_and_replace(std::string* source, const std::string& find, const std::string& replace);
        void filter(std::string* source, const std::string& comment_start, const std::string& comment_end = "\n");
        std::string strip_path(const std::string& path);

        //  -- Properties --
        bool is_numerical(const std::string& str);



    } // namespace utl
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_UTL_STRING_HPP
