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
             */
            Ambient::Ambient() :
                Shader(AMBIENT_SHADER_DIR, false),
                m_mvp_uni(init_uniform("mvp")),
                m_col_uni(init_uniform("prop_col"))
            {
            }



        } // namespace shader
    } // namespace graphical
} // namespace arc
