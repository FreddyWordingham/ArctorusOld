/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   07/02/2018.
 */



//  == HEADER ==
#include "cls/phys/particle/photon.hpp"



//  == INCLUDES ==
//  -- General --
#include "gen/constants.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace phys
    {
        namespace particle
        {



            //  == INSTANTIATION ==
            //  -- Constructors --
            /**
             *  Construct a photon packet at a given position with an initial direction at an emission time and
             *  initial statistical weight and wavelength.
             *
             *  @param  t_pos           Initial position of the photon packet.
             *  @param  t_dir           Initial direction of the photon packet.
             *  @param  t_time          Emission time of the photon packet.
             *  @param  t_wavelength    Initial wavelength of the photon packet.
             *  @param  t_weight        Initial statistical weight of the photon packet.
             *  @param  t_ref_index     Initial refractive index.
             *  @param  t_albedo        Initial albedo.
             *  @param  t_interaction   Initial interaction coefficient.
             *  @param  t_anisotropy    Initial anisotropy value.
             *
             *  @post   n_dir must be normalised.
             *  @post   m_time must be greater than, or equal to, zero
             *  @post   m_wavelength must be positive.
             *  @post   n_weight must be positive.
             *  @post   m_ref_index must be positive.
             *  @post   m_albedo must be greater than, or equal to, zero.
             *  @post   m_interaction must be greater than zero.
             *  @post   m_anisotropy must be greater than, or equal to, minus one and must be less than, or equal to, one.
             */
            Photon::Photon(const math::Vec<3>& t_pos, const math::Vec<3>& t_dir, const double t_time, const double t_wavelength,
                           const double t_weight, const double t_ref_index, const double t_albedo, const double t_interaction,
                           const double t_anisotropy) :
                Particle(t_pos, t_dir, t_time, t_weight),
                m_wavelength(t_wavelength),
                m_ref_index(t_ref_index),
                m_albedo(t_albedo),
                m_interaction(t_interaction),
                m_anisotropy(t_anisotropy)
            {
                assert(n_dir.is_normalised());
                assert(n_time >= 0.0);
                assert(m_wavelength > 0.0);
                assert(n_weight > 0.0);
                assert(m_ref_index > 0.0);
                assert(m_albedo >= 0.0);
                assert(m_interaction > 0.0);
                assert((m_anisotropy >= -1.0) && (m_anisotropy <= 1.0));

                // Record the initial position of the photon.
                record_path();
            }



            //  == METHODS ==
            //  -- Simulation --
            /**
             *  Move the photon a given distance.
             *
             *  @param  t_dist  Distance to move the photon.
             *
             *  @pre    t_dist must be greater than zero.
             */
            void Photon::move(const double t_dist)
            {
                assert(t_dist > 0.0);

                // Move the photons position.
                n_pos[X] += n_dir[X] * t_dist;
                n_pos[Y] += n_dir[Y] * t_dist;
                n_pos[Z] += n_dir[Z] * t_dist;

                // Update the time.
                n_time += (t_dist * m_ref_index) / SPEED_OF_LIGHT;

                // Record the new position of the photon.
                record_path();
            }


            //  -- Data --
            /**
             *  Record the current properties of the photon to the path data.
             */
            void Photon::record_path()
            {
                m_path.emplace_back(graphical::point::Photon({n_pos[X], n_pos[Y], n_pos[Z]}, static_cast<float>(m_wavelength),
                                                             static_cast<float>(n_weight), static_cast<float>(n_time)));
            }



        } // namespace particle
    } // namespace phys
} // namespace arc
