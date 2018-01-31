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
            const std::array<Vertex, 3> m_vert; //! Vertices of the triangle.

            //  -- Properties --
            const double m_area;    //! Area of the triangle.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            Triangle(const std::array<math::Vec<3>, 3>& t_pos, const std::array<math::Vec<3>, 3>& t_norm);


            //  == METHODS ==
          public:
            //  -- Getters --
            inline const math::Vec<3>& get_pos(size_t t_index) const;
            inline const math::Vec<3>& get_norm(size_t t_index) const;
            double get_area() const { return (m_area); }
        };



        //  == METHODS ==
        //  -- Getters --
        /**
         *  Get a vertex position of the triangle.
         *
         *  @param  t_index Index of the vertex position to retrieve.
         *
         *  @pre    t_index must be less than three.
         *
         *  @return A const reference to the triangle vertex position.
         */
        inline const math::Vec<3>& Triangle::get_pos(const size_t t_index) const
        {
            assert(t_index < 3);

            return (m_pos[t_index]);
        }

        /**
         *  Get a vertex normal of the triangle.
         *
         *  @param  t_index Index of the vertex normal to retrieve.
         *
         *  @pre    t_index must be less than three.
         *
         *  @return A const reference to the triangle vertex normal.
         */
        inline const math::Vec<3>& Triangle::get_norm(const size_t t_index) const
        {
            assert(t_index < 3);

            return (m_norm[t_index]);
        }



    } // namespace geom
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GEOM_TRIANGLE_HPP
