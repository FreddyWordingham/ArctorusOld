/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   11/01/2018.
 */



//  == HEADER ==
#include "cls/file/handle.hpp"



//  == INCLUDES ==
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
            const size_t size = get_file_size();
            if (size > SIZE_WARNING)
            {
                WARN("Large file opened.", "file: '" << filename << "' is " << size << "bytes.");
            }
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
        /**
         *  Initialise the handle to the file itself.
         *
         *  @param  mode    Mode to open the file with.
         *
         *  @post   file should be open.
         *
         *  @return The handle to the requested file.
         */
        std::fstream Handle::init_file(const std::fstream::openmode& mode) const
        {
            std::fstream init_file;
            init_file.open(path, mode);

            if (!init_file.is_open())
            {
                init_file.open(config::ARCTORUS_DIR + path, mode);
            }

            if (!init_file.is_open())
            {
                ERROR("Failed to construct file::Handle object.", "The file: '" << filename << "' could not be opened.");
            }

            if (mode == std::fstream::out)
            {
                init_file << COMMENT_CHAR << " Created by Arctorus: " << utl::create_timestamp() << "\n";
                init_file << COMMENT_CHAR << " Build: " << config::BUILD_INFO << "\n";
            }

            assert(init_file.is_open());

            return (init_file);
        }



        //  == METHODS ==
        //  -- Getters --
        /**
         *  Get the size of the file in bytes.
         *
         *  @return The size of the file in bytes.
         */
        size_t Handle::get_file_size() const
        {
            const std::streampos get_pos = file.tellg();

            file.seekg(0);

            const std::streampos first = file.tellg();
            file.seekg(0, std::fstream::end);
            const size_t size = static_cast<size_t>(file.tellg() - first);

            file.seekg(get_pos);

            return (size);
        }



    } // namespace file
} // namespace arc
