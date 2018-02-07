/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   31/01/2018.
 */



//  == VERSION ==
#version 330 core



//  == LINKING ==
//  -- Layout --
layout(location = 0) in vec3 pos;   //! Vertex positions.
layout(location = 1) in vec3 norm;  //! Vertex normals.

//  -- Uniforms --
uniform mat4 mvp;       //! Model-view-projection matrix.
uniform mat4 view;      //! View matrix.
uniform vec4 col;       //! Mesh colour.
uniform vec3 sun_pos;   //! Sun position.



//  == IN/OUTPUT ==
//  -- Output --
out vec4 vert_col;              //! Colour to draw the vertex with.
out vec3 cam_space_norm;        //! Camera-space light normal.
out vec3 cam_space_light_dir;   //! Camera-space light direction.
out float dist;                 //! Distance between the light and the vertex.



//  == MAIN ==
/**
 *  Main function of the diffuse vertex sub-shader.
 */
void main()
{
    // Set pixel position.
    gl_Position = mvp * vec4(pos, 1.0);

    // Set vertex properties.
    vert_col = col;

    // Calculate the camera space light direction and normal.
    cam_space_light_dir = normalize((view * vec4(sun_pos, 1.0)).xyz - (view * vec4(pos, 1.0)).xyz);
    cam_space_norm      = normalize((view * vec4(norm, 0.0)).xyz);

    // Calculate the distance between the sun and the vertex.
    dist = length(sun_pos - pos);
}
