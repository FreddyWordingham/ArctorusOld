/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   07/02/2018.
 */



//  == HEADER ==
#include "cls/phys/particle.hpp"



//  == INCLUDES ==
//  -- General --
#include "gen/math.hpp"



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
        Particle::Particle(const math::Vec<3>& t_pos, const math::Vec<3>& t_dir, const double t_time, const double t_weight) :
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
            assert((t_azi >= 0.0) && (t_azi <= 2.0 * M_PI));

            if (std::fabs(1.0 - std::fabs(n_dir[Z])) < 1E-10)
            {
                n_dir[X] = std::sin(t_dec) * std::cos(t_azi);
                n_dir[Y] = std::sin(t_dec) * std::sin(t_azi);
                n_dir[Z] = math::sign(n_dir[Z]) * std::cos(t_dec);
            }
            else
            {
                const math::Vec<3> prev_dir = n_dir;

                const double a         = std::sqrt(1.0 - math::square(prev_dir[Z]));
                const double sin_theta = std::sin(t_dec);
                const double cos_theta = std::cos(t_dec);
                const double sin_phi   = std::sin(t_azi);
                const double cos_phi   = std::cos(t_azi);

                n_dir[X] = ((sin_theta / a) * ((prev_dir[X] * prev_dir[Z] * cos_phi) - (prev_dir[Y] * sin_phi))) + (prev_dir[X] * cos_theta);
                n_dir[Y] = ((sin_theta / a) * ((prev_dir[Y] * prev_dir[Z] * cos_phi) + (prev_dir[X] * sin_phi))) + (prev_dir[Y] * cos_theta);
                n_dir[Z] = (prev_dir[Z] * cos_theta) - (sin_theta * cos_phi * a);
            }

            n_dir.normalise();

            assert(n_dir.is_normalised());
        }



    } // namespace phys
} // namespace arc
