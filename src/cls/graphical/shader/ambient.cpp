/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   01/02/2018.
 */



//  == HEADER ==
#include "cls/graphical/shader/ambient.hpp"



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
             *  Construct an ambient shader.
             *
             *  @param  t_geom_serial   Serialised source code of the geometry shader.
             *  @param  t_vert_serial   Serialised source code of the vertex shader.
             *  @param  t_frag_serial   Serialised source code of the fragment shader.
             */
            Ambient::Ambient(const std::string& t_geom_serial, const std::string& t_vert_serial, const std::string& t_frag_serial) :
                Shader(t_geom_serial, t_vert_serial, t_frag_serial),
                m_mvp_uni(init_uniform("mvp")),
                m_col_uni(init_uniform("col"))
            {
            }



        } // namespace shader
    } // namespace graphical
} // namespace arc
