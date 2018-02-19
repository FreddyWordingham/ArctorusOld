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
        Photon::Photon(const math::Vec<3>& t_pos, const math::Vec<3>& t_dir, double t_wavelength, double t_ref_index,
                       double t_albedo, double t_interaction, double t_anisotropy) :
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
