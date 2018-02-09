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
        Light::Light(const geom::Mesh& t_mesh, const random::Linear& t_spec) :
            m_mesh(t_mesh),
            m_spec(t_spec)
        {
        }


        //  -- Initialisation --



    } // namespace equip
} // namespace arc
