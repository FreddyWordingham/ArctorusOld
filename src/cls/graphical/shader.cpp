/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   01/02/2018.
 */



//  == MODULE ==
#include "gen/config.hpp"
#ifdef ENABLE_GRAPHICS



//  == HEADER ==
#include "cls/graphical/shader.hpp"



//  == INCLUDES ==
//  -- General --
#include "gen/log.hpp"

//  -- Classes --
#include "cls/file/handle.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace graphical
    {



        //  == INSTANTIATION ==
        //  -- Constructors --
        /**
         *  Construct a shader object from individual sub-shader codes.
         *
         *  @param  t_path          Path to the directory containing the sub-shader programs.
         *  @param  t_geom_shader   When true also load a geometry sub-shader.
         */
        Shader::Shader(const std::string& t_path, const bool t_geom_shader) :
            m_handle(init_handle(t_path, t_geom_shader))
        {
        }


        //  -- Initialisation --
        /**
         *  Compile the full shader program and return the handle to it.
         *
         *  @param  t_path          Path to the directory containing the sub-shader programs.
         *  @param  t_geom_shader   When true also load a geometry sub-shader.
         *
         *  @return The handle to the initialised shader program.
         */
        GLuint Shader::init_handle(const std::string& t_path, const bool t_geom_shader) const
        {
            // Initialise the sub-shaders.
            const GLuint vert_shader = init_sub_shader(SHADER_DIR + t_path + VERT_SHADER_FILENAME, GL_VERTEX_SHADER);
            const GLuint geom_shader = t_geom_shader ? init_sub_shader(SHADER_DIR + t_path + GEOM_SHADER_FILENAME,
                                                                       GL_GEOMETRY_SHADER) : 0;
            const GLuint frag_shader = init_sub_shader(SHADER_DIR + t_path + FRAG_SHADER_FILENAME, GL_FRAGMENT_SHADER);

            // Compile the complete shader.
            const GLuint r_handle = glCreateProgram();
            glAttachShader(r_handle, vert_shader);
            if (t_geom_shader)
            {
                glAttachShader(r_handle, geom_shader);
            }
            glAttachShader(r_handle, frag_shader);
            glLinkProgram(r_handle);

            // Check that the complete shader compiled successfully.
            GLint success;
            glGetProgramiv(r_handle, GL_LINK_STATUS, &success);
            if (success == GL_FALSE)
            {
                GLint log_length;
                glGetProgramiv(r_handle, GL_INFO_LOG_LENGTH, &log_length);
                std::vector<char> error_log(static_cast<size_t>(log_length));

                glGetProgramInfoLog(r_handle, log_length, nullptr, error_log.data());
                std::string error_text(begin(error_log), end(error_log));

                ERROR("Unable to construct graphical::Shader object.",
                      "Shader linking failed with error: '" << error_text << "'.");
            }

            // Clean up temporary sub-shaders.
            glDeleteShader(vert_shader);
            if (t_geom_shader)
            {
                glDeleteShader(geom_shader);
            }
            glDeleteShader(frag_shader);

            return (r_handle);
        }

        /**
         *  Initialise a sub-shader.
         *
         *  @param  t_path  Complete path to the sub-shader source file.
         *  @param  t_type  Type of sub-shader to be initialised.
         *
         *  @post   r_sub_shader must not equal zero.
         *
         *  @return The handle to the initialised sub-shader program.
         */
        GLuint Shader::init_sub_shader(const std::string& t_path, const GLenum t_type) const
        {
            // Load the shader source code.
            const std::string serial = file::read(t_path, false);
            const char* code = serial.c_str();

            // Compile the vertex shader.
            const GLuint r_sub_shader = glCreateShader(t_type);
            glShaderSource(r_sub_shader, 1, &code, nullptr);
            glCompileShader(r_sub_shader);

            // Check that the vertex shader compiled successfully.
            GLint success;
            glGetShaderiv(r_sub_shader, GL_COMPILE_STATUS, &success);
            if (success == GL_FALSE)
            {
                GLint log_length;
                glGetShaderiv(r_sub_shader, GL_INFO_LOG_LENGTH, &log_length);
                std::vector<char> error_log(static_cast<size_t>(log_length));

                glGetShaderInfoLog(r_sub_shader, log_length, nullptr, error_log.data());
                const std::string error_text(begin(error_log), end(error_log));

                ERROR("Unable to construct graphical::Shader object.",
                      "Shader: '" << t_path << "', compilation failed with error: '" << error_text << "'.");
            }

            assert(r_sub_shader != 0);

            return (r_sub_shader);
        }

        /**
         *  Initialise a handle to a shader uniform using its name.
         *
         *  @param  t_uni_name  Name of the uniform to initialise.
         *
         *  @return The handle to the initialised shader uniform.
         */
        GLint Shader::init_uniform(const std::string& t_uni_name) const
        {
            GLint r_uniform = glGetUniformLocation(m_handle, t_uni_name.c_str());

            if (r_uniform < 0)
            {
                ERROR("Unable to construct graphical::Shader object.",
                      "Failed to determine the uniform location of: '" << t_uni_name << "' within the shader.");
            }

            return (r_uniform);
        }



    } // namespace graphical
} // namespace arc



//  == MODULE END ==
#endif
