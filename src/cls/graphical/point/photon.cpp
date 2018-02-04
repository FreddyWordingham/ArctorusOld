/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   03/02/2018.
 */



//  == HEADER ==
#include "cls/graphical/point/photon.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace graphical
    {
        namespace point
        {



            //  == INSTANTIATION ==
            //  -- Constructors --
            /**
             *  Construct a graphical photon packet at a given position.
             *
             *  @param  t_pos           Three dimensional position of the packet.
             *  @param  t_wavelength    Wavelength the packet.
             *  @param  t_weight        Statistical weight of the packet.
             *  @param  t_dist          Distance traveled so far by the packet.
             *
             *  @post   m_wavelength must be greater than zero.
             *  @post   m_weight must be greater than zero.
             *  @post   m_dist must be greater than zero.
             */
            Photon::Photon(const glm::vec3& t_pos, const float t_wavelength, const float t_weight, const float t_dist) :
                Point(t_pos),
                m_wavelength(t_wavelength),
                m_weight(t_weight),
                m_dist(t_dist)
            {
                assert(m_wavelength > 0.0f);
                assert(m_weight > 0.0f);
                assert(m_dist > 0.0f);
            }



        } // namespace point
    } // namespace graphical
} // namespace arc
