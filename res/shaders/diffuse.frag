/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   31/01/2018.
 */



//  == VERSION ==
#version 330 core



//  == CONSTANTS --
//  -- Uniforms --
uniform float amb_pow;  //! Ambient lighting power.
uniform vec3 sun_pos;   //! Sun position.
const float light_pow   = 5.0f; //! Power of the light source (arbitrary).



//  == INPUT ==
//  -- Passed --
in vec3 vert_col;               //! Colour to draw the vertex with.
in vec3 cam_space_norm;         //! Camera-space light normal.
in vec3 cam_space_light_dir;    //! Camera-space light direction.
in float dist;                  //! Distance between the light and the vertex.



//  == OUTPUT ==
//  -- Passed --
out vec3 col;   //! Output fragment colour.



//  == MAIN ==
/**
 *  Illuminate objects with uniform ambient lighting.
 */
void main()
{
    float cos_theta = clamp(dot(cam_space_norm, cam_space_light_dir), 0.0, 1.0);

    col = vert_col * (amb_pow + ((light_pow * cos_theta) / (dist * dist)));
}
