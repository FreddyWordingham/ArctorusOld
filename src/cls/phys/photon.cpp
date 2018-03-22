/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   19/02/2018.
 */



//  == HEADER ==
#include "cls/phys/photon.hpp"



//  == INCLUDES ==
//  -- General --
#include "gen/constants.hpp"
#include "gen/math.hpp"



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
         *  @post   m_time must be non-negative.
         *  @post   m_weight must be unity.
         *  @post   m_wavelength must be positive.
         *  @post   m_ref_index must be positive.
         *  @post   m_albedo must be non-negative.
         *  @post   m_interaction must be positive.
         *  @post   m_anisotropy must be between minus one and one.
         *  @post   m_entity_index must be of size one.
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
            m_entity_index({-1}),
            m_time(0.0)
        {
            assert(m_dir.is_normalised());
            assert(m_time >= 0.0);
            assert(m_weight == 1.0);
            assert(m_wavelength > 0.0);
            assert(m_ref_index > 0.0);
            assert(m_albedo >= 0.0);
            assert(m_interaction > 0.0);
            assert((m_anisotropy >= -1.0) && (m_anisotropy <= 1.0));
            assert(m_entity_index.size() == 1);

#ifdef ENABLE_PHOTON_PATHS
            // Record the initial position of the photon.
            record_path();
#endif
        }



        //  == METHODS ==
        //  -- Setters --
        /**
         *  Set the direction of the photon.
         *
         *  @param  t_dir   Direction to set.
         *
         *  @pre    t_dir must be normalised.
         *
         *  @post   m_dir must be normalised.
         */
        void Photon::set_dir(const math::Vec<3>& t_dir)
        {
            assert(t_dir.is_normalised());

            m_dir = t_dir;

            assert(m_dir.is_normalised());
        }

        /**
         *  Move the photon a given distance.
         *
         *  @param  t_dist  Distance to move the photon.
         *
         *  @pre    t_dist must be greater than zero.
         *  @pre    m_dir must be normalised.
         */
        void Photon::move(const double t_dist)
        {
            assert(t_dist > 0.0);
            assert(m_dir.is_normalised());

            // Move the photons position.
            m_pos[X] += m_dir[X] * t_dist;
            m_pos[Y] += m_dir[Y] * t_dist;
            m_pos[Z] += m_dir[Z] * t_dist;

            // Update the time.
            m_time += (t_dist * m_ref_index) / SPEED_OF_LIGHT;

#ifdef ENABLE_PHOTON_PATHS
            // Record the new position of the photon.
            record_path();
#endif
        }

        /**
         *  Change the photon's wavelength
         *
         *  @param  t_wavelength_change  New wavelength of the photon.
         *
         */
        void Photon::change_wavelength(const double t_wavelength_change)
        {
            // Change the wavelength of the photon.
            m_wavelength = m_wavelength - t_wavelength_change;
        }


        /**
         *  Rotate the particle by a given declination and then a given azimuthal rotation.
         *
         *  @param  t_dec   Declination angle away from current direction vector.
         *  @param  t_azi   Azimuthal rotation around current direction vector.
         *
         *  @pre    n_dir must be normalised.
         *  @pre    t_dec must be between zero and pi.
         *  @pre    t_azi must be between zero and two pi.
         *
         *  @post   n_dir must be normalised.
         */
        void Photon::rotate(const double t_dec, const double t_azi)
        {
            assert(m_dir.is_normalised());
            assert((t_dec >= 0.0) && (t_dec <= M_PI));
            assert((t_azi >= 0.0) && (t_azi <= 2.0 * M_PI));

            if (std::fabs(1.0 - std::fabs(m_dir[Z])) < 1E-10)
            {
                m_dir[X] = std::sin(t_dec) * std::cos(t_azi);
                m_dir[Y] = std::sin(t_dec) * std::sin(t_azi);
                m_dir[Z] = math::sign(m_dir[Z]) * std::cos(t_dec);
            }
            else
            {
                const math::Vec<3> prev_dir = m_dir;

                const double a         = std::sqrt(1.0 - math::square(prev_dir[Z]));
                const double sin_theta = std::sin(t_dec);
                const double cos_theta = std::cos(t_dec);
                const double sin_phi   = std::sin(t_azi);
                const double cos_phi   = std::cos(t_azi);

                m_dir[X] = ((sin_theta / a) * ((prev_dir[X] * prev_dir[Z] * cos_phi) - (prev_dir[Y] * sin_phi))) + (prev_dir[X] * cos_theta);
                m_dir[Y] = ((sin_theta / a) * ((prev_dir[Y] * prev_dir[Z] * cos_phi) + (prev_dir[X] * sin_phi))) + (prev_dir[Y] * cos_theta);
                m_dir[Z] = (prev_dir[Z] * cos_theta) - (sin_theta * cos_phi * a);
            }

            m_dir.normalise();

            assert(m_dir.is_normalised());
        }

        /**
         *  Multiply the photon's current statistical weight by a given value.
         *
         *  @param  t_mult  Multiplier.
         *
         *  @pre    t_mult must be positive.
         */
        void Photon::multiply_weight(const double t_mult)
        {
            assert(t_mult >= 0.0);

            m_weight *= t_mult;
        }

        /**
         *  Set the photon's optical properties using the given material.
         *
         *  @param  t_mat   Material used to set the optical properties.
         *
         *  @pre    m_wavelength must be within the bounds of t_mat.
         *  @post   m_ref_index must be positive.
         *  @post   m_albedo must be non-negative.
         *  @post   m_interaction must be positive.
         *  @post   m_anisotropy must be between minus one and one.
         */
        void Photon::set_opt(const phys::Material& t_mat)
        {
            assert((m_wavelength >= t_mat.get_min_bound()) && (m_wavelength <= t_mat.get_max_bound()));

            // Set optical properties.
            m_ref_index   = t_mat.get_ref_index(m_wavelength);
            m_albedo      = t_mat.get_albedo(m_wavelength);
            m_interaction = t_mat.get_interaction(m_wavelength);
            m_anisotropy  = t_mat.get_anisotropy(m_wavelength);

            assert(m_ref_index > 0.0);
            assert(m_albedo >= 0.0);
            assert(m_interaction > 0.0);
            assert((m_anisotropy >= -1.0) && (m_anisotropy <= 1.0));
        }


        //  -- Data --
#ifdef ENABLE_PHOTON_PATHS
        /**
         *  Record the current properties of the photon to the path data.
         */
        void Photon::record_path()
        {
            m_path.emplace_back(graphical::point::Photon({m_pos[X], m_pos[Y], m_pos[Z]}, static_cast<float>(m_wavelength),
                                                         static_cast<float>(m_weight), static_cast<float>(m_time)));
        }
#endif



    } // namespace phys
} // namespace arc
