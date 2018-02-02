/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   02/02/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_GRAPHICAL_CAMERA_FLY_HPP
#define ARCTORUS_SRC_CLS_GRAPHICAL_CAMERA_FLY_HPP



//  == BASE CLASS ==
#include "cls/graphical/camera.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace graphical
    {
        namespace camera
        {



            //  == CLASS ==
            /**
             *  A specialised camera with fly controls.
             */
            class Fly : public Camera
            {
                //  == FIELDS ==
              private:
                //  -- Orientation --
                float m_azi;    //! Rotation of the camera around its local z-axis.
                float m_dec;    //! Declination of the camera from its local z-axis.


                //  == INSTANTIATION ==
              public:
                //  -- Constructors --
                Fly(const glm::vec3& t_pos, float t_aspect_ratio, float t_speed = DEFAULT_SPEED,
                    float t_fov = DEFAULT_FOV);


                //  == METHODS ==
              private:
                //  -- Movement --
                void move(const glm::vec3& t_translate, const glm::vec2& t_rotate) override;
            };



        } // namespace camera
    } // namespace graphical
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GRAPHICAL_CAMERA_FLY_HPP
