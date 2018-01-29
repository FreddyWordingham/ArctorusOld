/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   29/01/2018.
 */



//  == HEADER ==
#include "cls/graphical/prop.hpp"



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
         *  Construct a prop to be rendered.
         *
         *  @param  t_vert  Vector of vertices forming the prop.
         *  @param  t_col   Colour of the prop.
         */
        Prop::Prop(const std::vector<Vertex>& t_vert, const glm::vec3& t_col) :
            m_num_vert(static_cast<GLsizei>(t_vert.size())),
            m_col(t_col),
            m_vao(init_vao()),
            m_vao(init_vbo())
        {

        }


        /**
         *  Construct a basic prop using a given shape type, colour and scale.
         *
         *  @param  t_shape Type of shape to be created.
         *  @param  t_col   Colour of the shape.
         *  @param  t_scale Scaling to be applied to the shape.
         */
//        Prop(const shape t_shape, const glm::vec3& t_col, const float t_scale = 1.0) : Prop(init_er)


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


    } // namespace graphical
} // namespace arc
