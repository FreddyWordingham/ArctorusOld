/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   02/02/2018.
 */



//  == VERSION ==
#version 330 core



//  == INPUT ==
//  -- Passed --
in vec4 vert_col;   //! Colour of the geometry vertex.



//  == OUTPUT ==
//  -- Passed --
out vec4 frag_col;  //! Output fragment colour.



//  == MAIN ==
/**
 *  Illuminate objects with uniform ambient lighting.
 */
void main()
{
    frag_col = vert_col;
}
