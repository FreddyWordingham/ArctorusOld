/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   28/01/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_GEOM_MESH_HPP
#define ARCTORUS_SRC_CLS_GEOM_MESH_HPP



//  == INCLUDES ==
//  -- System --
#include <vector>

//  -- Classes --
#include "cls/geom/triangle.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace geom
    {



        //  == CLASS ==
        /**
         *  Triangular mesh class used to form the boundary of objects.
         */
        class Mesh
        {
            //  == FIELDS ==
          private:
            //  -- Properties --
            const size_t m_num_vert;    //! Number of vertex positions.
            const size_t m_num_norm;    //! Number of vertex normals.
            const size_t m_num_tri;     //! Number of triangle faces.

            //  -- Triangle Data --
            const std::vector<geom::Triangle> m_tri;    //! List of triangles forming the mesh.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --

          private:
            //  -- Initialisation --


            //  == OPERATORS ==
          private:


            //  == METHODS ==
          public:
            //  -- Getters --
            size_t get_num_vert() const { return (m_num_vert); }
            size_t get_num_norm() const { return (m_num_norm); }
            size_t get_num_tri() const { return (m_num_tri); }
            inline const Triangle& get_tri(size_t t_index) const;
        };



        //  == METHODS ==
        //  -- Getters --
        /**
         *  Retrieve a reference to a triangle of the mesh.
         *
         *  @param  t_index Index of the triangle to retrieve.
         *
         *  @pre    t_index must be a valid index of m_tri.
         *
         *  @return A const reference to the triangle.
         */
        inline const Triangle& Mesh::get_tri(const size_t t_index) const
        {
            assert(t_index < m_tri.size());

            return (m_tri[t_index]);
        }



    } // namespace geom
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GEOM_MESH_HPP
