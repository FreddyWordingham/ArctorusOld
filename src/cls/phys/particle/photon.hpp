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
                double m_wavelength;    //! Packet wavelength.


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



        } // namespace particle
    } // namespace phys
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_PHYS_PARTICLE_PHOTON_HPP
