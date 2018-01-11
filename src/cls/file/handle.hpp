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



        //  == SETTINGS ==
        //  -- Formatting --
        constexpr const char COMMENT_CHAR = '#';    //! Character used to comment file lines.
        constexpr const char DELIMIT_CHAR = ',';    //! Character used to delimit file data.



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
            const std::string path;     //! Path to the file.
            const std::string filename; //! Name of the file.

            //  -- Handle --
            mutable std::fstream file;  //! Handle to the file.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            Handle(const std::string& init_path, const std::fstream::openmode& mode);

            //  -- Destructors --
            ~Handle();

          private:
            //  -- Initialisation --
            std::fstream init_file(const std::fstream::openmode& mode) const;


            //  == OPERATORS ==
          public:
            //  -- Writing --
            template <typename T>
            Handle& operator<<(const T& val);


            //  == METHODS ==
          private:
            //  -- Getters --
            std::string get_filename() const { return (filename); }
            size_t get_file_size() const;
        };



        //  == OPERATORS ==
        //  -- Writing --
        /**
         *  Enable writing of the file opened by the file handle.
         *
         *  @tparam T   Type of variable to be written to the file.
         *
         *  @param  val Value to be written to the file.
         *
         *  @return A reference to this file handler.
         */
        template <typename T>
        Handle& Handle::operator<<(const T& val)
        {
            file << val;

            return (*this);
        }



    } // namespace file
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_FILE_HANDLER_HPP
