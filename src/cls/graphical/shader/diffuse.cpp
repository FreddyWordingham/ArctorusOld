/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   02/02/2018.
 */



//  == HEADER ==
#include "cls/graphical/shader/diffuse.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace graphical
    {
        namespace shader
        {



            //  == INSTANTIATION ==
            //  -- Constructors --
            /**
             *  Construct a diffuse shader.
             *
             *  @param  t_vert_serial   Serialised source code of the vertex shader.
             *  @param  t_frag_serial   Serialised source code of the fragment shader.
             */
            Diffuse::Diffuse(const std::string& t_vert_serial, const std::string& t_frag_serial) :
                Shader(t_vert_serial, t_frag_serial),
                m_mvp_uni(init_uniform("mvp")),
                m_view_uni(init_uniform("view")),
                m_col_uni(init_uniform("col")),
                m_sun_pos_uni(init_uniform("sun_pos")),
                m_amb_pow_uni(init_uniform("amb_pow"))
            {
            }



        } // namespace shader
    } // namespace graphical
} // namespace arc
