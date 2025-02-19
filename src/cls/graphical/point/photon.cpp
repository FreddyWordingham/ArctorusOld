/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   03/02/2018.
 */



//  == MODULE ==
#include "gen/config.hpp"
#ifdef ENABLE_GRAPHICS



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
             *  @param  t_time          Time of the packet.
             *
             *  @post   m_wavelength must be greater than zero.
             *  @post   m_weight must be greater than zero.
             *  @post   m_age must be greater than or equal to zero.
             */
            Photon::Photon(const glm::vec3& t_pos, const float t_wavelength, const float t_weight, const float t_time) :
                Point(t_pos),
                m_wavelength(t_wavelength),
                m_weight(t_weight),
                m_time(t_time)
            {
                assert(m_wavelength > 0.0f);
                assert(m_weight > 0.0f);
                assert(m_time >= 0.0f);
            }



        } // namespace point
    } // namespace graphical
} // namespace arc



//  == MODULE END ==
#endif
