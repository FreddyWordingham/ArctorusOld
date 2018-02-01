/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   01/02/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_GRAPHICAL_SHADER_HPP
#define ARCTORUS_SRC_CLS_GRAPHICAL_SHADER_HPP



//  == INCLUDES ==
//  -- System --
#include <GL/glew.h>
#include <string>



//  == NAMESPACE ==
namespace arc
{
    namespace graphical
    {



        //  == CLASS ==
        /**
         *  Base shader class.
         *  Complex shaders should be derived from this base class.
         */
        class Shader
        {
            //  == FIELDS ==
          private:
            //  -- Program --
            const GLuint m_handle;  //! Handle to the compiled shader program.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            Shader(const std::string& t_geom_serial, const std::string& t_vert_serial, const std::string& t_frag_serial);

          private:
            //  -- Initialisation --
            GLuint init_handle(const std::string& t_geom_serial, const std::string& t_vert_serial, const std::string& t_frag_serial) const;
            GLint init_uniform(const std::string& t_uni_name) const;


            //  == METHODS ==
          private:
        };



    } // namespace graphical
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GRAPHICAL_SHADER_HPP
