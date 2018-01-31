/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   31/01/2018.
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
             *  Construct an diffuse shader.
             *
             *  @param  t_vert_serial   Serialised source code of the vertex shader.
             *  @param  t_frag_serial   Serialised source code of the fragment shader.
             */
            Diffuse::Diffuse(const std::string& t_vert_serial, const std::string& t_frag_serial) :
                Shader(t_vert_serial, t_frag_serial),
                m_view(init_uniform(VIEW_MAT_UNIFORM_NAME)),
                m_prop_col(init_uniform(PROP_COL_UNIFORM_NAME)),
                m_light_pos(init_uniform(LIGHT_POS_UNIFORM_NAME))
            {
            }



        } // namespace shader
    } // namespace graphical
} // namespace arc
