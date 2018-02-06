/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   31/01/2018.
 */



//  == HEADER ==
#include "cls/geom/vertex.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace geom
    {



        //  == INSTANTIATION ==
        //  -- Constructors --
        /**
         *  Construct a vertex from a given position and normal.
         *
         *  @param  t_pos   Position of the vertex.
         *  @param  t_norm  Normal direction associated with the vertex.
         *
         *  @post   t_norm must be normalised.
         */
        Vertex::Vertex(const math::Vec<3>& t_pos, const math::Vec<3>& t_norm) :
            m_pos(t_pos),
            m_norm(t_norm)
        {
            assert(t_norm.is_normalised());
        }



        //  == METHODS ==
        //  -- Transformation --
        /**
         *  Transform a vector using a given position and normal transformation matrix.
         *
         *  @param  t_pos_trans_mat Position transformation matrix.
         *  @param  t_dir_trans_mat Normal transformation matrix.
         */
        void Vertex::transform(const math::Mat<4, 4>& t_pos_trans_mat, const math::Mat<4, 4>& t_dir_trans_mat)
        {
            // Calculate the position transform.
            math::Vec<4> pos({{m_pos[X], m_pos[Y], m_pos[Z], 1.0}});
            pos *= t_pos_trans_mat;
            m_pos[X] = pos[X];
            m_pos[Y] = pos[Y];
            m_pos[Z] = pos[Z];

            // Calculate the normal transform.
            math::Vec<4> norm({{m_norm[X], m_norm[Y], m_norm[Z], 1.0}});
            norm *= t_dir_trans_mat;
            m_norm[X] = norm[X];
            m_norm[Y] = norm[Y];
            m_norm[Z] = norm[Z];
        }



    } // namespace geom
} // namespace arc
