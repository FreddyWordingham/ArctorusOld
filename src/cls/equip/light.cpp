/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   09/02/2018.
 */



//  == HEADER ==
#include "cls/equip/light.hpp"



//  == INCLUDES ==
//  -- System --



//  == NAMESPACE ==
namespace arc
{
    namespace equip
    {



        //  == INSTANTIATION ==
        //  -- Constructors --
        /**
         *  Construct a light from a given mesh and spectrum.
         *
         *  @param  t_mesh  Mesh to describe the surface of the light.
         *  @param  t_spec  Spectrum distribution.
         */
        Light::Light(const geom::Mesh& t_mesh, const phys::Spectrum& t_spec) :
            m_mesh(t_mesh),
            m_spec(t_spec)
        {
        }


        //  -- Initialisation --



    } // namespace equip
} // namespace arc
