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
                const float m_dist;         //! Distance traveled so far by the packet.


                //  == INSTANTIATION ==
              public:
                //  -- Constructors --

              private:
                //  -- Initialisation --


                //  == OPERATORS ==
              private:


                //  == METHODS ==
              private:
            };



        } // namespace point
    } // namespace graphical
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GRAPHICAL_POINT_PHOTON_HPP
