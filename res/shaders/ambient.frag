/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   29/01/2018.
 */



//  == VERSION ==
#version 330 core



//  == OUTPUT ==
//  -- Passed --
vec4 out_color; //! Output fragment colour.



//  == MAIN ==
/**
 *  Illuminate objects with uniform ambient lighting.
 */
void main()
{
    out_color = vec4(1.0, 0.0, 0.0, 1.0);
}
