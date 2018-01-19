/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   19/01/2018.
 */



//  == HEADER ==
#include "cls/math/mat.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace math
    {



        //  == FUNCTIONS ==
        //  -- Matrix --
        /**
         *  Create a position transformation matrix.
         *  Transformation matrix is constructed from the individual transformations given.
         *  Rotations are performed in the order x, y, z-axis.
         *
         *  @param  t_scale Scaling vector.
         *  @param  t_rot   Rotation vector.
         *  @param  t_trans Translation vector.
         *
         *  @return The position transformation matrix.
         */
        Mat<4, 4> pos_trans(const Vec<3>& t_scale, const Vec<3>& t_rot, const Vec<3>& t_trans)
        {
            Mat<4, 4> scale(
                {{{{t_scale[X], 0.0, 0.0, 0.0}}, {{0.0, t_scale[Y], 0.0, 0.0}}, {{0.0, 0.0, t_scale[Z], 0.0}}, {{0.0, 0.0, 0.0, 1.0}}}});

            Mat<4, 4> rot(
                {{{{cos(t_rot[Y]) * cos(t_rot[Z]), (cos(t_rot[Z]) * sin(t_rot[X]) * sin(t_rot[Y])) - (cos(t_rot[X]) * sin(
                    t_rot[Z])), (cos(t_rot[X]) * cos(t_rot[Z]) * sin(t_rot[Y])) - (sin(t_rot[X]) * sin(t_rot[Z])), 0.0}}, {{cos(
                    t_rot[Y]) * sin(t_rot[Z]), (cos(t_rot[X]) * cos(t_rot[Z])) + (sin(t_rot[X]) * sin(t_rot[Y]) * sin(
                    t_rot[Z])), (cos(t_rot[X]) * sin(t_rot[Y]) * sin(t_rot[Z])) - (cos(t_rot[Z]) * sin(
                    t_rot[X])), 0.0}}, {{-sin(t_rot[Y]), cos(t_rot[Y]) * sin(t_rot[X]), cos(t_rot[X]) * cos(
                    t_rot[Y]), 0.0}}, {{0.0, 0.0, 0.0, 1.0}}}});

            Mat<4, 4> trans(
                {{{{1.0, 0.0, 0.0, t_trans[X]}}, {{1.0, 0.0, 0.0, t_trans[Y]}}, {{1.0, 0.0, 0.0, t_trans[Z]}}, {{0.0, 0.0, 0.0, 1.0}}}});

            return (trans * rot * scale);
        }

        /**
         *  Create a direction transformation matrix.
         *  Transformation matrix is constructed from the individual transformations given.
         *  Rotations are performed in the order x, y, z-axis.
         *
         *  @param  t_scale Scaling vector.
         *  @param  t_rot   Rotation vector.
         *
         *  @return The rotation transformation matrix.
         */
        Mat<4, 4> dir_trans(const Vec<3>& t_scale, const Vec<3>& t_rot)
        {
            Mat<4, 4> scale(
                {{{{1.0 / t_scale[X], 0.0, 0.0, 0.0}}, {{0.0, 1.0 / t_scale[Y], 0.0, 0.0}}, {{0.0, 0.0, 1.0 / t_scale[Z], 0.0}}, {{0.0, 0.0, 0.0, 1.0}}}});

            Mat<4, 4> rot(
                {{{{cos(t_rot[Y]) * cos(t_rot[Z]), (cos(t_rot[Z]) * sin(t_rot[X]) * sin(t_rot[Y])) - (cos(t_rot[X]) * sin(
                    t_rot[Z])), (cos(t_rot[X]) * cos(t_rot[Z]) * sin(t_rot[Y])) - (sin(t_rot[X]) * sin(t_rot[Z])), 0.0}}, {{cos(
                    t_rot[Y]) * sin(t_rot[Z]), (cos(t_rot[X]) * cos(t_rot[Z])) + (sin(t_rot[X]) * sin(t_rot[Y]) * sin(
                    t_rot[Z])), (cos(t_rot[X]) * sin(t_rot[Y]) * sin(t_rot[Z])) - (cos(t_rot[Z]) * sin(
                    t_rot[X])), 0.0}}, {{-sin(t_rot[Y]), cos(t_rot[Y]) * sin(t_rot[X]), cos(t_rot[X]) * cos(
                    t_rot[Y]), 0.0}}, {{0.0, 0.0, 0.0, 1.0}}}});

            return (rot * scale);
        }



    } // namespace math
} // namespace arc
