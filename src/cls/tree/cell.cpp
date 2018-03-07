/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   07/03/2018.
 */



//  == HEADER ==
#include "cls/tree/cell.hpp"



//  == INCLUDES ==
//  -- System --



//  == NAMESPACE ==
namespace arc
{
    namespace tree
    {



        //  == INSTANTIATION ==
        //  -- Constructors --
        /**
         *  Construct a root cell to record a given list of entity, light, ccd and spectrometer objects.
         *  Tree will reproduce until at least the minimum depth has been reached.
         *  Tree will stop reproducing until either the maxmium depth is reached, or the target maximum number of triangles has
         *  been reached.
         *
         *  @param  t_min_bound     Minimum spatial bound of the cell.
         *  @param  t_max_bound     Maximum spatial bound of the cell.
         *  @param  t_min_depth     Minimum depth for the cell to split to.
         *  @param  t_max_depth     Maximum depth for the cell to split to.
         *  @param  t_entity        Vector of entity objects which may lie within the cell.
         *  @param  t_light         Vector of light objects which may lie within the cell.
         *  @param  t_ccd           Vector of ccd objects which may lie within the cell.
         *  @param  m_spectrometer  Vector of spectrometer objects which may lie within the cell.
         *
         *  @post   m_half_width[X] must be positive.
         *  @post   m_half_width[Y] must be positive.
         *  @post   m_half_width[Z] must be positive.
         */
        Cell::Cell(const math::Vec<3>& t_min_bound, const math::Vec<3>& t_max_bound, const unsigned int t_min_depth,
                   const unsigned int t_max_depth, const std::vector<equip::Entity>& t_entity,
                   const std::vector<equip::Light>& t_light, const std::vector<detector::Ccd>& t_ccd,
                   const std::vector<detector::Spectrometer>& t_spectrometer) :
            m_center((t_max_bound + t_min_bound) / 2.0),
            m_half_width((t_max_bound - t_min_bound) / 2.0),
            m_entity(t_entity),
            m_light(t_light),
            m_ccd(t_ccd),
            m_spectrometer(t_spectrometer),
            m_light_tri_list(init_light_tri_list())
        {
            assert(m_half_width[X] > 0.0);
            assert(m_half_width[Y] > 0.0);
            assert(m_half_width[Z] > 0.0);
        }


        //  -- Initialisation --
        /**
         *  Initialise the list vector list of light triangles within the cell.
         *
         *  @return The initialised list vector of light triangles within the cell.
         */
        std::vector<std::array<size_t, 2>> Cell::init_light_tri_list() const
        {
            // Create the return triangle list.
            std::vector<std::array<size_t, 2>> r_light_tri_list;

            // Iterate through each of the light sources.
            for (size_t i = 0; i < m_light_tri_list; ++i)
            {
                // Iterate through each of the light's triangles.
                for (size_t j = 0; j < m_light_tri_list[i].get_mesh().get_num_tri(); ++j)
                {
                    // If the cell overlaps any part of the triangle, add the indices to the list.
                    if (overlap(m_light_tri_list[i].get_mesh().get_tri(j)))
                    {
                        r_light_tri_list.emplace_back({{i, j}});
                    }
                }
            }

            return (r_light_tri_list);
        }



        //  == METHODS ==
        //  -- Overlap Test --
        /**
         *  Determine if a plane described by a given normal and point overlaps with the box centered at the origin.
         *
         *  @param  t_norm          Normal of the plane.
         *  @param  t_point         Point located on the plane.
         *
         *  @return True if the plane and box are intersecting.
         */
        bool Cell::plane_overlap(const math::Vec<3>& t_norm, const math::Vec<3>& t_point) const
        {
            math::Vec<3> min, max;

            for (size_t q = 0; q < 3; ++q)
            {
                double v = t_point[q];

                if (t_norm[q] > 0.0)
                {
                    min[q] = -m_half_width[q] - v;
                    max[q] = m_half_width[q] - v;
                }
                else
                {
                    min[q] = m_half_width[q] - v;
                    max[q] = -m_half_width[q] - v;
                }
            }

            return (((t_norm * min) <= 0.0) && ((t_norm * max) >= 0.0));
        }



    } // namespace tree
} // namespace arc
