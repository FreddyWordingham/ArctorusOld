/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   07/02/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_PHYS_PARTICLE_HPP
#define ARCTORUS_SRC_CLS_PHYS_PARTICLE_HPP



//  == INCLUDES ==
//  -- Classes --
#include "cls/math/vec.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace phys
    {



        //  == CLASS ==
        /**
         *  A physical particle.
         */
        class Particle
        {
            //  == FIELDS ==
          private:
            //  -- Properties --
            math::Vec<3> m_pos; //! Position of the particle.
            math::Vec<3> m_dir; //! Direction of travel.
            double       m_wavelengh; //! Associated wavelength.

            //  -- Simulation --
            double m_time;      //! Emission time plus current age of the particle.
            double m_weight;    //! Statistical weight of the particle.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            Particle(const math::Vec<3>& t_pos, const math::Vec<3>& t_dir, double t_wavelength, double t_time, double t_weight = 1.0);


            //  == METHODS ==
          public:
            //  -- Getters --
            math::Vec<3>& get_pos() const { return (m_pos); }
            math::Vec<3>& get_dir() const { return (m_dir); }
            double get_wavelength() const { return (m_wavelengh); }
            double get_time() const { return (m_time); }
            double get_weight() const { return (m_weight); }
        };



    } // namespace phys
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_PHYS_PARTICLE_HPP
