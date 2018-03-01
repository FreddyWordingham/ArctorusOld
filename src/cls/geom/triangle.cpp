/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   28/01/2018.
 */



//  == HEADER ==
#include "cls/geom/triangle.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace geom
    {



        //  == INSTANTIATION ==
        //  -- Constructors --
        /**
         *  Construct a triangle from an array of given vertex positions and an array of the associated vertex normals.
         *
         *  @param  t_pos   Array of vertex positions.
         *  @param  t_norm  Array of vertex normals.
         *
         *  @post   m_norm[ALPHA] must be normalised.
         *  @post   m_norm[BETA] must be normalised.
         *  @post   m_norm[GAMMA] must be normalised.
         *  @post   m_area must be non-negative.
         *  @post   m_plane_norm must be normalised.
         */
        Triangle::Triangle(const std::array<math::Vec<3>, 3>& t_pos, const std::array<math::Vec<3>, 3>& t_norm) :
            m_area(math::area(t_pos)),
            m_plane_norm(math::normalise((t_pos[BETA] - t_pos[ALPHA]) ^ (t_pos[GAMMA] - t_pos[ALPHA]))),
            m_pos(t_pos),
            m_norm(t_norm),
            m_cons(std::acos(), ,),
        {
            assert(m_norm[ALPHA].is_normalised());
            assert(m_norm[BETA].is_normalised());
            assert(m_norm[GAMMA].is_normalised());
            assert(m_area >= 0.0);
            assert(m_plane_norm.is_normalised());
        }



        //  == METHODS ==
        //  -- Getters --
        /**
         *  Get the intersection distance and normal of a ray and the triangle.
         *  If the given ray does not intersect the triangle, return a large distance and a zero length vector.
         *
         *  @param  t_pos   Start position of the ray.
         *  @param  t_dir   Direction of the ray.
         *
         *  @return The distance to intersection, and the normal of the triangle at the intersection point.
         */
        std::pair<double, math::Vec<3>> Triangle::get_intersection(const math::Vec<3>& t_pos, const math::Vec<3>& t_dir) const
        {
            assert(t_dir.is_normalised());

            // Calculate edge vectors.
            const math::Vec<3> edge_1 = m_pos[BETA] - m_pos[ALPHA];
            const math::Vec<3> edge_2 = m_pos[GAMMA] - m_pos[ALPHA];

            const math::Vec<3> q = t_dir ^edge_2;
            const double       a = edge_1 * q;

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
            const double beta  = s * q;
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
            math::Vec<3> r_norm = math::normalise((m_norm[ALPHA] * alpha) + (m_norm[BETA] * beta) + (m_norm[GAMMA] * gamma));

            return (std::pair<double, math::Vec<3>>(r_dist, r_norm));
        }


        //  -- Generation --
        /**
         *  Generate a random position on the triangle's surface and determine the associated normal.
         *  Position and normal are stored together in an array.
         *
         *  @post   r_norm must be normalised.
         *
         *  @return A random position and associated normal on the triangle's surface.
         */
        std::pair<math::Vec<3>, math::Vec<3>> Triangle::gen_random_pos_and_norm() const
        {
            // Generate a pair of random barycentric coordinates.
            double a = rng::random();
            double b = rng::random();

            // If the generated coordinate falls beyond the triangle, mirror it back inside.
            if ((a + b) > 1.0)
            {
                a = 1.0 - a;
                b = 1.0 - b;
            }

            // Calculate the world-space cartesian coordinates from the barycentric coordinates.
            const math::Vec<3> r_pos = m_pos[GAMMA] + ((m_pos[ALPHA] - m_pos[GAMMA]) * a) + ((m_pos[BETA] - m_pos[GAMMA]) * b);

            // Calculate the corresponding normal.
            const math::Vec<3> r_norm = math::normalise(
                (m_norm[ALPHA] * a) + (m_norm[BETA] * b) + (m_norm[GAMMA] * (1.0 - a - b)));

            assert(r_norm.is_normalised());

            return (std::make_pair(r_pos, r_norm));
        }



    } // namespace geom
} // namespace arc
