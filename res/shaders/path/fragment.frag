/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   04/02/2018.
 */



//  == VERSION ==
#version 330 core



//  == INPUT ==
//  -- Passed --
in vec4 vert_col;   //! Colour to draw the vertex with.
in float vert_time;

//  -- Constants --
uniform float render_time;  //! Time to render photons at.



//  == OUTPUT ==
//  -- Passed --
out vec4 col;



//  == MAIN ==
/**
 *  Photon packet path rendering shader.
 */
void main()
{
    // Set fragment colour.
    col = vert_col;

    if (render_time > 0.0)
    {
        float close = 1.0 - clamp(abs(render_time - vert_time), 0.0, 1.0);
        col.a = close * close * close;
    }
}
