/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   28/01/2018.
 */



//  == HEADER ==
#include "cls/geom/triangle.hpp"



//  == INCLUDES ==
//  -- General --



//  == NAMESPACE ==
namespace arc
{
    namespace geom
    {



        //  == INSTANTIATION ==
        //  -- Constructors --
        /**
         *  Construct a triangle from three vertices.
         *
         *  @param  t_vert  Array of three vertices forming the triangle.
         *
         *  @post   m_area must be positive.
         *  @post   m_norm must be normalised.
         */
        Triangle::Triangle(const std::array<Vertex, 3>& t_vert) :
            m_vert(t_vert),
            m_area(math::area({{m_vert[ALPHA].get_pos(), m_vert[BETA].get_pos(), m_vert[GAMMA].get_pos()}})),
            m_norm(init_norm())
        {
            assert(m_area > 0.0);
            assert(m_norm.is_normalised());
        }


        //  -- Initialisation --
        /**
         *  Initialise the normal vector of the triangle by determining the cross-product of two of the triangles edges.
         *  Normal must be normalised after determining the cross-product.
         *
         *  @post   r_norm must be normalised.
         *
         *  @return The normal vector of the triangle.
         */
        math::Vec<3> Triangle::init_norm() const
        {
            // Compute the cross-product of two edges to find the triangle's normal.
            math::Vec<3> r_norm = (m_vert[BETA].get_pos() - m_vert[ALPHA].get_pos()) ^ (m_vert[GAMMA].get_pos() - m_vert[ALPHA].get_pos());

            // Normalise the normal.
            r_norm.normalise();

            assert(r_norm.is_normalised());

            return (r_norm);
        }



        //  == METHODS ==
        //  -- Getters --
        /**
         *  Generate a random position on the triangle's surface and determine the associated normal.
         *
         *  @return A random position and associated normal on the triangle's surface.
         */
        std::array<math::Vec<3>, 2> Triangle::get_random_pos_and_norm() const
        {
            // Create return array.
            std::array<math::Vec<3>, 2> r_vec;

            // Generate a pair of random barycentric coordinates.
            double a = rng::random();
            double b = rng::random();

            // If the generated coordinate falls beyond the triangle, mirror it back inside.
            if ((a + b) > 1.0)
            {
                a = 1.0 - a;
                b = 1.0 - b;
            }

            // Generate the world-space cartesian coordinates from the barycentric coordinates.
            r_vec[0] = m_vert[GAMMA].get_pos() + ((m_vert[ALPHA].get_pos() - m_vert[GAMMA].get_pos()) * a) + ((m_vert[BETA]
                .get_pos() - m_vert[GAMMA].get_pos()) * b);
            r_vec[1] = (m_vert[ALPHA].get_norm() * a) + (m_vert[BETA].get_norm() * b) + (m_vert[GAMMA]
                .get_norm() * (1.0 - a - b));
            r_vec[1].normalise();

            return (r_vec);
        }



    } // namespace geom
} // namespace arc
