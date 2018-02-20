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
            //  -- Vertices --
            const std::array<Vertex, 3> m_vert; //! Vertices of the triangle.

            //  -- Properties --
            const double       m_area;  //! Area of the triangle.
            const math::Vec<3> m_norm;  //! Normal of the triangle.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            explicit Triangle(const std::array<Vertex, 3>& t_vert);

            //  -- Initialisation --
            math::Vec<3> init_norm() const;


            //  == METHODS ==
          public:
            //  -- Getters --
            double get_area() const { return (m_area); }
            inline const Vertex& get_vert(size_t t_index) const;
            std::pair<double, math::Vec<3>> get_intersection_dist(const math::Vec<3>& t_pos, const math::Vec<3>& t_dir) const
            {
                assert(t_dir.is_normalised());
                assert(m_norm.is_normalised());

                // Calculate edge vectors.
                const math::Vec<3> edge_1 = m_vert[BETA].get_pos() - m_vert[ALPHA].get_pos();
                const math::Vec<3> edge_2 = m_vert[GAMMA].get_pos() - m_vert[ALPHA].get_pos();

                const math::Vec<3> q = t_dir ^edge_2;
                const double       a = edge_1 * q;

                // Check if ray is almost parallel to the triangle.
                if (std::fabs(a) <= std::numeric_limits<double>::epsilon())
                {
                    // Does not hit triangle.
                    return (std::pair<double, math::Vec<3>>(std::numeric_limits<double>::max(),
                                                            math::Vec<3>({{0.0, 0.0, 0.0}})));
                }

                const math::Vec<3> s = (t_pos - m_vert[ALPHA].get_pos()) / a;
                const math::Vec<3> r = s ^edge_1;

                // Calculate barycentric coordinates.
                const double alpha = s * q;
                const double beta  = r * t_dir;
                const double gamma = 1.0 - alpha - beta;

                // Check hit is on triangle (rather than somewhere else in the plane).
                if ((alpha < 0.0) || (beta < 0.0) | (gamma < 0.0))
                {
                    // Does not hit triangle.
                    return (std::pair<double, math::Vec<3>>(std::numeric_limits<double>::max(),
                                                            math::Vec<3>({{0.0, 0.0, 0.0}})));
                }

                // Calculate intersection distance.
                const double r_dist = edge_2 * r;

                // Check triangle is ahead of ray, rather than behind.
                if (r_dist <= 0.0)
                {
                    // Does not hit triangle.
                    return (std::pair<double, math::Vec<3>>(std::numeric_limits<double>::max(),
                                                            math::Vec<3>({{0.0, 0.0, 0.0}})));
                }

                // Determine interpolated normal.
                math::Vec<3> r_norm = math::normalise(
                    (m_vert[ALPHA].get_norm() * gamma) + (m_vert[BETA].get_norm() * alpha) + (m_vert[GAMMA].get_norm() * beta));

                return (std::pair<double, math::Vec<3>>(r_dist, r_norm));
            }

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
