/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   11/01/2018.
 */



//  == HEADER ==
#include "cls/file/handle.hpp"



//  == INCLUDES ==
//  -- System --

//  -- General --
#include "gen/config.hpp"
#include "gen/log.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace file
    {



        //  == INSTANTIATION ==
        //  -- Constructors --
        /**
         *  Construct a handle to a given file with the specified mode.
         *
         *  @param  init_path   Path to the file being opened.
         *  @param  mode        Mode to open the file with.
         */
        Handle::Handle(const std::string& init_path, const std::fstream::openmode& mode) :
            path(init_path),
            filename(utl::strip_path(path)),
            file(init_file(mode))
        {
            // TODO file size warning.
        }


        //  -- Destructors --
        /**
         *  Close the open file.
         *
         *  @pre    file must be open.
         *
         *  @post   file must be closed.
         */
        Handle::~Handle()
        {
            assert(file.is_open());

            file.close();

            assert(!file.is_open());
        }


        //  -- Initialisation --
        std::fstream Handle::init_file(const std::fstream::openmode& mode) const
        {
            std::fstream file;
            file.open(path, mode);

            if (!file.is_open())
            {
                file.open(config::ARCTORUS_DIR + path, mode);
            }

            if (file.is_open())
            {
                ERROR("Failed to construct file::Handle object.", "The file: '" << filename << "' could not be opened.");
            }

            if (mode == std::fstream::out)
            {

            }

            return (file);
        }



    } // namespace file
} // namespace arc
