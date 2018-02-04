/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   01/02/2018.
 */



//  == HEADER ==
#include "cls/graphical/shader.hpp"



//  == INCLUDES ==
//  -- General --
#include "gen/log.hpp"



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
         *  @param  t_vert_serial   Serialised source code of the vertex shader.
         *  @param  t_geom_serial   Serialised source code of the geometry shader.
         *  @param  t_frag_serial   Serialised source code of the fragment shader.
         */
        Shader::Shader(const std::string& t_vert_serial, const std::string& t_geom_serial, const std::string& t_frag_serial) :
            m_handle(init_handle(t_vert_serial, t_geom_serial, t_frag_serial))
        {
        }


        //  -- Initialisation --
        /**
         *  Compile the full shader program and return the handle to it.
         *
         *  @param  t_vert_serial   Serialised source code of the vertex shader.
         *  @param  t_geom_serial   Serialised source code of the geometry shader.
         *  @param  t_frag_serial   Serialised source code of the fragment shader.
         *
         *  @return The handle to the initialised shader program.
         */
        GLuint Shader::init_handle(const std::string& t_vert_serial, const std::string& t_geom_serial, const std::string& t_frag_serial) const
        {
            // Track if compilation was successful.
            GLint success;

            // Compile the vertex shader.
            const char* vert_code = t_vert_serial.c_str();
            GLuint vert_shader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vert_shader, 1, &vert_code, nullptr);
            glCompileShader(vert_shader);

            // Check that the vertex shader compiled successfully.
            glGetShaderiv(vert_shader, GL_COMPILE_STATUS, &success);
            if (success == GL_FALSE)
            {
                GLint log_length;
                glGetShaderiv(vert_shader, GL_INFO_LOG_LENGTH, &log_length);
                std::vector<char> error_log(static_cast<size_t>(log_length));

                glGetShaderInfoLog(vert_shader, log_length, nullptr, error_log.data());
                std::string error_text(begin(error_log), end(error_log));

                ERROR("Unable to construct graphical::Shader object.",
                      "Vertex shader compilation failed with error: '" << error_text << "'.");
            }

            // Compile the geometry shader.
            GLuint geom_shader = 0;
            if (!t_geom_serial.empty())
            {
                const char* geom_code = t_geom_serial.c_str();
                geom_shader = glCreateShader(GL_GEOMETRY_SHADER);
                glShaderSource(geom_shader, 1, &geom_code, nullptr);
                glCompileShader(geom_shader);

                // Check that the vertex shader compiled successfully.
                glGetShaderiv(geom_shader, GL_COMPILE_STATUS, &success);
                if (success == GL_FALSE)
                {
                    GLint log_length;
                    glGetShaderiv(geom_shader, GL_INFO_LOG_LENGTH, &log_length);
                    std::vector<char> error_log(static_cast<size_t>(log_length));

                    glGetShaderInfoLog(geom_shader, log_length, nullptr, error_log.data());
                    std::string error_text(begin(error_log), end(error_log));

                    ERROR("Unable to construct graphical::Shader object.",
                          "Geometry shader compilation failed with error: '" << error_text << "'.");
                }
            }

            // Compile the fragment shader.
            const char* frag_code = t_frag_serial.c_str();
            GLuint frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(frag_shader, 1, &frag_code, nullptr);
            glCompileShader(frag_shader);

            // Check that the fragment shader compiled successfully.
            glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &success);
            if (success == GL_FALSE)
            {
                GLint log_length;
                glGetShaderiv(frag_shader, GL_INFO_LOG_LENGTH, &log_length);
                std::vector<char> error_log(static_cast<size_t>(log_length));

                glGetShaderInfoLog(frag_shader, log_length, nullptr, error_log.data());
                std::string error_text(begin(error_log), end(error_log));

                ERROR("Unable to construct graphical::Shader object.",
                      "Fragment shader compilation failed with error: '" << error_text << "'.");
            }

            // Compile the complete shader.
            GLuint r_handle = glCreateProgram();
            glAttachShader(r_handle, vert_shader);
            if (!t_geom_serial.empty())
            {
                glAttachShader(r_handle, geom_shader);
            }
            glAttachShader(r_handle, frag_shader);
            glLinkProgram(r_handle);

            // Check that the complete shader compiled successfully.
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

            // Clean up temporary shaders.
            glDeleteShader(vert_shader);
            if (!t_geom_serial.empty())
            {
                glDeleteShader(geom_shader);
            }
            glDeleteShader(frag_shader);

            return (r_handle);
        }

        /**
         *  Initialise a sub-shader.
         *
         *  @param  t_serial    Serialised source code of the sub-shader.
         *  @param  t_type      Type of sub-shader to be initialised.
         *
         *  @return The handle to the initialised sub-shader program.
         */
        GLuint Shader::init_sub_shader(const std::string& t_serial, const GLenum t_type) const
        {
            // Compile the vertex shader.
            const char* code = t_serial.c_str();
            GLuint r_sub_shader = glCreateShader(t_type);
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
                std::string error_text(begin(error_log), end(error_log));

                ERROR("Unable to construct graphical::Shader object.",
                      "Shader type: '" << t_type << "', compilation failed with error: '" << error_text << "'.");
            }

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
