/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   29/01/2018.
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



        //  == SETTINGS ==
        //  -- Uniforms --
        constexpr const char* MVP_UNIFORM_NAME = "mvp";    //! Name of the mvp matrix uniform within the shader.



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

            //  -- Uniforms --
            const GLint m_mvp;  //! Model-view-projection uniform handle.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            Shader(const std::string& t_vert_serial, const std::string& t_frag_serial);

          protected:
            //  -- Initialisation --
            GLuint init_handle(const std::string& t_vert_serial, const std::string& t_frag_serial) const;
            GLint init_uniform(const std::string& t_uni_name) const;


            //  == METHODS ==
          public:
            //  -- Getters --
            GLuint get_handle() const { return (m_handle); }
            GLint get_mvp() const { return (m_mvp); }
        };



    } // namespace graphical
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GRAPHICAL_SHADER_HPP
