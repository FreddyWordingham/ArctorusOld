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
            math::Vec<3> r_norm = (m_vert[BETA].get_pos() - m_vert[ALPHA].get_pos()) ^(m_vert[GAMMA].get_pos() - m_vert[ALPHA]
                .get_pos());

            // Normalise the normal.
            r_norm.normalise();

            assert(r_norm.is_normalised());

            return (r_norm);
        }



        //  == METHODS ==
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
            const math::Vec<3> r_pos = m_vert[GAMMA].get_pos() + ((m_vert[ALPHA].get_pos() - m_vert[GAMMA]
                .get_pos()) * a) + ((m_vert[BETA].get_pos() - m_vert[GAMMA].get_pos()) * b);

            // Calculate the corresponding normal.
            const math::Vec<3> r_norm = math::normalise(
                (m_vert[ALPHA].get_norm() * a) + (m_vert[BETA].get_norm() * b) + (m_vert[GAMMA].get_norm() * (1.0 - a - b)));

            return (std::make_pair(r_pos, r_norm));
        }



    } // namespace geom
} // namespace arc
