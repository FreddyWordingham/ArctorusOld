/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   17/02/2018.
 */



//  == HEADER ==
#include "cls/mesh/cell.hpp"



//  == INCLUDES ==
//  -- General --
#include "gen/math.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace mesh
    {



        //  == INSTANTIATION ==
        //  -- Constructors --
        Cell::Cell(const math::Vec<3>& t_min_bound, const math::Vec<3>& t_max_bound, const std::vector<equip::Entity>& t_entity,
                   const std::vector<equip::Light>& t_light) :
            m_min_bound(t_min_bound),
            m_max_bound(t_max_bound),
            m_entity_list(init_entity_list(t_entity)),
            m_light_list(init_light_list(t_light)),
            m_empty(m_entity_list.empty && m_light_list.empty)
        {
            assert(t_max_bound[X] > t_min_bound[X]);
            assert(t_max_bound[Y] > t_min_bound[Y]);
            assert(t_max_bound[Z] > t_min_bound[Z]);
        }


        //  -- Initialisation --
        std::vector<std::array<size_t, 2>> Cell::init_entity_list(const std::vector<equip::Entity>& t_entity) const
        {
            std::vector<std::array<size_t, 2>> r_entity_list;

            const math::Vec<3> center    = (m_max_bound + m_min_bound) / 2.0;
            const math::Vec<3> half_size = (m_max_bound - m_min_bound) / 2.0;

            for (size_t i = 0; i < t_entity.size(); ++i)
            {
                for (size_t j = 0; j < t_entity[i].get_mesh().get_num_tri(); ++j)
                {
                    if (math::tri_cuboid_overlap(center, half_size, t_entity[i].get_mesh().get_tri(j)))
                    {
                        r_entity_list.push_back({{i, j}});
                    }
                }
            }

            return (r_entity_list);
        }

        std::vector<std::array<size_t, 2>> Cell::init_light_list(const std::vector<equip::Light>& t_light) const
        {
            std::vector<std::array<size_t, 2>> r_light_list;

            const math::Vec<3> center    = (m_max_bound + m_min_bound) / 2.0;
            const math::Vec<3> half_size = (m_max_bound - m_min_bound) / 2.0;

            for (size_t i = 0; i < t_light.size(); ++i)
            {
                for (size_t j = 0; j < t_light[i].get_mesh().get_num_tri(); ++j)
                {
                    if (math::tri_cuboid_overlap(center, half_size, t_light[i].get_mesh().get_tri(j)))
                    {
                        r_light_list.push_back({{i, j}});
                    }
                }
            }

            return (r_light_list);
        }



    } // namespace mesh
} // namespace arc
