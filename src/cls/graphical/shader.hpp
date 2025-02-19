/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   01/02/2018.
 */



//  == MODULE ==
#include "gen/config.hpp"
#ifdef ENABLE_GRAPHICS



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
        //  -- Directories --
        constexpr const char* SHADER_DIR = "res/shaders/";  //! Path to the resource directory holding shader files.

        //  -- Filenames --
        constexpr const char* VERT_SHADER_FILENAME = "vertex.vert";   //! Name of the vertex sub-shader file.
        constexpr const char* GEOM_SHADER_FILENAME = "geometry.geom"; //! Name of the geometry sub-shader file.
        constexpr const char* FRAG_SHADER_FILENAME = "fragment.frag"; //! Name of the fragment sub-shader file.



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
            Shader(const std::string& t_path, bool t_geom_shader);

          private:
            //  -- Initialisation --
            GLuint init_handle(const std::string& t_path, bool t_geom_shader) const;
            GLuint init_sub_shader(const std::string& t_serial, GLenum t_type) const;

          protected:
            //  -- Initialisation --
            GLint init_uniform(const std::string& t_uni_name) const;


            //  == METHODS ==
          public:
            //  -- Getters --
            GLuint get_handle() const { return (m_handle); }
        };



    } // namespace graphical
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GRAPHICAL_SHADER_HPP



//  == MODULE END ==
#endif
