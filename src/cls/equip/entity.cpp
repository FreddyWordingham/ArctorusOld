/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   09/02/2018.
 */



//  == HEADER ==
#include "cls/equip/entity.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace equip
    {



        //  == INSTANTIATION ==
        //  -- Constructors --
        /**
         *  Construct an entity from a given mesh and material.
         *
         *  @param  t_mesh  Mesh to describe the boundaries of the entity.
         *  @param  t_mat   Material describing the optical properties of the entity.
         */
        Entity::Entity(const geom::Mesh& t_mesh, const phys::Material& t_mat) :
            m_mesh(t_mesh),
            m_mat(t_mat)
        {
        }



    } // namespace equip
} // namespace arc
