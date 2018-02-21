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
         *  @param  t_path      Path to the file being opened.
         *  @param  t_mode      Mode to open the file with.
         *  @param  t_header    When true, write the Arctorus file header.
         */
        Handle::Handle(const std::string& t_path, const std::fstream::openmode& t_mode, const bool t_header) :
            m_path(t_path),
            m_filename(utl::strip_path(m_path)),
            m_file(init_file(t_mode, t_header))
        {
            const size_t size = get_file_size();
            if (size > SIZE_WARNING)
            {
                WARN("Large file opened.", "file: '" << m_filename << "' is " << size << "bytes.");
            }
        }


        //  -- Destructors --
        /**
         *  Close the open file.
         *
         *  @pre    m_file must be open.
         *
         *  @post   m_file must be closed.
         */
        Handle::~Handle()
        {
            assert(m_file.is_open());

            m_file.close();

            assert(!m_file.is_open());
        }


        //  -- Initialisation --
        /**
         *  Initialise the handle to the file itself.
         *
         *  @param  t_mode      Mode to open the file with.
         *  @param  t_header    When true, write the Arctorus file header.
         *
         *  @post   r_file should be open.
         *
         *  @return The handle to the requested file.
         */
        std::fstream Handle::init_file(const std::fstream::openmode& t_mode, const bool t_header) const
        {
            std::fstream r_file;
            r_file.open(m_path, t_mode);

            if (!r_file.is_open())
            {
                r_file.open(config::ARCTORUS_DIR + m_path, t_mode);
            }

            if (!r_file.is_open())
            {
                ERROR("Failed to construct file::Handle object.", "The file: '" << m_filename << "' could not be opened.");
            }

            if ((t_mode == std::fstream::out) && (t_header))
            {
                r_file << COMMENT_CHAR << " Created by Arctorus: " << utl::create_timestamp() << "\n";
                r_file << COMMENT_CHAR << " Build: " << config::BUILD_INFO << "\n";
            }

            assert(r_file.is_open());

            return (r_file);
        }



        //  == METHODS ==
        //  -- Getters --
        /**
         *  Get the filename of the open file.
         *
         *  @return The filename of the file.
         */
        std::string Handle::get_filename() const
        {
            return (m_filename);
        }

        /**
         *  Get the size of the file in bytes.
         *
         *  @return The size of the file in bytes.
         */
        size_t Handle::get_file_size() const
        {
            const std::streampos get_pos = m_file.tellg();

            m_file.seekg(0, std::fstream::beg);

            const std::streampos first = m_file.tellg();
            m_file.seekg(0, std::fstream::end);
            const size_t r_size = static_cast<size_t>(m_file.tellg() - first);

            m_file.seekg(get_pos);

            return (r_size);
        }

        /**
         *  Retrieve the contents of the open file as a string.
         *  Commented lines are filtered out.
         *
         *  @param  t_filter    If true filter the file when reading its contents.
         *
         *  @return A string of the open file's contents.
         */
        std::string Handle::get_contents(const bool t_filter) const
        {
            const std::streampos get_pos = m_file.tellg();

            m_file.seekg(0, std::fstream::beg);

            std::stringstream contents_stream;
            contents_stream << m_file.rdbuf();

            m_file.seekg(get_pos);

            std::string r_contents = contents_stream.str();
            if (t_filter)
            {
                utl::filter(&r_contents, std::string(1, COMMENT_CHAR));
            }

            if (r_contents.back() == '\n')
            {
                r_contents.pop_back();
            }

            return (r_contents);
        }


        //  -- Writing --
        /**
         *  Enable writing of a comment to the file handle.
         *
         *  @return A reference to this file handle.
         */
        Handle& Handle::comment()
        {
            m_file << COMMENT_CHAR << " ";

            return (*this);
        }



        //  == FUNCTIONS ==
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
            return (arc::file::Handle(t_file_path, std::fstream::in).get_contents(t_filter));
        }



    } // namespace file
} // namespace arc
