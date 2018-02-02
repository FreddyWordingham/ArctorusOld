/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   29/01/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_GEN_CONTROLS_HPP
#define ARCTORUS_SRC_GEN_CONTROLS_HPP



//  == INCLUDES ==
//  -- System --
#include <GLFW/glfw3.h>



//  == NAMESPACE ==
namespace arc
{
    namespace control
    {



        //  == SETTINGS ==
        //  -- Window --
        constexpr const int QUIT = GLFW_KEY_ESCAPE; //! Quit and close the graphical window.

        //  -- Camera --
        constexpr const int SWAP_CAM           = GLFW_KEY_TAB;          //! Swap the primary and secondary cameras.
        constexpr const int DECREASE_CAM_SPEED = GLFW_KEY_LEFT_CONTROL; //! Decrease camera speed.
        constexpr const int INCREASE_CAM_SPEED = GLFW_KEY_LEFT_SHIFT;   //! Increase camera speed.
        constexpr const int TRANS_CAM_FORWARD  = GLFW_KEY_W;            //! Move the camera forward.
        constexpr const int TRANS_CAM_BACKWARD = GLFW_KEY_S;            //! Move the camera backward.
        constexpr const int TRANS_CAM_LEFT     = GLFW_KEY_A;            //! Move the camera left.
        constexpr const int TRANS_CAM_RIGHT    = GLFW_KEY_D;            //! Move the camera right.
        constexpr const int TRANS_CAM_UP       = GLFW_KEY_E;            //! Move the camera upwards.
        constexpr const int TRANS_CAM_DOWN     = GLFW_KEY_Q;            //! Move the camera downwards.
        constexpr const int ROT_CAM_LEFT       = GLFW_KEY_J;            //! Rotate the camera to the left.
        constexpr const int ROT_CAM_RIGHT      = GLFW_KEY_L;            //! Rotate the camera to the right.
        constexpr const int ROT_CAM_UP         = GLFW_KEY_I;            //! Rotate the camera upwards.
        constexpr const int ROT_CAM_DOWN       = GLFW_KEY_K;            //! Rotate the camera downwards.

        //  -- Illuminator --
        const int TRANS_SUN_FORWARD  = GLFW_KEY_T;  //! Move the sun global illuminator forward.
        const int TRANS_SUN_BACKWARD = GLFW_KEY_G;  //! Move the sun global illuminator backward.
        const int TRANS_SUN_LEFT     = GLFW_KEY_F;  //! Move the sun global illuminator left.
        const int TRANS_SUN_RIGHT    = GLFW_KEY_H;  //! Move the sun global illuminator right.
        const int TRANS_SUN_UP       = GLFW_KEY_Y;  //! Move the sun global illuminator upwards.
        const int TRANS_SUN_DOWN     = GLFW_KEY_R;  //! Move the sun global illuminator downwards.


    } // namespace control
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_GEN_CONTROLS_HPP
