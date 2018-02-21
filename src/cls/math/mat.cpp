/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   21/02/2018.
 */



//  == HEADER ==
#include "cls/math/mat.hpp"



//  == INCLUDES ==
//  -- System --



//  == NAMESPACE ==
namespace arc
{
    namespace math
    {



        //  == FUNCTIONS ==
        double determinant(const Mat<2, 2>& t_mat)
        {
            return ((t_mat[0][0] * t_mat[1][1]) - (t_mat[0][1] * t_mat[1][0]));
        }



    } // namespace math
} // namespace arc
