/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   09/02/2018.
 */



//  == HEADER ==
#include "cls/equip/light.hpp"



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
         *  @param  t_spec  Spectrum distribution.
         *  @param  t_power Power of the light source.
         *
         *  @post   m_power must be greater than zero.
         */
        Light::Light(const geom::Mesh& t_mesh, const phys::Spectrum& t_spec, const double t_power) :
            m_mesh(t_mesh),
            m_spec(t_spec),
            m_tri_select(init_rand_tri()),
            m_power(t_power)
        {
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
         *  @param  t_mat   Material to sample initial optical properties from.
         *
         *  @return The newly generated photon.
         */
        phys::Photon Light::gen_photon(const phys::Material& t_mat) const
        {
            // Get a random position and normal from the mesh.
            math::Vec<3> pos, norm;
            std::tie(pos, norm) = m_mesh.get_tri(m_tri_select.gen_index()).gen_random_pos_and_norm();

            return (phys::Photon(pos, norm, m_spec.gen_wavelength(), t_mat));
        }



    } // namespace equip
} // namespace arc
