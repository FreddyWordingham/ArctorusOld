/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   01/02/2018.
 */



//  == HEADER ==
#include "cls/graphical/shader.hpp"



//  == INCLUDES ==
//  -- System --



//  == NAMESPACE ==
namespace arc
{
    namespace graphical
    {



        //  == INSTANTIATION ==
        //  -- Constructors --
        /**
         *  Construct a shader object from individual geometry, vertex and fragment serialised shader codes.
         *
         *  @param  t_geom_serial   Serialised source code of the geometry shader.
         *  @param  t_vert_serial   Serialised source code of the vertex shader.
         *  @param  t_frag_serial   Serialised source code of the fragment shader.
         */
        Shader::Shader(const std::string& t_geom_serial, const std::string& t_vert_serial, const std::string& t_frag_serial) :
            m_handle(init_handle(t_geom_serial, t_vert_serial, t_frag_serial))
        {
        }


        //  -- Initialisation --



    } // namespace graphical
} // namespace arc
