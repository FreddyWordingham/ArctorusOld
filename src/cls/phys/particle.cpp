/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   07/02/2018.
 */



//  == HEADER ==
#include "cls/phys/particle.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace phys
    {



        //  == INSTANTIATION ==
        //  -- Constructors --
        /**
         *  Construct a particle at a given position with an initial direction at an emission time and
         *  initial statistical weight.
         *
         *  @param  t_pos           Initial position of the particle.
         *  @param  t_dir           Initial direction of the particle.
         *  @param  t_time          Emission time of the particle.
         *  @param  t_weight        Initial statistical weight of the particle.
         *
         *  @post   m_dir must be normalised.
         *  @post   m_wavelength must be positive.
         *  @post   m_time must be greater than, or equal to, zero.
         *  @post   m_weight must be positive.
         */
        Particle::Particle(const math::Vec<3>& t_pos, const math::Vec<3>& t_dir, const double t_time,
                           const double t_weight) :
            n_pos(t_pos),
            n_dir(t_dir),
            n_time(t_time),
            n_weight(t_weight)
        {
            assert(n_dir.is_normalised());
            assert(n_time >= 0.0);
            assert(n_weight > 0.0);
        }



        //  == METHODS ==
        //  -- Simulation --
        /**
         *  Rotate a particle by a given declination and then a given azimuthal rotation.
         *
         *  @param  t_dec   Declination angle away from current direction vector.
         *  @param  t_azi   Azimuthal rotation around current direction vector.
         *
         *  @pre    n_dir must be normalised.
         *  @pre    t_dec must be between zero and pi.
         *  @pre    t_azi must be between zero and two pi.
         *
         *  @post   n_dir must be normalised.
         */
        void Particle::rotate(double t_dec, double t_azi)
        {
            assert(n_dir.is_normalised());
            assert((t_dec >= 0.0) && (t_dec <= M_PI));
            assert((t_azi >= 0.0) && (t_azi <= 2.0*M_PI));


            assert(n_dir.is_normalised());
        }



    } // namespace phys
} // namespace arc
