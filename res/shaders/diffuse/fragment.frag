/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   31/01/2018.
 */



//  == VERSION ==
#version 330 core



//  == SETTINGS ==
//  -- Light Properties --
const float light_pow = 5.0f;   //! Power of the light source (arbitrary).



//  == LINKING ==
//  -- Uniforms --
uniform float amb_pow;  //! Ambient lighting power.
uniform vec3 sun_pos;   //! Sun position.



//  == IN/OUTPUT ==
//  -- Input --
in vec4 vert_col;               //! Colour to draw the vertex with.
in vec3 cam_space_norm;         //! Camera-space light normal.
in vec3 cam_space_light_dir;    //! Camera-space light direction.
in float dist;                  //! Distance between the light and the vertex.

//  -- Output --
out vec4 frag_col;  //! Output fragment colour.



//  == MAIN ==
/**
 *  Illuminate objects with uniform ambient lighting.
 */
void main()
{
    // Calculate the angle between the camera and the light source.
    float cos_theta = clamp(dot(cam_space_norm, cam_space_light_dir), 0.0, 1.0);

    // Set the fragment colour.
    frag_col = vert_col;

    // Multiply the fragment colour depending on the camera-light source angle.
    frag_col.xyz *= (amb_pow + ((light_pow * cos_theta) / (dist * dist)));
}
