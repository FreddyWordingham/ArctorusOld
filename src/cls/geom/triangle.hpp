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


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            Triangle(const std::array<math::Vec<3>, 3>& t_pos, const std::array<math::Vec<3>, 3>& t_norm);

            //  -- Initialisation --
            math::Vec<3> init_plane_norm(const std::array<math::Vec<3>, 3>& t_pos,
                                         const std::array<math::Vec<3>, 3>& t_norm) const;


            //  == METHODS ==
          public:
            //  -- Getters --
            double get_area() const { return (m_area); }
            const math::Vec<3>& get_pos(const size_t t_index) const { return (m_pos[t_index]); }
            const math::Vec<3>& get_norm(const size_t t_index) const { return (m_norm[t_index]); }

            //  -- Geometric --
            double plane_dist(const math::Vec<3>& t_pos) const;
            std::array<double, 3> get_barycentric_coor(const math::Vec<3>& t_pos) const;
            bool within_tri(const math::Vec<3>& t_pos, double t_tol = 1.0e-18) const;
            std::pair<bool, double> intersection_dist(const math::Vec<3>& t_pos, const math::Vec<3>& t_dir,
                                                      double t_tol = std::numeric_limits<double>::min()) const;
            math::Vec<3> get_norm(const math::Vec<3>& t_pos) const;

            //  -- Generation --
            std::pair<math::Vec<3>, math::Vec<3>> gen_random_pos_and_norm() const;

            /**
 *  Get the intersection distance and normal of a ray and the triangle.
 *  If the given ray does not intersect the triangle, return a large distance and a zero length vector.
 *
 *  @param  t_pos   Start position of the ray.
 *  @param  t_dir   Direction of the ray.
 *
 *  @pre    t_dir must be normalised.
 *
 *  @post   r_i_dot_n must be less than pi/2.
 *
 *  @return The distance to intersection, and the consistent normal at the intersection point.
 */
            std::pair<double, math::Vec<3>> get_intersection(const math::Vec<3>& t_pos, const math::Vec<3>& t_dir) const
            {
                assert(t_dir.is_normalised());

                // Calculate edge vectors.
                const math::Vec<3> edge_1 = m_pos[BETA] - m_pos[ALPHA];
                const math::Vec<3> edge_2 = m_pos[GAMMA] - m_pos[ALPHA];

                const math::Vec<3> t = t_dir ^edge_2;
                const double       a = edge_1 * t;

                // Check if ray is almost parallel to the triangle.
                if (std::fabs(a) <= std::numeric_limits<double>::epsilon())
                {
                    // Does not hit triangle.
                    return (std::pair<double, math::Vec<3>>(std::numeric_limits<double>::max(), math::Vec<3>(0.0, 0.0, 0.0)));
                }

                const math::Vec<3> s = (t_pos - m_pos[ALPHA]) / a;
                const math::Vec<3> r = s ^edge_1;

                // Calculate barycentric coordinates.
                const double gamma = r * t_dir;
                const double beta  = s * t;
                const double alpha = 1.0 - beta - gamma;

                // Check hit is on triangle (rather than somewhere else in the plane).
                if ((alpha < 0.0) || (beta < 0.0) || (gamma < 0.0))
                {
                    // Does not hit triangle.
                    return (std::pair<double, math::Vec<3>>(std::numeric_limits<double>::max(), math::Vec<3>(0.0, 0.0, 0.0)));
                }

                // Calculate intersection distance.
                const double r_dist = edge_2 * r;

                // Check triangle is ahead of ray, rather than behind.
                if (r_dist <= 0.0)
                {
                    // Does not hit triangle.
                    return (std::pair<double, math::Vec<3>>(std::numeric_limits<double>::max(), math::Vec<3>(0.0, 0.0, 0.0)));
                }

                // Determine interpolated normal.
                const math::Vec<3> r_norm = math::normalise(
                    (m_norm[ALPHA] * alpha) + (m_norm[BETA] * beta) + (m_norm[GAMMA] * gamma));

                return (std::pair<double, math::Vec<3>>(r_dist, r_norm));
            }
        };



    } // namespace geom
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GEOM_TRIANGLE_HPP
