/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   29/01/2018.
 */



//  == VERSION ==
#version 330 core



//  == INPUT ==
//  -- Passed --
in vec3 vert_col;   //! Colour to draw the vertex with.



//  == OUTPUT ==
//  -- Passed --
out vec3 col;   //! Output fragment colour.



//  == MAIN ==
/**
 *  Illuminate objects with uniform ambient lighting.
 */
void main()
{
    col = vert_col;
}
