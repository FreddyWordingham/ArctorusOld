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
#include "gen/math.hpp"



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
         */
        Triangle::Triangle(const std::array<Vertex, 3>& t_vert) :
            m_vert(t_vert),
            m_area(math::area({{m_vert[ALPHA].get_pos(), m_vert[BETA].get_pos(), m_vert[GAMMA].get_pos()}}))
        {
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
            std::array<math::Vec<3>, 2> r_vec{};

            // Generate a pair of random barycentric coordinates.
            const double x = rng::random();
            const double y = rng::random();

            // If the generated coordinate falls beyond the triangle, mirror it back inside.
            if ((x + y) > 1.0)
            {
                x = 1.0 - x;
                y  = 1.0 - y;
            }

            return (r_vec);
        }

        //  -- Transformation --
        /**
         *  Transform a triangle's vertices using a given position and normal transformation matrix.
         *
         *  @param  t_pos_trans_mat Position transformation matrix.
         *  @param  t_dir_trans_mat Normal transformation matrix.
         */
        void Triangle::transform(const math::Mat<4, 4>& t_pos_trans_mat, const math::Mat<4, 4>& t_dir_trans_mat)
        {
            // Transform the vertices.
            m_vert[ALPHA].transform(t_pos_trans_mat, t_dir_trans_mat);
            m_vert[BETA].transform(t_pos_trans_mat, t_dir_trans_mat);
            m_vert[GAMMA].transform(t_pos_trans_mat, t_dir_trans_mat);

            // Recalculate the triangle's area.
            m_area = math::area({{m_vert[ALPHA].get_pos(), m_vert[BETA].get_pos(), m_vert[GAMMA].get_pos()}});
        }



    } // namespace geom
} // namespace arc
