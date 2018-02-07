/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   04/02/2018.
 */



//  == VERSION ==
#version 330 core



//  == SETTINGS ==
//  -- Time Rendering --
const int time_fade = 16;   //! Power to fade photons away from the render_time.



//  == LINKING ==
//  -- Uniforms --
uniform vec4 col;           //! Path colour.
uniform float render_time;  //! Time to render photons at.



//  == IN/OUTPUT ==
//  -- Input --
in vec4 vert_col;   //! Colour to draw the vertex with.
in float vert_time; //! Timestamp of the vertex.

//  -- Output --
out vec4 frag_col;  //! Fragment colour.



//  == MAIN ==
/**
*  Main function of the path fragment sub-shader.
*/
void main()
{
    // Set fragment colour.
    frag_col = col;

    // Set fragement alpha if time rendering.
    if (render_time > 0.0)
    {
        // Reduce the fragment alpha value if it is far from the render time.
        float delta_time = 1.0 - clamp(abs(render_time - vert_time), 0.0, 1.0);
        frag_col.a = pow(delta_time, time_fade);
    }
}
