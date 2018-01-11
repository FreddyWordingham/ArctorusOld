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
        std::string create_timestamp()
        {
            std::time_t t = std::time(nullptr);

            std::stringstream time_stream;
            time_stream << std::put_time(std::localtime(&t), "%d-%m-%Y %H:%M:%S");

            return (time_stream.str());
        }

        /**
         *  Convert a given number of seconds into a sexagesimal time string.
         *
         *  @param  sec Number of seconds to convert to a time string.
         *
         *  @pre    sec must be positive.
         *
         *  @return A sexagesimal string representing the given number of seconds.
         */
        std::string create_time_string(int sec)
        {
            assert(sec > 0);

            const int hrs = sec / 3600;
            sec %= 3600;

            const int min = sec / 60;
            sec %= 60;

            return (std::to_string(hrs) + "h " + std::to_string(min) + "m " + std::to_string(sec) + "s");
        }


        //  -- Manipulation --
        /**
         *  Find and replace all substrings within a given source string with another replacement string.
         *
         *  @param  source  Source string in which substring values will be replaced.
         *  @param  find    Substring to be replaced with the rep string.
         *  @param  rep     String to replace the found substrings with.
         *
         *  @pre    source must not be empty.
         *  @pre    find must not be empty.
         */
        void find_and_replace(std::string& source, const std::string& find, const std::string& rep)
        {
            assert(!source.empty());
            assert(!find.empty());

            for (size_t pos = 0; (pos = source.find(find, pos)) != std::string::npos; pos += rep.size())
            {
                source.replace(pos, find.size(), rep);
            }
        }

        /**
         *  Remove all parts of string between two given comment identifying strings.
         *
         *  @param  source          Source string to filter comments from.
         *  @param  comment_start   Comment start string identifier.
         *  @param  comment_end     Comment end string identifier.
         *
         *  @pre    source must not be empty.
         *  @pre    comment_start must not be empty.
         *  @pre    comment_end must not be empty.
         */
        void filter(std::string& source, const std::string& comment_start, const std::string& comment_end)
        {
            assert(!source.empty());
            assert(!comment_start.empty());
            assert(!comment_end.empty());

            size_t start;
            while ((start = source.find(comment_start)) != std::string::npos)
            {
                size_t end;
                if ((end = source.find(comment_end, start)) != std::string::npos)
                {
                    source.erase(start, end - start + comment_end.size());
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
         *  @param  path    Full file path.
         *
         *  @pre    path must not be empty.
         *
         *  @return The filename.
         */
        std::string strip_path(const std::string& path)
        {
            assert(!path.empty());

            size_t last_slash_pos = path.find_last_of('/');

            if (last_slash_pos == std::string::npos)
            {
                return (path);
            }

            return (path.substr(last_slash_pos + 1));
        }


        //  -- Properties --
        /**
         *  Determine if the given string can be parsed into a numerical value.
         *
         *  @param  str String to be tested.
         *
         *  @return True if the string can be parsed into a numerical value.
         */
        bool is_numerical(const std::string& str)
        {
            std::stringstream string_stream(str);

            double x;
            string_stream >> x;

            return (!string_stream.fail() && (!string_stream.rdbuf()->in_avail()));
        }



    } // namespace utl
} // namespace arc
