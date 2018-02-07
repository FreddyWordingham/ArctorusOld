/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   04/02/2018.
 */



//  == HEADER ==
#include "cls/graphical/shader/path.hpp"



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
             *  Construct a path shader.
             */
            Path::Path() :
                Shader(PATH_SHADER_DIR, false),
                m_mvp_uni(init_uniform("mvp")),
                m_col_uni(init_uniform("prop_col")),
                m_render_time(init_uniform("time"))
            {
            }



        } // namespace shader
    } // namespace graphical
} // namespace arc
