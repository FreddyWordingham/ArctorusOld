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
             *  @param  t_path  Path to the directory containing the diffuse sub-shader programs.
             */
            Normal::Normal(const std::string& t_path) :
                Shader(t_path, true),
                m_mvp_uni(init_uniform("mvp")),
                m_col_uni(init_uniform("prop_col")),
                m_light_power_uni(init_uniform("light_power"))
            {
            }



        } // namespace shader
    } // namespace graphical
} // namespace arc
