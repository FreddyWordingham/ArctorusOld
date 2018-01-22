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
#include <sstream>



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

        //  -- Conversion --
        template <typename T>
        T str_to(const std::string& t_str);



        //  == FUNCTIONS ==
        /**
         *  Parse the string into a numerical value.
         *
         *  @tparam T   Type to parse the string into.
         *
         *  @param  t_str   String to be parsed.
         *
         *  @pre  t_str may not be empty.
         *
         *  @post string_stream read may not fail.
         *  @post string_stream may not have left over characters.
         *
         *  @return The parsed value of the string.
         */
        template <typename T>
        T str_to(const std::string& t_str)
        {
            assert(!t_str.empty());

            std::stringstream string_stream(t_str);

            T x;
            string_stream >> x;

            assert(!string_stream.fail());
            assert(string_stream.rdbuf()->in_avail() == 0);

            return (x);
        }



    } // namespace utl
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_UTL_STRING_HPP
