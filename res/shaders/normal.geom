/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   01/02/2018.
 */



//  == VERSION ==
#version 330 core



//  == CONSTANTS ==
//  -- Drawing --
const float length = 1.0; //! Length to draw normal lines.



//  == INPUT ==
//  -- Vertex --
layout(points) in;

//  -- Passed --
in Vertex
{
    vec3 norm;
    vec4 col;
}   vertex[];

//  -- Uniforms --
uniform mat4 mvp;   //! Model-view-projection matrix.



//  == OUTPUT ==
//  -- Layout --
layout(line_strip, max_vertices = 2) out;

//  -- Passed --
out vec4 geom_col;  //! Colour to draw the vertex with.



//  == MAIN ==
/**
 *  Illuminate objects with uniform ambient lighting.
 */
void main()
{
        vec4 v0     = gl_in[0].gl_Position;
        gl_Position = mvp * v0;
        geom_col = vertex[0].col;
        EmitVertex();

        // we calculate v1 of our line segment
        vec4 v1     = v0 + vec4(vertex[0].norm * length, 0);
        gl_Position = mvp * (v0 + vec4(vertex[0].norm * length, 0));
        geom_col = vertex[0].col;
        EmitVertex();

        EndPrimitive();
}
