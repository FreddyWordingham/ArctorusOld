/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   07/02/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_PHYS_PARTICLE_PHOTON_HPP
#define ARCTORUS_SRC_CLS_PHYS_PARTICLE_PHOTON_HPP



//  == BASE CLASS ==
#include "cls/phys/particle.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace phys
    {
        namespace particle
        {



            //  == CLASS ==
            /**
             *  Photon packet particle class.
             */
            class Photon : public Particle
            {
                //  == FIELDS ==
              private:
                //  -- Properties --
                const double m_wavelength;  //! Packet wavelength.

                //  -- Optical --
                double m_ref_index;     //! Current refractive index.
                double m_albedo;        //! Current albedo.
                double m_interation;    //! Current interaction coefficient.
                double m_anisotropy;    //! Current anisotropy value.


                //  == INSTANTIATION ==
              public:
                //  -- Constructors --
                Photon(const math::Vec<3>& t_pos, const math::Vec<3>& t_dir, double t_time, double t_wavelength, double t_weight = 1.0, double t_red_index, double t_albedo, double t_interaction, double t_anisotropy);


                //  == METHODS ==
              public:
                //  -- Getters --
                double get_wavelength() const { return (m_wavelength); }
            };



        } // namespace particle
    } // namespace phys
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_PHYS_PARTICLE_PHOTON_HPP
