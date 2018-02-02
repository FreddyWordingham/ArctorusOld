/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   02/02/2018.
 */



//  == HEADER ==
#include "cls/graphical/shader/normal.hpp"



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
             *  Construct a normal shader.
             *
             *  @param  t_vert_serial   Serialised source code of the vertex shader.
             *  @param  t_geom_serial   Serialised source code of the geometry shader.
             *  @param  t_frag_serial   Serialised source code of the fragment shader.
             */
            Normal::Normal(const std::string& t_vert_serial, const std::string& t_geom_serial, const std::string& t_frag_serial) :
                Shader(t_vert_serial, t_geom_serial, t_frag_serial),
                m_mvp_uni(init_uniform("mvp")),
                m_col_uni(init_uniform("prop_col"))
            {
            }



        } // namespace shader
    } // namespace graphical
} // namespace arc
