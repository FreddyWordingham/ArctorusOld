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
            m_plane_norm(init_plane_norm(t_pos, t_norm)),
            m_pos(t_pos),
            m_norm(t_norm)
        {
            assert(m_norm[ALPHA].is_normalised());
            assert(m_norm[BETA].is_normalised());
            assert(m_norm[GAMMA].is_normalised());
            assert(m_area >= 0.0);
            assert(m_plane_norm.is_normalised());
        }


        //  -- Initialisation --
        /**
         *  Initialise the normal vector of the triangle by determining the cross-product of two of the triangles edges.
         *  Normal must be normalised after determining the cross-product.
         *
         *  @param  t_pos   Array of vertex positions.
         *  @param  t_norm  Array of vertex normals.
         *
         *  @post   r_plane_norm must be normalised.
         *  @post   r_plane_norm * t_norm[ALPHA] must be greater than zero.
         *  @post   r_plane_norm * t_norm[BETA] must be greater than zero.
         *  @post   r_plane_norm * t_norm[GAMMA] must be greater than zero.
         *
         *  @return The normal vector of the triangle.
         */
        math::Vec<3> Triangle::init_plane_norm(const std::array<math::Vec<3>, 3>& t_pos,
                                               const std::array<math::Vec<3>, 3>& t_norm) const
        {
            // Compute the cross-product of two edges to find the triangle's normal.
            math::Vec<3> r_plane_norm = math::normalise((t_pos[BETA] - t_pos[ALPHA]) ^ (t_pos[GAMMA] - t_pos[ALPHA]));

            // Mirror the plane normal if it faces away from the vertex normals.
            if ((r_plane_norm * (t_norm[ALPHA] + t_norm[BETA] + t_norm[GAMMA])) < 0.0)
            {
                r_plane_norm *= -1.0;
            }

            assert(r_plane_norm.is_normalised());
            assert((r_plane_norm * t_norm[ALPHA]) > 0.0);
            assert((r_plane_norm * t_norm[BETA]) > 0.0);
            assert((r_plane_norm * t_norm[GAMMA]) > 0.0);

            return (r_plane_norm);
        }



        //  == METHODS ==
        //  -- Geometric --
        /**
         *  Determine if a ray intersects the triangle and also the distance until intersection.
         *  Note that a signalling NaN is returned as the distance when an intersection does not occur.
         *  This means that intersection status should be checked before distance is used if intersection is not guaranteed.
         *  Algoritm adapted from 'Fast Minimum Storage RayTriangle Intersection' by Tomal Moller et al.
         *
         *  @param  t_pos   Initial position of the ray.
         *  @param  t_dir   Direction of the ray.
         *  @param  t_tol   Tolerance used to determine if ray is parallel to the triangle surface.
         *
         *  @pre    t_dir must be normalised.
         *  @pre    t_tol must be positive.
         *
         *  @return True if intersection occurs and the distance until ray-triangle intersection.
         */
        std::pair<bool, double> Triangle::intersection_dist(const math::Vec<3>& t_pos, const math::Vec<3>& t_dir,
                                                            const double t_tol) const
        {
            assert(t_dir.is_normalised());
            assert(t_tol >= 0.0);

            // Calculate edge vectors sharing vertex alpha.
            const math::Vec<3> edge_alpha_beta  = m_pos[BETA] - m_pos[ALPHA];
            const math::Vec<3> edge_alpha_gamma = m_pos[GAMMA] - m_pos[ALPHA];

            // Calculate determinant.
            const math::Vec<3> p   = t_dir ^edge_alpha_gamma;
            const double       det = edge_alpha_beta * p;

            // Check if ray is parallel to the triangle surface.
            if (std::abs(det) < t_tol)
            {
                return (std::pair<bool, double>(false, std::numeric_limits<double>::signaling_NaN()));
            }

            // Calculate first barycentric coordinate and test bounds.
            const math::Vec<3> t = t_pos - m_pos[ALPHA];
            const double       u = (t * p) / det;

            // If u is not between zero and unity, the intersection with the plane is not inside the triangle.
            if ((u < 0.0) || (u > 1.0))
            {
                return (std::pair<bool, double>(false, std::numeric_limits<double>::signaling_NaN()));
            }

            // Calculate second barycentric coordinate and test bounds.
            const math::Vec<3> q = t ^edge_alpha_beta;
            const double       v = (t_dir * q) / det;

            // Test if intersection falls outside of triangle.
            if ((v < 0.0) || ((u + v) > 1.0))
            {
                return (std::pair<bool, double>(false, std::numeric_limits<double>::signaling_NaN()));
            }

            // Calculate distance to intersection.
            const double r_dist = (edge_alpha_gamma * q) / det;

            // Check if triangle is behind ray.
            if (r_dist < 0.0)
            {
                return (std::pair<bool, double>(false, std::numeric_limits<double>::signaling_NaN()));
            }

            return (std::pair<bool, double>(true, r_dist));
        }


        //  -- Generation --
        /**
         *  Generate a random position on the triangle's surface and determine the associated normal.
         *  Position and normal are stored together in an array.
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

            return (std::make_pair(r_pos, r_norm));
        }



    } // namespace geom
} // namespace arc
