/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   09/02/2018.
 */



//  == HEADER ==
#include "cls/equip/light.hpp"



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
         *  @param  t_power Power of the light source.
         *
         *  @post   m_power must be greater than zero.
         */
        Light::Light(const geom::Mesh& t_mesh, const phys::Spectrum& t_spec, const double t_power) :
            m_power(t_power),
            m_mesh(t_mesh),
            m_spec(t_spec)
        {
            assert(m_power > 0.0);
        }



    } // namespace equip
} // namespace arc
