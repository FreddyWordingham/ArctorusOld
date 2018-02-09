/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   09/02/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_EQUIP_LIGHT_HPP
#define ARCTORUS_SRC_CLS_EQUIP_LIGHT_HPP



//  == INCLUDES ==
//  -- Classes --
#include "cls/geom/mesh.hpp"
#include "cls/random/linear.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace equip
    {



        //  == CLASS ==
        /**
         *  Light source class used to emit photons from.
         */
        class Light
        {
            //  == FIELDS ==
          private:
            //  -- Properties --
            const geom::Mesh     m_mesh;    //! Mesh describing the surface of the light.
            const random::Linear m_spec;    //! Linear random generator forming the emission spectrum.


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



    } // namespace equip
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_EQUIP_LIGHT_HPP
