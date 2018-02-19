/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   19/02/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_PHYS_PHOTON_HPP
#define ARCTORUS_SRC_CLS_PHYS_PHOTON_HPP



//  == INCLUDES ==
//  -- Classes --
#include "cls/graphical/point/photon.hpp"
#include "cls/math/vec.hpp"
#include "material.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace phys
    {



        //  == CLASS ==
        /**
         *  Photon packet class.
         */
        class Photon
        {
            //  == FIELDS ==
          private:
            //  -- Spatial --
            math::Vec<3> m_pos;     //! Position of the particle.
            math::Vec<3> m_dir;     //! Direction of travel.
            double       m_weight;  //! Statistical weight of the particle.

            //  -- Optical --
            const double m_wavelength;  //! Wavelength of the photon packet.
            double       m_ref_index;   //! Current refractive index.
            double       m_albedo;      //! Current albedo.
            double       m_interaction; //! Current interaction coefficient.
            double       m_anisotropy;  //! Current anisotropy value.

            //  -- Data --
            double                                m_time;   //! Emission time plus current age of the particle.
            std::vector<graphical::point::Photon> m_path;   //! Path data of the photon.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            Photon(const math::Vec<3>& t_pos, const math::Vec<3>& t_dir, double t_wavelength, const phys::Material& t_mat);

          private:
            //  -- Constructors --
            Photon(const math::Vec<3>& t_pos, const math::Vec<3>& t_dir, double t_wavelength, double t_ref_index,
                   double t_albedo, double t_interaction, double t_anisotropy);


            //  == METHODS ==
          public:
            //  -- Getters --
            const math::Vec<3>& get_pos() const { return (m_pos); }
            const math::Vec<3>& get_dir() const { return (m_dir); }
            const std::vector<graphical::point::Photon>& get_path() const { return (m_path); }
            double get_interaction() const { return (m_interaction); }

            //  -- Setters --
            void move(double t_dist);
            void rotate(double t_dec, double t_azi);
            void multiply_weight(double t_mult);

          private:
            //  -- Data --
            void record_path();
        };



    } // namespace phys
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_PHYS_PHOTON_HPP
