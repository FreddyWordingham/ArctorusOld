/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   09/02/2018.
 */



//  == HEADER ==
#include "cls/equip/light.hpp"



//  == INCLUDES ==
//  -- General --
#include "gen/log.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace equip
    {



        //  == INSTANTIATION ==
        //  -- Constructors --
        /**
         *  Construct a light from a given mesh and spectrum.
         *
         *  @param  t_mesh  Mesh to describe the surface of the light.
         *  @param  t_mat   Material describing the created photons optical properties.
         *  @param  t_spec  Spectrum distribution.
         *  @param  t_power Power of the light source.
         *
         *  @post   m_power must be greater than zero.
         */
        Light::Light(const geom::Mesh& t_mesh, const phys::Material& t_mat, const phys::Spectrum& t_spec,
                     const double t_power) :
            m_min_bound(std::max(t_mat.get_min_bound(), t_spec.get_min_bound())),
            m_max_bound(std::min(t_mat.get_max_bound(), t_spec.get_max_bound())),
            m_mesh(t_mesh),
            m_mat(t_mat),
            m_spec(t_spec),
            m_tri_select(init_rand_tri()),
            m_power(t_power)
        {
            if (m_min_bound >= m_max_bound)
            {
                ERROR("Unable to construct equip::Light object.",
                      "Wavelength ranges of given phys::Material and phys::Spectrum do not overlap.");
            }

            assert(m_power > 0.0);
        }


        //  -- Initialisation --
        /**
         *  Initialise the random triangle index generator.
         *
         *  @return The random triangle index generator.
         */
        random::Index Light::init_rand_tri() const
        {
            // Create vector of triangle areas.
            std::vector<double> r_tri_area(m_mesh.get_num_tri());

            // Get areas of each triangle.
            for (size_t i = 0; i < m_mesh.get_num_tri(); ++i)
            {
                r_tri_area[i] = m_mesh.get_tri(i).get_area();
            }

            return (random::Index(r_tri_area));
        }



        //  == METHODS ==
        //  -- Generation --
        /**
         *  Generate a photon at a random point on the light's surface with optical properties determined by the light's
         *  material.
         *
         *  @return The newly generated photon.
         */
        phys::particle::Photon Light::gen_photon() const
        {
            // Get a random position and normal from the mesh.
            const std::array<math::Vec<3>, 2> tri_pos_norm = m_mesh.get_tri(m_tri_select.gen_index()).get_random_pos_and_norm();

            return (phys::particle::Photon(tri_pos_norm[0], tri_pos_norm[1], 0.0, 1.0, m_spec.gen_wavelength(), m_mat));
        }



    } // namespace equip
} // namespace arc
