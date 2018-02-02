/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   01/02/2018.
 */



//  == VERSION ==
#version 330 core



//  == INPUT ==
//  -- Vertex --
layout(points) in;

//  -- Passed --
in vec3 vert_pos[];
in vec3 vert_norm[];

//  -- Uniforms --
uniform mat4 mvp;           //! Model-view-projection matrix.
uniform vec4 prop_col;      //! Prop colour.
uniform float light_power;  //! Length to draw normal lines.



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
        vec4 v0     = vec4(vert_pos[0], 1.0);
        gl_Position = mvp * v0;
        geom_col = prop_col;
        EmitVertex();

        vec4 v1     = v0 + vec4(vert_norm[0] * light_power, 0.0);
        gl_Position = mvp * v1;
        geom_col = vec4(0.0, 0.0, 0.0, 1.0);
        EmitVertex();

        EndPrimitive();
}
