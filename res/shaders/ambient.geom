/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   01/02/2018.
 */



//  == VERSION ==
#version 330 core



//  == INPUT ==
//  -- Layout --
layout(triangles) in;

//  -- Passed --
in vec4 vert_col[]; //! Colour to draw the vertex with.



//  == OUTPUT ==
//  -- Layout --
layout(triangle_strip, max_vertices = 1) out;

//  -- Passed --
out vec4 geom_col;  //! Colour to draw the vertex with.



//  == MAIN ==
/**
 *  Illuminate objects with uniform ambient lighting.
 */
void main()
{
    gl_Position = gl_in[0].gl_Position;
    geom_col = vert_col[0];

    EmitVertex();
    EndPrimitive();
}
