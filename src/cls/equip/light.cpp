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
         *  @param  t_mat   Material describing the created photons optical properties.
         *  @param  t_spec  Spectrum distribution.
         *  @param  t_power Power of the light source.
         *
         *  @post   m_power must be greater than zero.
         */
        Light::Light(const geom::Mesh& t_mesh, const phys::Material& t_mat, const phys::Spectrum& t_spec, const double t_power) :
            m_mesh(t_mesh),
            m_mat(t_mat),
            m_spec(t_spec),
            m_power(t_power)
        {
            assert(m_power > 0.0);
        }


        //  -- Initialisation --
        /**
         *  Initialise the vector of triangle areas by determining the area of each triangle and normalising the result.
         *
         *  @return The vector of normalised triangle areas.
         */
        std::vector<double> Light::init_tri_area() const
        {
            // Create the return vector.
            std::vector<double> r_tri_area(m_mesh.get_num_tri());

            // Compile the vector of areas and the total area.
            r_tri_area[0] = m_mesh.get_tri(0).get_area();
            for (size_t i = 1; i < m_mesh.get_num_tri(); ++i)
            {
                r_tri_area[i] = r_tri_area[i - 1] + m_mesh.get_tri(i).get_area();
            }

            // Normalise the areas.
            for (size_t i=0; i<m_tri_area.size(); ++i)
            {
                r_tri_area[i] /= r_tri_area.back();
            }

            return (r_tri_area);
        }



    } // namespace equip
} // namespace arc
