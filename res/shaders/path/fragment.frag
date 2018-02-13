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
const int time_fade = 128;   //! Power to fade photons away from the render_time.



//  == LINKING ==
//  -- Uniforms --
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
    frag_col = vert_col;

    float delta_time = abs(vert_time - render_time);
/*
    if (render_time > 0.0)
    {
        float delta_time = abs(vert_time - render_time);

        if (delta_time > 1e-10)
        {
            frag_col.a = 0.0;
        }
        else
        {
            frag_col.a = 1.0 - (delta_time / 1e-10);
        }
    }*/
}
