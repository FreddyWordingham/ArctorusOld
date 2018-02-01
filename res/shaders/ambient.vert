/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   29/01/2018.
 */



//  == VERSION ==
#version 330 core



//  == INPUT ==
//  -- Layout --
in vec3 pos;    //! Vertex positions.
in vec3 norm;   //! Vertex normals.

//  -- Uniforms --
uniform mat4 mvp;       //! Model-view-projection matrix.
uniform vec3 prop_col;  //! Prop colour.



//  == OUTPUT ==
//  -- Passed --
out vec4 vert_col;  //! Colour to draw the vertex with.



//  == MAIN ==
/**
 *  Illuminate objects with uniform ambient lighting.
 */
void main()
{
    gl_Position = mvp * vec4(pos, 1.0);

    vert_col = vec4(prop_col, 1.0);
}
