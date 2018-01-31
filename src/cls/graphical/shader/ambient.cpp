/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   29/01/2018.
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
             *  @param  t_vert_serial   Serialised source code of the vertex shader.
             *  @param  t_frag_serial   Serialised source code of the fragment shader.
             */
            Ambient::Ambient(const std::string& t_vert_serial, const std::string& t_frag_serial) :
                Shader(t_vert_serial, t_frag_serial)
            {
            }




        } // namespace shader
    } // namespace graphical
} // namespace arc
