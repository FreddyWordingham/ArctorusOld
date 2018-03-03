/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   02/02/2018.
 */



//  == MODULE ==
#include "gen/config.hpp"
#ifdef ENABLE_GRAPHICS



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
             */
            Normal::Normal() :
                Shader(NORMAL_SHADER_DIR, true),
                m_mvp_uni(init_uniform("mvp")),
                m_col_uni(init_uniform("col")),
                m_light_power_uni(init_uniform("light_power"))
            {
            }



        } // namespace shader
    } // namespace graphical
} // namespace arc



//  == MODULE END ==
#endif
