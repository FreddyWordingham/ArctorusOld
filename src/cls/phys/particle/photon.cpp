/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   07/02/2018.
 */



//  == HEADER ==
#include "cls/phys/particle/photon.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace phys
    {
        namespace particle
        {



            //  == INSTANTIATION ==
            //  -- Constructors --
            /**
             *  Construct a photon packet at a given position with an initial direction at an emission time and
             *  initial statistical weight and wavelength.
             *
             *  @param  t_pos           Initial position of the photon packet.
             *  @param  t_dir           Initial direction of the photon packet.
             *  @param  t_time          Emission time of the photon packet.
             *  @param  t_wavelength    Initial wavelength of the photon packet.
             *  @param  t_weight        Initial statistical weight of the photon packet.
             *
             *  @post   n_dir must be normalised.
             *  @post   n_time must be positive.
             *  @post   m_wavelength must be positive.
             *  @post   n_weight must be positive.
             */
            Photon::Photon(const math::Vec<3>& t_pos, const math::Vec<3>& t_dir, const double t_time,
                               const double t_wavelength, const double t_weight) :
                Particle(t_pos, t_dir, t_time, t_weight),
                m_wavelength(t_wavelength)
            {
                assert(n_dir.is_normalised());
                assert(n_time > 0.0);
                assert(m_wavelength > 0.0);
                assert(n_weight > 0.0);
            }



        } // namespace particle
    } // namespace phys
} // namespace arc
