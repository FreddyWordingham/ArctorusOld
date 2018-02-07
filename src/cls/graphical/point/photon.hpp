/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   03/02/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_GRAPHICAL_POINT_PHOTON_HPP
#define ARCTORUS_SRC_CLS_GRAPHICAL_POINT_PHOTON_HPP



//  == BASE CLASS ==
#include "cls/graphical/point.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace graphical
    {
        namespace point
        {



            //  == CLASS ==
            /**
             *  Data about a single renderable photon packet at a point.
             */
            class Photon : public Point
            {
                //  == FIELDS ==
              private:
                //  -- Data --
                const float m_wavelength;   //! Wavelength the packet.
                const float m_weight;       //! Statistical weight of the packet.
                const float m_time;         //! Age of the packet.


                //  == INSTANTIATION ==
              public:
                //  -- Constructors --
                Photon(const glm::vec3& t_pos, float t_wavelength, float t_weight, float t_time);


                //  == METHODS ==
              public:
                //  -- Getters --
                float get_wavelength() const { return (m_wavelength); }
                float get_weight() const { return (m_weight); }
                float get_time() const { return (m_time); }
            };



        } // namespace point
    } // namespace graphical
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GRAPHICAL_POINT_PHOTON_HPP
