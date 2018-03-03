/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   28/02/2018.
 */



//  == HEADER ==
#include "utl/file.hpp"



//  == INCLUDES ==
//  -- System --
#include <sys/stat.h>

//  -- Classes --
#include "gen/log.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace utl
    {



        //  == FUNCTIONS ==
        /**
         *  Create a new directory and check that it was successfully created.
         *
         *  @param  t_name  Name of the directory.
         */
        void create_directory(const std::string& t_name)
        {
            if (mkdir(t_name.c_str(), S_IRWXU) != 0)
            {
                ERROR("Unable to create directory.", "The directory: '" << t_name << "', could not be created.");
            }
        }


        //  -- File Contents --
        /**
         *  Read the contents of the given file into a string.
         *
         *  @param  t_file_path Path to the file to retrieve the contents from.
         *  @param  t_filter    If true filter the file when reading its contents.
         *
         *  @return A string of the file's contents.
         */
        std::string read(const std::string& t_file_path, bool t_filter)
        {
            return (file::Handle(t_file_path, std::fstream::in).get_contents(t_filter));
        }



    } // namespace utl
} // namespace arc
