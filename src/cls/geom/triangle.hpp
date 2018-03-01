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
            const double       m_area;          //! Area of the triangle.
            const math::Vec<3> m_plane_norm;    //! Normal of the triangle plane.

            //  -- Vertices --
            const std::array<math::Vec<3>, 3> m_pos;    //! Vertex positions.
            const std::array<math::Vec<3>, 3> m_norm;   //! Vertex normals.
            const std::array<math::Vec<3>, 3> m_cons;   //! Consistent normals used to calculate real reflections.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            Triangle(const std::array<math::Vec<3>, 3>& t_pos, const std::array<math::Vec<3>, 3>& t_norm);


            //  == METHODS ==
          public:
            //  -- Getters --
            double get_area() const { return (m_area); }
            const math::Vec<3>& get_plane_norm() const { return (m_plane_norm); }
            const math::Vec<3>& get_pos(const size_t t_index) const { return (m_pos[t_index]); }
            const math::Vec<3>& get_norm(const size_t t_index) const { return (m_norm[t_index]); }
            std::pair<double, math::Vec<3>> get_intersection(const math::Vec<3>& t_pos, const math::Vec<3>& t_dir) const;

            //  -- Generation --
            std::pair<math::Vec<3>, math::Vec<3>> gen_random_pos_and_norm() const;
        };



    } // namespace geom
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GEOM_TRIANGLE_HPP
