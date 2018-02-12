/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   28/01/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_GEOM_TRIANGLE_HPP
#define ARCTORUS_SRC_CLS_GEOM_TRIANGLE_HPP



//  == INCLUDES ==
//  -- Classes --
#include "cls/geom/vertex.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace geom
    {



        //  == CLASS ==
        /**
         *  Triangle class used to form triangular meshes.
         */
        class Triangle
        {
            //  == FIELDS ==
          private:
            //  -- Vertices --
            std::array<Vertex, 3> m_vert;   //! Vertices of the triangle.

            //  -- Properties --
            double m_area;  //! Area of the triangle.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            explicit Triangle(const std::array<Vertex, 3>& t_vert);


            //  == METHODS ==
          public:
            //  -- Getters --
            double get_area() const { return (m_area); }
            inline const Vertex& get_vert(size_t t_index) const;
            std::array<math::Vec<3>, 2> get_random_pos_and_norm() const;

            //  -- Transformation --
            void transform(const math::Mat<4, 4>& t_pos_trans_mat, const math::Mat<4, 4>& t_dir_trans_mat);
        };



        //  == METHODS ==
        //  -- Getters --
        /**
         *  Retrieve a const reference to a vertex of the triangle,
         *
         *  @param  t_index Index of the vertex to retrieve.
         *
         *  @pre    t_index must be a valid index of m_vert.
         *
         *  @return A const reference to a vertex of the triangle.
         */
        inline const Vertex& Triangle::get_vert(const size_t t_index) const
        {
            assert(t_index < m_vert.size());

            return (m_vert[t_index]);
        }

        std::array<math::Vec<3>, 2> Triangle::get_random_pos_and_norm() const
        {

        }



    } // namespace geom
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GEOM_TRIANGLE_HPP
