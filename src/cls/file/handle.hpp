/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   11/01/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_FILE_HANDLER_HPP
#define ARCTORUS_SRC_CLS_FILE_HANDLER_HPP



//  == INCLUDES ==
//  -- System --
#include <fstream>



//  == NAMESPACE ==
namespace arc
{
    namespace file
    {



        //  -- Warnings --
        constexpr const int SIZE_WARNING = 10;  //! [bytes] Warning triggered when opening files larger than this size.

        //  -- Formatting --
        constexpr const char COMMENT_CHAR = '#';    //! Character used to comment file lines.
        constexpr const char DELIMIT_CHAR = ',';    //! Character used to delimit file data.
        constexpr const int  PRINT_WIDTH  = 16;     //! Space allocated to each data print.



        //  == CLASS ==
        /**
         *  A class which creates a handle to a given file.
         *  File opening or creation is first attempted relative to the current working directory,
         *  If that fails, the file is opened relative to the Arctorus top level directory.
         *  Upon destruction of the file handler object, check that the file is closed.
         */
        class Handle
        {
            //  == FIELDS ==
          private:
            //  -- Properties --
            const std::string m_path;       //! Path to the file.
            const std::string m_filename;   //! Name of the file.

            //  -- Handle --
            mutable std::fstream m_file;    //! Handle to the file.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            Handle(const Handle& /*unused*/) = delete;
            Handle(const Handle&& /*unused*/) = delete;
            Handle(const std::string& t_path, const std::fstream::openmode& t_mode);

            //  -- Destructors --
            ~Handle();

          private:
            //  -- Initialisation --
            std::fstream init_file(const std::fstream::openmode& t_mode) const;


            //  == OPERATORS ==
          public:
            //  -- Copy --
            Handle& operator=(const Handle& /*unused*/) = delete;
            Handle& operator=(const Handle&& /*unused*/) = delete;

            //  -- Writing --
            template <typename T>
            Handle& operator<<(const T& t_val);


            //  == METHODS ==
          public:
            //  -- Getters --
            std::string get_filename() const;
            size_t get_file_size() const;
            std::string get_contents() const;

            //  -- Writing --
            Handle& comment();
        };



        //  == FUNCTION PROTOTYPES ==
        //  -- File Contents --
        std::string read(const std::string& t_file_path);



        //  == OPERATORS ==
        //  -- Writing --
        /**
         *  Enable writing of the file opened by the file handle.
         *
         *  @tparam T   Type of variable to be written to the file.
         *
         *  @param  t_val   Value to be written to the file.
         *
         *  @return A reference to this file handler.
         */
        template <typename T>
        Handle& Handle::operator<<(const T& t_val)
        {
            m_file << t_val;

            return (*this);
        }



    } // namespace file
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_FILE_HANDLER_HPP
