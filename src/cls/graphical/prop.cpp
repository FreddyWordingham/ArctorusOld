/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   29/01/2018.
 */



//  == HEADER ==
#include "cls/graphical/prop.hpp"



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
         */
        Prop::Prop(const std::vector<Vertex>& t_vert, const glm::vec3& t_col) :
            m_num_vert(static_cast<GLsizei>(t_vert.size())),
            m_col(t_col),
            m_vao(init_vao()),
            m_vbo(init_vbo())
        {
            glBindVertexArray(m_vao);
            glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
            glBufferData(GL_ARRAY_BUFFER, static_cast<size_t>(m_num_vert) * sizeof(Vertex), &t_vert.front(), GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) 0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) (3 * sizeof(GLfloat)));
            glEnableVertexAttribArray(1);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }

        /**
         *  Construct a basic prop using a given shape type, colour and scale.
         *
         *  @param  t_shape     Type of shape to be created.
         *  @param  t_col       Colour of the shape.
         *  @param  t_scale     Scaling to be applied to the shape.
         *  @param  t_aperture  Aperture used by some shapes.
         */
        Prop::Prop(const shape t_shape, const glm::vec3& t_col, const float t_scale, const float t_aperture) :
            Prop(init_vert(t_shape, t_scale, t_aperture), t_col) {}


        //  -- Initialisation --
        /**
         *  Initialise the handle to the prop's vao.
         *
         *  @return Handle to the prop's vao.
         */
        GLuint Prop::init_vao() const
        {
            GLuint r_vao;

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
            GLuint r_vbo;

            glGenBuffers(1, &r_vbo);

            return (r_vbo);
        }

        /**
         *  Initialise the vertices for a simple prop shape.
         *
         *  @param  t_shape     Type of shape to be created.
         *  @param  t_scale     Scaling to be applied to the shape.
         *  @param  t_aperture  Aperture used by some shapes.
         *
         *  @return The initialised vector of vertices for the simple shape.
         */
        std::vector<Vertex> Prop::init_vert(const shape t_shape, const float t_scale, const float t_aperture) const
        {
            switch (t_shape)
            {
                case shape::CUBE:
                    return (init_vert_cube(t_scale));
                case shape::SPOTLIGHT:
                    return (init_vert_spotlight(t_scale, t_aperture));
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
            std::vector<Vertex> r_vert;
            r_vert.reserve(36);

            r_vert.push_back(Vertex({{-t_scale, -t_scale, -t_scale}}, {{-1.0f, +0.0f, +0.0f}}));
            r_vert.push_back(Vertex({{-t_scale, -t_scale, +t_scale}}, {{-1.0f, +0.0f, +0.0f}}));
            r_vert.push_back(Vertex({{-t_scale, +t_scale, +t_scale}}, {{-1.0f, +0.0f, +0.0f}}));
            r_vert.push_back(Vertex({{+t_scale, +t_scale, -t_scale}}, {{+0.0f, +0.0f, -1.0f}}));
            r_vert.push_back(Vertex({{-t_scale, -t_scale, -t_scale}}, {{+0.0f, +0.0f, -1.0f}}));
            r_vert.push_back(Vertex({{-t_scale, +t_scale, -t_scale}}, {{+0.0f, +0.0f, -1.0f}}));

            r_vert.push_back(Vertex({{+t_scale, -t_scale, +t_scale}}, {{+0.0f, -1.0f, +0.0f}}));
            r_vert.push_back(Vertex({{-t_scale, -t_scale, -t_scale}}, {{+0.0f, -1.0f, +0.0f}}));
            r_vert.push_back(Vertex({{+t_scale, -t_scale, -t_scale}}, {{+0.0f, -1.0f, +0.0f}}));
            r_vert.push_back(Vertex({{+t_scale, +t_scale, -t_scale}}, {{+0.0f, +0.0f, -1.0f}}));
            r_vert.push_back(Vertex({{+t_scale, -t_scale, -t_scale}}, {{+0.0f, +0.0f, -1.0f}}));
            r_vert.push_back(Vertex({{-t_scale, -t_scale, -t_scale}}, {{+0.0f, +0.0f, -1.0f}}));

            r_vert.push_back(Vertex({{-t_scale, -t_scale, -t_scale}}, {{-1.0f, +0.0f, +0.0f}}));
            r_vert.push_back(Vertex({{-t_scale, +t_scale, +t_scale}}, {{-1.0f, +0.0f, +0.0f}}));
            r_vert.push_back(Vertex({{-t_scale, +t_scale, -t_scale}}, {{-1.0f, +0.0f, +0.0f}}));
            r_vert.push_back(Vertex({{+t_scale, -t_scale, +t_scale}}, {{+0.0f, -1.0f, +0.0f}}));
            r_vert.push_back(Vertex({{-t_scale, -t_scale, +t_scale}}, {{+0.0f, -1.0f, +0.0f}}));
            r_vert.push_back(Vertex({{-t_scale, -t_scale, -t_scale}}, {{+0.0f, -1.0f, +0.0f}}));

            r_vert.push_back(Vertex({{-t_scale, +t_scale, +t_scale}}, {{+0.0f, +0.0f, +1.0f}}));
            r_vert.push_back(Vertex({{-t_scale, -t_scale, +t_scale}}, {{+0.0f, +0.0f, +1.0f}}));
            r_vert.push_back(Vertex({{+t_scale, -t_scale, +t_scale}}, {{+0.0f, +0.0f, +1.0f}}));
            r_vert.push_back(Vertex({{+t_scale, +t_scale, +t_scale}}, {{+1.0f, +0.0f, +0.0f}}));
            r_vert.push_back(Vertex({{+t_scale, -t_scale, -t_scale}}, {{+1.0f, +0.0f, +0.0f}}));
            r_vert.push_back(Vertex({{+t_scale, +t_scale, -t_scale}}, {{+1.0f, +0.0f, +0.0f}}));

            r_vert.push_back(Vertex({{+t_scale, -t_scale, -t_scale}}, {{+1.0f, +0.0f, +0.0f}}));
            r_vert.push_back(Vertex({{+t_scale, +t_scale, +t_scale}}, {{+1.0f, +0.0f, +0.0f}}));
            r_vert.push_back(Vertex({{+t_scale, -t_scale, +t_scale}}, {{+1.0f, +0.0f, +0.0f}}));
            r_vert.push_back(Vertex({{+t_scale, +t_scale, +t_scale}}, {{+0.0f, +1.0f, +0.0f}}));
            r_vert.push_back(Vertex({{+t_scale, +t_scale, -t_scale}}, {{+0.0f, +1.0f, +0.0f}}));
            r_vert.push_back(Vertex({{-t_scale, +t_scale, -t_scale}}, {{+0.0f, +1.0f, +0.0f}}));

            r_vert.push_back(Vertex({{+t_scale, +t_scale, +t_scale}}, {{+0.0f, +1.0f, +0.0f}}));
            r_vert.push_back(Vertex({{-t_scale, +t_scale, -t_scale}}, {{+0.0f, +1.0f, +0.0f}}));
            r_vert.push_back(Vertex({{-t_scale, +t_scale, +t_scale}}, {{+0.0f, +1.0f, +0.0f}}));
            r_vert.push_back(Vertex({{+t_scale, +t_scale, +t_scale}}, {{+0.0f, +0.0f, +1.0f}}));
            r_vert.push_back(Vertex({{-t_scale, +t_scale, +t_scale}}, {{+0.0f, +0.0f, +1.0f}}));
            r_vert.push_back(Vertex({{+t_scale, -t_scale, +t_scale}}, {{+0.0f, +0.0f, +1.0f}}));

            return (r_vert);
        }

        /**
         *  Initialise the vertices for a spotlight prop shape.
         *
         *  @param  t_scale     Radius of the spotlight base.
         *  @param  t_aperture  Numerical aperture of the spotlight.
         *
         *  @return The initialised vector of vertices for a spotlight.
         */
        std::vector<Vertex> Prop::init_vert_spotlight(float t_scale, float t_aperture) const
        {
            std::vector<Vertex> r_vert;
            r_vert.reserve(36);

            r_vert.push_back(Vertex({{-t_scale, -t_scale, -t_scale}}, {{-1.0f, +0.0f, +0.0f}}));
            r_vert.push_back(Vertex({{-t_scale, -t_scale, +t_scale}}, {{-1.0f, +0.0f, +0.0f}}));
            r_vert.push_back(Vertex({{-t_scale, +t_scale, +t_scale}}, {{-1.0f, +0.0f, +0.0f}}));
            r_vert.push_back(Vertex({{+t_scale, +t_scale, -t_scale}}, {{+0.0f, +0.0f, -1.0f}}));
            r_vert.push_back(Vertex({{-t_scale, -t_scale, -t_scale}}, {{+0.0f, +0.0f, -1.0f}}));
            r_vert.push_back(Vertex({{-t_scale, +t_scale, -t_scale}}, {{+0.0f, +0.0f, -1.0f}}));

            r_vert.push_back(Vertex({{+t_scale, -t_scale, +t_scale}}, {{+0.0f, -1.0f, +0.0f}}));
            r_vert.push_back(Vertex({{-t_scale, -t_scale, -t_scale}}, {{+0.0f, -1.0f, +0.0f}}));
            r_vert.push_back(Vertex({{+t_scale, -t_scale, -t_scale}}, {{+0.0f, -1.0f, +0.0f}}));
            r_vert.push_back(Vertex({{+t_scale, +t_scale, -t_scale}}, {{+0.0f, +0.0f, -1.0f}}));
            r_vert.push_back(Vertex({{+t_scale, -t_scale, -t_scale}}, {{+0.0f, +0.0f, -1.0f}}));
            r_vert.push_back(Vertex({{-t_scale, -t_scale, -t_scale}}, {{+0.0f, +0.0f, -1.0f}}));

            r_vert.push_back(Vertex({{-t_scale, -t_scale, -t_scale}}, {{-1.0f, +0.0f, +0.0f}}));
            r_vert.push_back(Vertex({{-t_scale, +t_scale, +t_scale}}, {{-1.0f, +0.0f, +0.0f}}));
            r_vert.push_back(Vertex({{-t_scale, +t_scale, -t_scale}}, {{-1.0f, +0.0f, +0.0f}}));
            r_vert.push_back(Vertex({{+t_scale, -t_scale, +t_scale}}, {{+0.0f, -1.0f, +0.0f}}));
            r_vert.push_back(Vertex({{-t_scale, -t_scale, +t_scale}}, {{+0.0f, -1.0f, +0.0f}}));
            r_vert.push_back(Vertex({{-t_scale, -t_scale, -t_scale}}, {{+0.0f, -1.0f, +0.0f}}));

            r_vert.push_back(Vertex({{-t_scale, +t_scale, +t_scale}}, {{+0.0f, +0.0f, +1.0f}}));
            r_vert.push_back(Vertex({{-t_scale, -t_scale, +t_scale}}, {{+0.0f, +0.0f, +1.0f}}));
            r_vert.push_back(Vertex({{+t_scale, -t_scale, +t_scale}}, {{+0.0f, +0.0f, +1.0f}}));
            r_vert.push_back(Vertex({{+t_scale, +t_scale, +t_scale}}, {{+1.0f, +0.0f, +0.0f}}));
            r_vert.push_back(Vertex({{+t_scale, -t_scale, -t_scale}}, {{+1.0f, +0.0f, +0.0f}}));
            r_vert.push_back(Vertex({{+t_scale, +t_scale, -t_scale}}, {{+1.0f, +0.0f, +0.0f}}));

            r_vert.push_back(Vertex({{+t_scale, -t_scale, -t_scale}}, {{+1.0f, +0.0f, +0.0f}}));
            r_vert.push_back(Vertex({{+t_scale, +t_scale, +t_scale}}, {{+1.0f, +0.0f, +0.0f}}));
            r_vert.push_back(Vertex({{+t_scale, -t_scale, +t_scale}}, {{+1.0f, +0.0f, +0.0f}}));
            r_vert.push_back(Vertex({{+t_scale, +t_scale, +t_scale}}, {{+0.0f, +1.0f, +0.0f}}));
            r_vert.push_back(Vertex({{+t_scale, +t_scale, -t_scale}}, {{+0.0f, +1.0f, +0.0f}}));
            r_vert.push_back(Vertex({{-t_scale, +t_scale, -t_scale}}, {{+0.0f, +1.0f, +0.0f}}));

            r_vert.push_back(Vertex({{+t_scale, +t_scale, +t_scale}}, {{+0.0f, +1.0f, +0.0f}}));
            r_vert.push_back(Vertex({{-t_scale, +t_scale, -t_scale}}, {{+0.0f, +1.0f, +0.0f}}));
            r_vert.push_back(Vertex({{-t_scale, +t_scale, +t_scale}}, {{+0.0f, +1.0f, +0.0f}}));
            r_vert.push_back(Vertex({{+t_scale, +t_scale, +t_scale}}, {{+0.0f, +0.0f, +1.0f}}));
            r_vert.push_back(Vertex({{-t_scale, +t_scale, +t_scale}}, {{+0.0f, +0.0f, +1.0f}}));
            r_vert.push_back(Vertex({{+t_scale, -t_scale, +t_scale}}, {{+0.0f, +0.0f, +1.0f}}));

            return (r_vert);
        }



    } // namespace graphical
} // namespace arc
