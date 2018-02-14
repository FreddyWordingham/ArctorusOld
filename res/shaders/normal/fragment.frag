/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   29/01/2018.
 */



//  == VERSION ==
#version 330 core



//  == IN/OUTPUT ==
//  -- Input --
in vec4 geom_col;   //! Colour of the geometry vertex.

//  -- Output --
out vec4 frag_col;  //! Output fragment colour.



//  == MAIN ==
/**
 *  Main function of the normal fragment sub-shader.
 */
void main()
{
    // Set the fragment colour.
    frag_col = geom_col;
}
