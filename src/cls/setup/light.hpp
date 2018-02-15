/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   15/02/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_SETUP_LIGHT_HPP
#define ARCTORUS_SRC_CLS_SETUP_LIGHT_HPP



//  == INCLUDES ==
//  -- System --
#include <string>



//  == NAMESPACE ==
namespace arc
{
    namespace setup
    {



        //  == CLASS ==
        /**
         *  Store information required to setup a light equipment object.
         */
        class Light
        {
            //  == FIELDS ==
          private:
            //  -- Filenames --
            const std::string m_mesh_path;  //! Path to mesh file.
            const std::string m_spec_path;  //! Path to spectrum file.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --

          private:
            //  -- Initialisation --


            //  == OPERATORS ==
          private:


            //  == METHODS ==
          private:
        };



    } // namespace setup
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_SETUP_LIGHT_HPP
