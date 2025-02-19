/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   09/02/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_EQUIP_LIGHT_HPP
#define ARCTORUS_SRC_CLS_EQUIP_LIGHT_HPP



//  == INCLUDES ==
//  -- Classes --
#include "cls/geom/mesh.hpp"
#include "cls/phys/material.hpp"
#include "cls/phys/photon.hpp"
#include "cls/phys/spectrum.hpp"
#include "cls/random/index.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace equip
    {



        //  == CLASS ==
        /**
         *  Light source class used to emit photons from.
         */
        class Light
        {
            //  == FIELDS ==
          private:
            //  -- Properties --
            const geom::Mesh     m_mesh;    //! Mesh describing the surface of the light.
            const phys::Spectrum m_spec;    //! Linear random generator forming the emission spectrum.

            //  -- Sorting --
            const random::Index m_tri_select;   //! Random triangle index selector.
            const double        m_power;        //! Power of the light source.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            Light(const geom::Mesh& t_mesh, const phys::Spectrum& t_spec, double t_power);

            //  -- Initialisation --
            random::Index init_rand_tri() const;


            //  == METHODS ==
          public:
            //  -- Getters --
            double get_min_bound() const { return (m_spec.get_min_bound()); }
            double get_max_bound() const { return (m_spec.get_max_bound()); }
            const geom::Mesh& get_mesh() const { return (m_mesh); }
            const phys::Spectrum& get_spec() const { return (m_spec); }
            double get_power() const { return (m_power); }

            //  -- Generation --
            phys::Photon gen_photon(const phys::Material& t_mat) const;
        };



    } // namespace equip
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_EQUIP_LIGHT_HPP
