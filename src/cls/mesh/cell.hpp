/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   17/02/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_MESH_CELL_HPP
#define ARCTORUS_SRC_CLS_MESH_CELL_HPP



//  == INCLUDES ==
//  -- System --
#include <array>
#include <mutex>
#include <vector>

//  -- Classes --
#include "cls/detector/ccd.hpp"
#include "cls/detector/spectrometer.hpp"
#include "cls/equip/entity.hpp"
#include "cls/equip/light.hpp"
#include "cls/math/vec.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace mesh
    {



        //  == CLASS ==
        /**
         *  Information about a single cell of the simulation.
         */
        class Cell
        {
            //  == FIELDS ==
          private:
            //  -- Bounds --
            const math::Vec<3> m_min_bound; //! Minimum bound of the cell.
            const math::Vec<3> m_max_bound; //! Maximum bound of the cell.

            //  -- Equipment References --
            const std::vector<equip::Entity>         & m_entity;        //! Reference to vector of sim entities.
            const std::vector<equip::Light>          & m_light;         //! Reference to vector of sim lights.
            const std::vector<detector::Ccd>         & m_ccd;           //! Reference to vector of sim ccds.
            const std::vector<detector::Spectrometer>& m_spectrometer;  //! Reference to vector of sim spectrometers.

            //  -- Lists --
            const std::vector<std::array<size_t, 2>> m_entity_tri_list;         //! List of entity triangles inside cell.
            const std::vector<std::array<size_t, 2>> m_light_tri_list;          //! List of light triangles inside cell.
            const std::vector<std::array<size_t, 2>> m_ccd_tri_list;            //! List of ccd triangles inside cell.
            const std::vector<std::array<size_t, 2>> m_spectrometer_tri_list;   //! List of spectrometer triangles inside cell.

            //  -- Data --
            const bool m_empty;         //! True if the cell contains no triangles.
//            std::mutex m_energy_mutex;  //! Protects energy data.
            double     m_energy = 0.0;  //! Energy within the cell.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            Cell(const math::Vec<3>& t_min_bound, const math::Vec<3>& t_max_bound, const std::vector<equip::Entity>& t_entity,
                 const std::vector<equip::Light>& t_light, const std::vector<detector::Ccd>& t_ccd,
                 const std::vector<detector::Spectrometer>& t_spectrometer);
            Cell(Cell&& t_cell) noexcept;

          private:
            //  -- Initialisation --
            std::vector<std::array<size_t, 2>> init_entity_tri_list() const;
            std::vector<std::array<size_t, 2>> init_light_tri_list() const;
            std::vector<std::array<size_t, 2>> init_ccd_tri_list() const;
            std::vector<std::array<size_t, 2>> init_spectrometer_tri_list() const;
            bool tri_overlap(const math::Vec<3>& t_center, const math::Vec<3>& t_half_size, const geom::Triangle& t_tri) const;
            bool plane_origin_overlap(const math::Vec<3>& t_norm, const math::Vec<3>& t_point,
                                      const math::Vec<3>& t_half_width) const;


            //  == METHODS ==
          public:
            //  -- Getters --
            const math::Vec<3>& get_min_bound() const { return (m_min_bound); }
            const math::Vec<3>& get_max_bound() const { return (m_max_bound); }
            double get_volume() const { return ((m_max_bound[X] - m_min_bound[X]) * (m_max_bound[Y] - m_min_bound[Y]) * (m_max_bound[Z] - m_min_bound[Z])); }
            double get_energy_density() const { return (m_energy / get_volume()); }
            bool empty() const { return (m_empty); }
            double get_dist_to_wall(const math::Vec<3>& t_pos, const math::Vec<3>& t_dir) const;
            std::tuple<bool, double, size_t, size_t> entity_dist(const math::Vec<3>& t_pos, const math::Vec<3>& t_dir) const;
            std::tuple<bool, double, size_t, size_t> ccd_dist(const math::Vec<3>& t_pos, const math::Vec<3>& t_dir) const;
            std::tuple<bool, double, size_t, size_t> spectrometer_dist(const math::Vec<3>& t_pos,
                                                                       const math::Vec<3>& t_dir) const;

            //  -- Setters --
            void add_energy(double t_energy);

            //  -- Testing --
            bool is_within(const math::Vec<3>& t_pos) const;
        };



    } // namespace mesh
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_MESH_CELL_HPP
