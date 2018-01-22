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
        std::string create_time_string(int t_sec);

        //  -- Manipulation --
        void find_and_replace(std::string* t_source, const std::string& t_find, const std::string& t_replace);
        void filter(std::string* t_source, const std::string& t_comment_start, const std::string& t_comment_end = "\n");
        std::string strip_path(const std::string& t_path);
        void strip_whitespace(std::string* t_str);

        //  -- Properties --
        bool is_numerical(const std::string& t_str);



    } // namespace utl
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_UTL_STRING_HPP
