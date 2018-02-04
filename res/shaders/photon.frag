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
}
