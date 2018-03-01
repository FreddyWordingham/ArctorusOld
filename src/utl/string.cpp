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
#include <cassert>
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
        std::string create_timestamp(const std::string& t_format)
        {
            std::time_t t = std::time(nullptr);

            std::stringstream time_stream;
            time_stream << std::put_time(std::localtime(&t), t_format.c_str());

            return (time_stream.str());
        }

        /**
         *  Convert a given number of seconds into a sexagesimal time string.
         *
         *  @param  t_sec   Number of seconds to convert to a time string.
         *
         *  @pre    t_sec must be positive.
         *
         *  @return A sexagesimal string representing the given number of seconds.
         */
        std::string create_time_string(int t_sec)
        {
            assert(t_sec > 0);

            const int hrs = t_sec / 3600;
            t_sec %= 3600;

            const int min = t_sec / 60;
            t_sec %= 60;

            return (std::to_string(hrs) + "h " + std::to_string(min) + "m " + std::to_string(t_sec) + "s");
        }


        //  -- Manipulation --
        /**
         *  Find and replace all substrings within a given source string with another replacement string.
         *
         *  @param  t_source    Source string in which substring values will be replaced.
         *  @param  t_find      Substring to be replaced with the rep string.
         *  @param  t_replace   String to replace the found substrings with.
         *
         *  @pre    t_source must not be empty.
         *  @pre    t_find must not be empty.
         */
        void find_and_replace(std::string* t_source, const std::string& t_find, const std::string& t_replace)
        {
            assert(!t_source->empty());
            assert(!t_find.empty());

            for (size_t pos = 0; (pos = t_source->find(t_find, pos)) != std::string::npos; pos += t_replace.size())
            {
                t_source->replace(pos, t_find.size(), t_replace);
            }
        }

        /**
         *  Remove all parts of string between two given comment identifying strings.
         *
         *  @param  t_source        Source string to filter comments from.
         *  @param  t_comment_start Comment start string identifier.
         *  @param  t_comment_end   Comment end string identifier.
         *
         *  @pre    t_source must not be empty.
         *  @pre    t_comment_start must not be empty.
         *  @pre    t_comment_end must not be empty.
         */
        void filter(std::string* t_source, const std::string& t_comment_start, const std::string& t_comment_end)
        {
            assert(!t_source->empty());
            assert(!t_comment_start.empty());
            assert(!t_comment_end.empty());

            size_t start;
            while ((start = t_source->find(t_comment_start)) != std::string::npos)
            {
                size_t end;
                if ((end = t_source->find(t_comment_end, start)) != std::string::npos)
                {
                    t_source->erase(start, end - start + t_comment_end.size());
                }
                else
                {
                    return;
                }
            }
        }

        /**
         *  Strip the path leaving only the filename and extension, from the full file path.
         *
         *  @param  t_path  Full file path.
         *
         *  @pre    t_path must not be empty.
         *
         *  @return The filename.
         */
        std::string strip_path(const std::string& t_path)
        {
            assert(!t_path.empty());

            size_t last_slash_pos = t_path.find_last_of('/');

            if (last_slash_pos == std::string::npos)
            {
                return (t_path);
            }

            return (t_path.substr(last_slash_pos + 1));
        }

        /**
         *  Strip the file extension leaving only the filename and extension, from the full file path.
         *
         *  @param  t_path  Full file path.
         *
         *  @pre    t_path must not be empty.
         *
         *  @return The path stripped of the file extension.
         */
        std::string strip_extension(const std::string& t_path)
        {
            assert(!t_path.empty());

            size_t last_period_pos = t_path.find_last_of('.');

            if (last_period_pos == std::string::npos)
            {
                return (t_path);
            }

            return (t_path.substr(last_period_pos + 1));
        }

        /**
         *  Strip the leading and trailing whitespace from a given string.
         *
         *  @param  t_str   String to be stripped of whitespace.
         *
         *  @pre    t_str must not be empty.
         *  @pre    t_str must contain characters other that whitespace characters.
         */
        void strip_whitespace(std::string* t_str)
        {
            assert(!t_str->empty());
            assert(t_str->find_last_not_of(" \t\f\v\n\r") != std::string::npos);

            t_str->erase(0, t_str->find_first_not_of(" \t\f\v\n\r"));
            t_str->erase(t_str->find_last_not_of(" \t\f\v\n\r") + 1);
        }


        //  -- Properties --
        /**
         *  Determine if the given string can be parsed into a numerical value.
         *
         *  @param  t_str   String to be tested.
         *
         *  @return True if the string can be parsed into a numerical value.
         */
        bool is_numerical(const std::string& t_str)
        {
            std::stringstream string_stream(t_str);

            double x;
            string_stream >> x;

            return (!string_stream.fail() && (string_stream.rdbuf()->in_avail() == 0));
        }



    } // namespace utl
} // namespace arc
