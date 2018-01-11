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
            const std::fstream file;    //! Handle to the file.


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
          private:


            //  == METHODS ==
          private:
        };



    } // namespace file
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_FILE_HANDLER_HPP
