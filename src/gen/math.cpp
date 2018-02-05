/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   05/02/2018.
 */



//  == HEADER ==
#include "gen/math.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace math
    {



        //  == FUNCTIONS ==
        //  -- Transformation --
        /**
         *  Create a translation transformation matrix.
         *
         *  @param  t_trans Vector of translation.
         *
         *  @return The created translation matrix.
         */
        Mat<4, 4> create_trans_mat(const Vec<3>& t_trans)
        {
            return (Mat<4, 4>(
                {{{{1.0, 0.0, 0.0, t_trans[X]}}, {{0.0, 1.0, 0.0, t_trans[Y]}}, {{0.0, 0.0, 1.0, t_trans[Z]}}, {{0.0, 0.0, 0.0, 1.0}}}}));
        }



    } // namespace math
} // namespace arc
