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
         *  @post   m_time must be positive.
         *  @post   m_weight must be positive.
         */
        Particle::Particle(const math::Vec<3>& t_pos, const math::Vec<3>& t_dir, const double t_time,
                           const double t_weight) :
            m_pos(t_pos),
            m_dir(t_dir),
            m_time(t_time),
            m_weight(t_weight)
        {
            assert(m_dir.is_normalised());
            assert(m_time > 0.0);
            assert(m_weight > 0.0);
        }



    } // namespace phys
} // namespace arc
