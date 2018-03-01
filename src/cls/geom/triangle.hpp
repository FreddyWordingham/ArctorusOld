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
//  -- System --
#include <utility>

//  -- General --
#include "gen/math.hpp"
#include "gen/rng.hpp"

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
            //  -- Properties --
            const double       m_area;  //! Area of the triangle.
            const math::Vec<3> m_norm;  //! Normal of the triangle.

            //  -- Vertices --
            const std::array<Vertex, 3> m_vert; //! Vertices of the triangle.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            Triangle(const math::Vec<3>& t_alpha_pos, const math::Vec<3>& t_beta_pos, const math::Vec<3>& t_gamma_pos,
                     const math::Vec<3>& t_alpha_norm, const math::Vec<3>& t_beta_norm, const math::Vec<3>& t_gamma_norm)

            //  -- Initialisation --
            math::Vec<3> init_norm() const;


            //  == METHODS ==
          public:
            //  -- Getters --
            double get_area() const { return (m_area); }
            inline const Vertex& get_vert(size_t t_index) const;
            std::pair<double, math::Vec<3>> get_intersection(const math::Vec<3>& t_pos, const math::Vec<3>& t_dir) const;

            //  -- Generation --
            std::pair<math::Vec<3>, math::Vec<3>> gen_random_pos_and_norm() const;
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



    } // namespace geom
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GEOM_TRIANGLE_HPP
