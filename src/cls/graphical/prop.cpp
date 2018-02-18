/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   02/02/2018.
 */



//  == HEADER ==
#include "cls/graphical/prop.hpp"



//  == INCLUDES ==
//  -- General --
#include "gen/enum.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace graphical
    {



        //  == INSTANTIATION ==
        //  -- Constructors --
        /**
         *  Construct a prop to be rendered.
         *
         *  @param  t_vert  Vector of vertices forming the prop.
         *  @param  t_col   Colour of the prop.
         *
         *  @post   m_col.r must be greater than, or equal to, zero and less than, or equal to, one.
         *  @post   m_col.g must be greater than, or equal to, zero and less than, or equal to, one.
         *  @post   m_col.b must be greater than, or equal to, zero and less than, or equal to, one.
         *  @post   m_col.a must be greater than, or equal to, zero and less than, or equal to, one.
         */
        Prop::Prop(const std::vector<Vertex>& t_vert, const glm::vec4& t_col) :
            m_num_vert(static_cast<GLsizei>(t_vert.size())),
            m_col(t_col),
            m_vao(init_vao()),
            m_vbo(init_vbo())
        {
            // Create vertex array object and vertex buffer object.
            glBindVertexArray(m_vao);
            glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
            glBufferData(GL_ARRAY_BUFFER, static_cast<size_t>(m_num_vert) * sizeof(Vertex), &t_vert.front(), GL_STATIC_DRAW);

            // Enable the vertex position layout location.
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(0));
            glEnableVertexAttribArray(0);

            // Enable the vertex normal layout location.
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat)));
            glEnableVertexAttribArray(1);

            // Bind the buffer object.
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            // Clear the active buffer.
            glBindVertexArray(0);

            assert((m_col.r >= 0.0f) && (m_col.r <= 1.0f));
            assert((m_col.g >= 0.0f) && (m_col.g <= 1.0f));
            assert((m_col.b >= 0.0f) && (m_col.b <= 1.0f));
            assert((m_col.a >= 0.0f) && (m_col.a <= 1.0f));
        }

        /**
         *  Construct a basic prop using a given shape type, colour and scale.
         *
         *  @param  t_shape Type of shape to be created.
         *  @param  t_col   Colour of the shape.
         *  @param  t_scale Scaling to be applied to the shape.
         */
        Prop::Prop(const shape t_shape, const glm::vec4& t_col, const float t_scale) :
            Prop(init_vert(t_shape, t_scale), t_col)
        {
        }

        /**
         *  Construct a basic prop using a given shape type, colour and bounds.
         *
         *  @param  t_shape Type of shape to be created.
         *  @param  t_col   Colour of the shape.
         *  @param  t_min   Minimum bound of the box.
         *  @param  t_max   Maximum bound of the box.
         */
        Prop::Prop(const shape t_shape, const glm::vec4& t_col, const glm::vec3& t_min, const glm::vec3& t_max) :
            Prop(init_vert(t_shape, t_min, t_max), t_col)
        {
        }

        /**
         *  Construct a photon packet path prop from a vector of photon positions.
         *
         *  @param  t_phot  Vector of photon point paths.
         *  @param  t_col   Default colour of the photon path.
         */
        Prop::Prop(const std::vector<point::Photon>& t_phot, const glm::vec4& t_col) :
            m_num_vert(static_cast<GLsizei>(t_phot.size())),
            m_col(t_col),
            m_vao(init_vao()),
            m_vbo(init_vbo())
        {
            // Create vertex array object and vertex buffer object.
            glBindVertexArray(m_vao);
            glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
            glBufferData(GL_ARRAY_BUFFER, static_cast<size_t>(m_num_vert) * sizeof(point::Photon), &t_phot.front(),
                         GL_STATIC_DRAW);

            // Enable the photon packet position layout location.
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(point::Photon), reinterpret_cast<GLvoid*>(0));
            glEnableVertexAttribArray(0);

            // Enable the photon packet wavelength layout location.
            glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(point::Photon),
                                  reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat)));
            glEnableVertexAttribArray(1);

            // Enable the photon packet statistical weight layout location.
            glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(point::Photon),
                                  reinterpret_cast<GLvoid*>(4 * sizeof(GLfloat)));
            glEnableVertexAttribArray(2);

            // Enable the photon packet time travelled layout location.
            glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(point::Photon),
                                  reinterpret_cast<GLvoid*>(5 * sizeof(GLfloat)));
            glEnableVertexAttribArray(3);

            // Bind the buffer object.
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            // Clear the active buffer.
            glBindVertexArray(0);
        }


        //  -- Initialisation --
        /**
         *  Initialise the handle to the prop's vao.
         *
         *  @return Handle to the prop's vao.
         */
        GLuint Prop::init_vao() const
        {
            // Create vertex array object handle.
            GLuint r_vao;

            // Initialise the vertex array object handle.
            glGenVertexArrays(1, &r_vao);

            return (r_vao);
        }

        /**
         *  Initialise the handle to the prop's vbo.
         *
         *  @return Handle to the prop's vbo.
         */
        GLuint Prop::init_vbo() const
        {
            // Create vertex buffer object handle.
            GLuint r_vbo;

            // Initialise the vertex buffer object handle.
            glGenBuffers(1, &r_vbo);

            return (r_vbo);
        }

        /**
         *  Initialise the vertices for a simple prop shape.
         *
         *  @param  t_shape Type of shape to be created.
         *  @param  t_scale Scaling to be applied to the shape.
         *
         *  @return The initialised vector of vertices for the simple shape.
         */
        std::vector<Vertex> Prop::init_vert(const shape t_shape, const float t_scale) const
        {
            switch (t_shape)
            {
                case shape::CUBE:
                    return (init_vert_cube(t_scale));
                case shape::SKYBOX:
                    return (init_vert_skybox(t_scale));
                case shape::SUN:
                    return (init_vert_sun(t_scale));
            }
        }

        /**
         *  Initialise the vertices for a simple, bounded, prop shape.
         *
         *  @param  t_shape Type of shape to be created.
         *  @param  t_min   Minimum bound of the box.
         *  @param  t_max   Maximum bound of the box.
         *
         *  @return The initialised vector of vertices for the simple shape.
         */
        std::vector<Vertex> Prop::init_vert(const shape t_shape, const glm::vec3 &t_min, const glm::vec3 &t_max) const
        {
            switch (t_shape)
            {
                case shape::BOX:
                    return (init_vert_box(t_min, t_max));
            }
        }

        /**
         *  Initialise the vertices for a simple cube prop shape.
         *
         *  @param  t_scale Size multiplier of the shape.
         *
         *  @return The initialised vector of vertices for a simple cube.
         */
        std::vector<Vertex> Prop::init_vert_cube(const float t_scale) const
        {
            // Create vertex vector.
            std::vector<Vertex> r_vert;

            // Reserve space for 36 vertices.
            r_vert.reserve(36);

            // Add face vertices into the vertex vector.
            r_vert.push_back(Vertex({-t_scale, -t_scale, -t_scale}, {-1.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({-t_scale, -t_scale, +t_scale}, {-1.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({-t_scale, +t_scale, +t_scale}, {-1.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({+t_scale, +t_scale, -t_scale}, {+0.0f, +0.0f, -1.0f}));
            r_vert.push_back(Vertex({-t_scale, -t_scale, -t_scale}, {+0.0f, +0.0f, -1.0f}));
            r_vert.push_back(Vertex({-t_scale, +t_scale, -t_scale}, {+0.0f, +0.0f, -1.0f}));

            r_vert.push_back(Vertex({+t_scale, -t_scale, +t_scale}, {+0.0f, -1.0f, +0.0f}));
            r_vert.push_back(Vertex({-t_scale, -t_scale, -t_scale}, {+0.0f, -1.0f, +0.0f}));
            r_vert.push_back(Vertex({+t_scale, -t_scale, -t_scale}, {+0.0f, -1.0f, +0.0f}));
            r_vert.push_back(Vertex({+t_scale, +t_scale, -t_scale}, {+0.0f, +0.0f, -1.0f}));
            r_vert.push_back(Vertex({+t_scale, -t_scale, -t_scale}, {+0.0f, +0.0f, -1.0f}));
            r_vert.push_back(Vertex({-t_scale, -t_scale, -t_scale}, {+0.0f, +0.0f, -1.0f}));

            r_vert.push_back(Vertex({-t_scale, -t_scale, -t_scale}, {-1.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({-t_scale, +t_scale, +t_scale}, {-1.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({-t_scale, +t_scale, -t_scale}, {-1.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({+t_scale, -t_scale, +t_scale}, {+0.0f, -1.0f, +0.0f}));
            r_vert.push_back(Vertex({-t_scale, -t_scale, +t_scale}, {+0.0f, -1.0f, +0.0f}));
            r_vert.push_back(Vertex({-t_scale, -t_scale, -t_scale}, {+0.0f, -1.0f, +0.0f}));

            r_vert.push_back(Vertex({-t_scale, +t_scale, +t_scale}, {+0.0f, +0.0f, +1.0f}));
            r_vert.push_back(Vertex({-t_scale, -t_scale, +t_scale}, {+0.0f, +0.0f, +1.0f}));
            r_vert.push_back(Vertex({+t_scale, -t_scale, +t_scale}, {+0.0f, +0.0f, +1.0f}));
            r_vert.push_back(Vertex({+t_scale, +t_scale, +t_scale}, {+1.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({+t_scale, -t_scale, -t_scale}, {+1.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({+t_scale, +t_scale, -t_scale}, {+1.0f, +0.0f, +0.0f}));

            r_vert.push_back(Vertex({+t_scale, -t_scale, -t_scale}, {+1.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({+t_scale, +t_scale, +t_scale}, {+1.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({+t_scale, -t_scale, +t_scale}, {+1.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({+t_scale, +t_scale, +t_scale}, {+0.0f, +1.0f, +0.0f}));
            r_vert.push_back(Vertex({+t_scale, +t_scale, -t_scale}, {+0.0f, +1.0f, +0.0f}));
            r_vert.push_back(Vertex({-t_scale, +t_scale, -t_scale}, {+0.0f, +1.0f, +0.0f}));

            r_vert.push_back(Vertex({+t_scale, +t_scale, +t_scale}, {+0.0f, +1.0f, +0.0f}));
            r_vert.push_back(Vertex({-t_scale, +t_scale, -t_scale}, {+0.0f, +1.0f, +0.0f}));
            r_vert.push_back(Vertex({-t_scale, +t_scale, +t_scale}, {+0.0f, +1.0f, +0.0f}));
            r_vert.push_back(Vertex({+t_scale, +t_scale, +t_scale}, {+0.0f, +0.0f, +1.0f}));
            r_vert.push_back(Vertex({-t_scale, +t_scale, +t_scale}, {+0.0f, +0.0f, +1.0f}));
            r_vert.push_back(Vertex({+t_scale, -t_scale, +t_scale}, {+0.0f, +0.0f, +1.0f}));

            return (r_vert);
        }

        /**
         *  Initialise the vertices for a skybox prop shape.
         *
         *  @param  t_scale Size multiplier of the shape.
         *
         *  @return The initialised vector of vertices for a skybox.
         */
        std::vector<Vertex> Prop::init_vert_skybox(const float t_scale) const
        {
            // Create vertex vector.
            std::vector<Vertex> r_vert;

            // Reserve space for 36 vertices.
            r_vert.reserve(36);

            // Add face vertices into the vertex vector.
            r_vert.push_back(Vertex({-t_scale, +t_scale, -t_scale}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({-t_scale, -t_scale, -t_scale}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({+t_scale, -t_scale, -t_scale}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({+t_scale, -t_scale, -t_scale}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({+t_scale, +t_scale, -t_scale}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({-t_scale, +t_scale, -t_scale}, {+0.0f, +0.0f, +0.0f}));

            r_vert.push_back(Vertex({-t_scale, -t_scale, +t_scale}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({-t_scale, -t_scale, -t_scale}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({-t_scale, +t_scale, -t_scale}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({-t_scale, +t_scale, -t_scale}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({-t_scale, +t_scale, +t_scale}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({-t_scale, -t_scale, +t_scale}, {+0.0f, +0.0f, +0.0f}));

            r_vert.push_back(Vertex({+t_scale, -t_scale, -t_scale}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({+t_scale, -t_scale, +t_scale}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({+t_scale, +t_scale, +t_scale}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({+t_scale, +t_scale, +t_scale}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({+t_scale, +t_scale, -t_scale}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({+t_scale, -t_scale, -t_scale}, {+0.0f, +0.0f, +0.0f}));

            r_vert.push_back(Vertex({-t_scale, -t_scale, +t_scale}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({-t_scale, +t_scale, +t_scale}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({+t_scale, +t_scale, +t_scale}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({+t_scale, +t_scale, +t_scale}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({+t_scale, -t_scale, +t_scale}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({-t_scale, -t_scale, +t_scale}, {+0.0f, +0.0f, +0.0f}));

            r_vert.push_back(Vertex({-t_scale, +t_scale, -t_scale}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({+t_scale, +t_scale, -t_scale}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({+t_scale, +t_scale, +t_scale}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({+t_scale, +t_scale, +t_scale}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({-t_scale, +t_scale, +t_scale}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({-t_scale, +t_scale, -t_scale}, {+0.0f, +0.0f, +0.0f}));

            r_vert.push_back(Vertex({-t_scale, -t_scale, -t_scale}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({-t_scale, -t_scale, +t_scale}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({+t_scale, -t_scale, -t_scale}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({+t_scale, -t_scale, -t_scale}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({-t_scale, -t_scale, +t_scale}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({+t_scale, -t_scale, +t_scale}, {+0.0f, +0.0f, +0.0f}));

            return (r_vert);
        }

        /**
         *  Initialise the vertices for a sun prop shape.
         *
         *  @param  t_scale Size multiplier of the shape.
         *
         *  @return The initialised vector of vertices for a sun.
         */
        std::vector<Vertex> Prop::init_vert_sun(const float t_scale) const
        {
            // Create vertex vector.
            std::vector<Vertex> r_vert;

            // Reserve space for 24 + 18 vertices.
            r_vert.reserve(24 + 18);

            // Add face vertices into the vertex vector.
            // Main body.
            r_vert.push_back(Vertex({+t_scale, +0.0f, +0.0f}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({+0.0f, +t_scale, +0.0f}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({+0.0f, +0.0f, +t_scale}, {+0.0f, +0.0f, +0.0f}));

            r_vert.push_back(Vertex({+0.0f, +t_scale, +0.0f}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({-t_scale, +0.0f, +0.0f}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({+0.0f, +0.0f, +t_scale}, {+0.0f, +0.0f, +0.0f}));

            r_vert.push_back(Vertex({-t_scale, +0.0f, +0.0f}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({+0.0f, -t_scale, +0.0f}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({+0.0f, +0.0f, +t_scale}, {+0.0f, +0.0f, +0.0f}));

            r_vert.push_back(Vertex({+0.0f, -t_scale, +0.0f}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({+t_scale, +0.0f, +0.0f}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({+0.0f, +0.0f, +t_scale}, {+0.0f, +0.0f, +0.0f}));

            r_vert.push_back(Vertex({+t_scale, +0.0f, +0.0f}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({+0.0f, +0.0f, -t_scale}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({+0.0f, +t_scale, +0.0f}, {+0.0f, +0.0f, +0.0f}));

            r_vert.push_back(Vertex({+0.0f, +t_scale, +0.0f}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({+0.0f, +0.0f, -t_scale}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({-t_scale, +0.0f, +0.0f}, {+0.0f, +0.0f, +0.0f}));

            r_vert.push_back(Vertex({-t_scale, +0.0f, +0.0f}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({+0.0f, +0.0f, -t_scale}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({+0.0f, -t_scale, +0.0f}, {+0.0f, +0.0f, +0.0f}));

            r_vert.push_back(Vertex({+0.0f, -t_scale, +0.0f}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({+0.0f, +0.0f, -t_scale}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({+t_scale, +0.0f, +0.0f}, {+0.0f, +0.0f, +0.0f}));

            // +z point.
            r_vert.push_back(Vertex({-0.25f*t_scale, +0.0f, +1.25f*t_scale}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({+0.0f, +0.25f*t_scale, +1.25f*t_scale}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({+0.0f, +0.0f, +1.75f*t_scale}, {+0.0f, +0.0f, +0.0f}));

            r_vert.push_back(Vertex({+0.0f, +0.25f*t_scale, +1.25f*t_scale}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({-0.25f*t_scale, +0.0f, +1.25f*t_scale}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({+0.0f, +0.0f, +1.75f*t_scale}, {+0.0f, +0.0f, +0.0f}));

            r_vert.push_back(Vertex({-0.25f*t_scale, +0.0f, +1.25f*t_scale}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({+0.0f, -0.25f*t_scale, +1.25f*t_scale}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({+0.0f, +0.0f, +1.75f*t_scale}, {+0.0f, +0.0f, +0.0f}));

            r_vert.push_back(Vertex({+0.0f, -0.25f*t_scale, +1.25f*t_scale}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({+0.25f*t_scale, +0.0f, +1.25f*t_scale}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({+0.0f, +0.0f, +1.75f*t_scale}, {+0.0f, +0.0f, +0.0f}));

            r_vert.push_back(Vertex({+0.25f*t_scale, +0.0f, +1.25f*t_scale}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({+0.0f, +0.25f*t_scale, +1.25f*t_scale}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({-0.25f*t_scale, +0.0f, +1.25f*t_scale}, {+0.0f, +0.0f, +0.0f}));

            r_vert.push_back(Vertex({-0.25f*t_scale, +0.0f, +1.25f*t_scale}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({+0.25f*t_scale, +0.0f, +1.25f*t_scale}, {+0.0f, +0.0f, +0.0f}));
            r_vert.push_back(Vertex({+0.0f, -0.25f*t_scale, +1.25f*t_scale}, {+0.0f, +0.0f, +0.0f}));

            return (r_vert);
        }

        /**
         *  Initialise the vertices for a box shape.
         *
         *  @param  t_min   Minimum bound of the box.
         *  @param  t_max   Maximum bound of the box.
         *
         *  @return The initialised vector of vertices for a box.
         */
        std::vector<Vertex> Prop::init_vert_box(const glm::vec3 &t_min, const glm::vec3 &t_max) const
        {
            // Create vertex vector.
            std::vector<Vertex> r_vert;

            // Reserve space for 24 vertices.
            r_vert.reserve(24);

            // Bottom of the box.
            r_vert.push_back(Vertex({t_min[X], t_min[Y], t_min[Z]}, {+0.0f, +0.0f, +0.0f}));)
            r_vert.push_back(Vertex({t_max[X], t_min[Y], t_min[Z]}, {+0.0f, +0.0f, +0.0f}));)
            r_vert.push_back(Vertex({t_max[X], t_min[Y], t_min[Z]}, {+0.0f, +0.0f, +0.0f}));)
            r_vert.push_back(Vertex({t_max[X], t_max[Y], t_min[Z]}, {+0.0f, +0.0f, +0.0f}));)
            r_vert.push_back(Vertex({t_max[X], t_max[Y], t_min[Z]}, {+0.0f, +0.0f, +0.0f}));)
            r_vert.push_back(Vertex({t_min[X], t_max[Y], t_min[Z]}, {+0.0f, +0.0f, +0.0f}));)
            r_vert.push_back(Vertex({t_min[X], t_max[Y], t_min[Z]}, {+0.0f, +0.0f, +0.0f}));)
            r_vert.push_back(Vertex({t_min[X], t_min[Y], t_min[Z]}, {+0.0f, +0.0f, +0.0f}));)

            // Pillars of the box.
            r_vert.push_back(Vertex({t_min[X], t_min[Y], t_min[Z]}, {+0.0f, +0.0f, +0.0f}));)
            r_vert.push_back(Vertex({t_min[X], t_min[Y], t_max[Z]}, {+0.0f, +0.0f, +0.0f}));)
            r_vert.push_back(Vertex({t_max[X], t_min[Y], t_min[Z]}, {+0.0f, +0.0f, +0.0f}));)
            r_vert.push_back(Vertex({t_max[X], t_min[Y], t_max[Z]}, {+0.0f, +0.0f, +0.0f}));)
            r_vert.push_back(Vertex({t_min[X], t_max[Y], t_min[Z]}, {+0.0f, +0.0f, +0.0f}));)
            r_vert.push_back(Vertex({t_min[X], t_max[Y], t_max[Z]}, {+0.0f, +0.0f, +0.0f}));)
            r_vert.push_back(Vertex({t_max[X], t_max[Y], t_min[Z]}, {+0.0f, +0.0f, +0.0f}));)
            r_vert.push_back(Vertex({t_max[X], t_max[Y], t_max[Z]}, {+0.0f, +0.0f, +0.0f}));)

            // Top of the box.
            r_vert.push_back(Vertex({t_min[X], t_min[Y], t_max[Z]}, {+0.0f, +0.0f, +0.0f}));)
            r_vert.push_back(Vertex({t_max[X], t_min[Y], t_max[Z]}, {+0.0f, +0.0f, +0.0f}));)
            r_vert.push_back(Vertex({t_max[X], t_min[Y], t_max[Z]}, {+0.0f, +0.0f, +0.0f}));)
            r_vert.push_back(Vertex({t_max[X], t_max[Y], t_max[Z]}, {+0.0f, +0.0f, +0.0f}));)
            r_vert.push_back(Vertex({t_max[X], t_max[Y], t_max[Z]}, {+0.0f, +0.0f, +0.0f}));)
            r_vert.push_back(Vertex({t_min[X], t_max[Y], t_max[Z]}, {+0.0f, +0.0f, +0.0f}));)
            r_vert.push_back(Vertex({t_min[X], t_max[Y], t_max[Z]}, {+0.0f, +0.0f, +0.0f}));)
            r_vert.push_back(Vertex({t_min[X], t_min[Y], t_max[Z]}, {+0.0f, +0.0f, +0.0f}));)

            return (r_vert);
        }



    } // namespace graphical
} // namespace arc
