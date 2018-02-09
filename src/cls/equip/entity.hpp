/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   09/02/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_EQUIP_ENTITY_HPP
#define ARCTORUS_SRC_CLS_EQUIP_ENTITY_HPP



//  == INCLUDES ==
//  -- Classes --
#include "cls/geom/mesh.hpp"
#include "cls/phys/material.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace equip
    {



        //  == CLASS ==
        /**
         *  Entity class coupling the optical properties of a material with the geometric boundaries of a mesh.
         */
        class Entity
        {
            //  == FIELDS ==
          private:
            //  -- Properties --
            const geom::Mesh     m_mesh;    //! Mesh describing the boundaries of the entity.
            const phys::Material m_mat;     //! Material describing the entities optical properties.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            Entity(const geom::Mesh &t_mesh, const phys::Material &t_mat);


          private:
            //  -- Initialisation --


            //  == METHODS ==
          private:
        };



    } // namespace equip
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_EQUIP_ENTITY_HPP
