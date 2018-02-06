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
        //  -- Transformation --
        /**
         *  Transform a triangle's vertices using a given position and normal transformation matrix.
         *
         *  @param  t_pos_trans_mat Position transformation matrix.
         *  @param  t_dir_trans_mat Normal transformation matrix.
         */
        void Triangle::transform(const math::Mat<4, 4>& t_pos_trans_mat, const math::Mat<4, 4>& t_dir_trans_mat)
        {
            m_vert[ALPHA].transform(t_pos_trans_mat, t_dir_trans_mat);
            m_vert[BETA].transform(t_pos_trans_mat, t_dir_trans_mat);
            m_vert[GAMMA].transform(t_pos_trans_mat, t_dir_trans_mat);
        }



    } // namespace geom
} // namespace arc
