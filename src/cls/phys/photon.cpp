/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   19/02/2018.
 */



//  == HEADER ==
#include "cls/phys/photon.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace phys
    {



        //  == INSTANTIATION ==
        //  -- Constructors --
        /**
         *  Construct a photon at a given initial position with a given initial direction using a given initial material.
         *
         *  @param  t_pos           Initial position of the photon.
         *  @param  t_dir           Initial direction of the photon.
         *  @param  t_wavelength    Wavelength of the photon packet.
         *  @param  t_mat           Initial material the photon is located within.
         */
        Photon::Photon(const math::Vec<3>& t_pos, const math::Vec<3>& t_dir, const double t_wavelength,
                       const phys::Material& t_mat) :
            Photon(t_pos, t_dir, t_wavelength, t_mat.get_ref_index(t_wavelength), t_mat.get_albedo(t_wavelength),
                   t_mat.get_interaction(t_wavelength), t_mat.get_anisotropy(t_wavelength))
        {
        }

        /**
         *  Construct a photon at a given initial position with a given initial direction with given initial optical properties.
         *
         *  @param  t_pos           Initial position of the photon.
         *  @param  t_dir           Initial direction of the photon.
         *  @param  t_wavelength    Wavelength of the photon packet.
         *  @param  t_ref_index     Refractive index of the current medium.
         *  @param  t_albedo        Single scattering albedo of the current medium.
         *  @param  t_interaction   Interaction coefficient of the current medium.
         *  @param  t_anisotropy    Anisotropy value of the current medium.
         *
         *  @post   m_dir must be normalised.
         */
        Photon::Photon(const math::Vec<3>& t_pos, const math::Vec<3>& t_dir, const double t_wavelength,
                       const double t_ref_index, const double t_albedo, const double t_interaction, const double t_anisotropy) :
            m_pos(t_pos),
            m_dir(t_dir),
            m_weight(1.0),
            m_wavelength(t_wavelength),
            m_ref_index(t_ref_index),
            m_albedo(t_albedo),
            m_interaction(t_interaction),
            m_anisotropy(t_anisotropy),
            m_time(0.0)
        {
            assert(m_dir.is_normalised());
        }


        //  -- Initialisation --



    } // namespace phys
} // namespace arc
