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
uniform float length = 1.0; //! Length to draw normal lines.



//  == INPUT ==
//  -- Vertex --
layout(triangles) in;

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
layout(line_strip, max_vertices=6) out;

//  -- Passed --
out vec4 geom_col;  //! Colour to draw the vertex with.



//  == MAIN ==
/**
 *  Illuminate objects with uniform ambient lighting.
 */
void main()
{
    for(int i = 0; i < gl_in.length(); i++)
    {
        vec3 P = gl_in[i].gl_Position.xyz;
        vec3 N = vertex[i].norm.xyz;

        gl_Position = mvp * vec4(P, 1.0);
        geom_col = vertex[i].col;
        EmitVertex();

        gl_Position = mvp * vec4(P + (N * length), 1.0);
        geom_col = vertex[i].col;
        EmitVertex();

        EndPrimitive();
    }
}
