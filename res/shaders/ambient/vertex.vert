/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   29/01/2018.
 */



//  == VERSION ==
#version 330 core



//  == LINKING ==
//  -- Layout --
layout(location = 0) in vec3 pos;   //! Vertex positions.
layout(location = 1) in vec3 norm;  //! Vertex normals.

//  -- Uniforms --
uniform mat4 mvp;   //! Model-view-projection matrix.
uniform vec4 col;   //! Mesh colour.



//  == IN/OUTPUT ==
//  -- Output --
out vec4 vert_col;  //! Colour to draw the vertex with.



//  == MAIN ==
/**
 *  Main function of the ambient vertex sub-shader.
 */
void main()
{
    // Set pixel position.
    gl_Position = mvp * vec4(pos, 1.0);

    // Set vertex properties.
    vert_col = col;
}
