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
          protected:
            //  -- Properties --
            math::Vec<3> n_pos; //! Position of the particle.
            math::Vec<3> n_dir; //! Direction of travel.

            //  -- Simulation --
            double n_time;      //! Emission time plus current age of the particle.
            double n_weight;    //! Statistical weight of the particle.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            Particle(const math::Vec<3>& t_pos, const math::Vec<3>& t_dir, double t_time, double t_weight = 1.0);


            //  == METHODS ==
          public:
            //  -- Getters --
            const math::Vec<3>& get_pos() const { return (n_pos); }
            const math::Vec<3>& get_dir() const { return (n_dir); }
            double get_time() const { return (n_time); }
            double get_weight() const { return (n_weight); }

          protected:
            //  -- Simulation --
            void rotate(double t_dec, double t_azi);
            void multiply_weight(const double t_mult) const { n_weight *= t_mult; }
        };



    } // namespace phys
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_PHYS_PARTICLE_HPP
