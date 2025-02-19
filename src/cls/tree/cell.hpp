/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   07/03/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_TREE_CELL_HPP
#define ARCTORUS_SRC_CLS_TREE_CELL_HPP



//  == INCLUDES ==
//  -- Classes --
#include "cls/detector/ccd.hpp"
#include "cls/detector/spectrometer.hpp"
#include "cls/equip/entity.hpp"
#include "cls/equip/light.hpp"
#include "cls/math/vec.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace tree
    {



        //  == CLASS ==
        /**
         *  Adaptive regular mesh tree forming octal cuboid cells.
         */
        class Cell
        {
            //  == ENUMERATIONS ==
            //  -- Indices --
          private:
            /**
             *  Enumeration of the triangle list indices.
             */
            enum list_index
            {
                OBJ,    //! List object index.
                TRI     //! List triangle index.
            };


            //  == FIELDS ==
          private:
            //  -- Bounds --
            const math::Vec<3> m_center;        //! Center of the cell.
            const math::Vec<3> m_half_width;    //! Half width of the cell.

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

            //  -- Depth Data --
            const unsigned int m_depth; //! Depth of the cell within the tree.
            const bool         m_leaf;  //! True if the cell is a terminal cell.

            //  -- Children --
            const std::array<std::unique_ptr<Cell>, 8> m_child; //! Array of child cell pointers.

            //  -- Data --
            double m_energy = 0.0;  //! Total energy within the cell.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            Cell(unsigned int t_min_depth, unsigned int t_max_depth, unsigned int t_max_tri, const math::Vec<3>& t_min_bound,
                 const math::Vec<3>& t_max_bound, const std::vector<equip::Entity>& t_entity,
                 const std::vector<equip::Light>& t_light, const std::vector<detector::Ccd>& t_ccd,
                 const std::vector<detector::Spectrometer>& t_spectrometer);
            Cell(unsigned int t_depth, unsigned int t_min_depth, unsigned int t_max_depth, unsigned int t_max_tri,
                 const math::Vec<3>& t_center, const math::Vec<3>& t_half_width, const std::vector<equip::Entity>& t_entity,
                 const std::vector<equip::Light>& t_light, const std::vector<detector::Ccd>& t_ccd,
                 const std::vector<detector::Spectrometer>& t_spectrometer,
                 const std::vector<std::array<size_t, 2>>& t_entity_tri_list,
                 const std::vector<std::array<size_t, 2>>& t_light_tri_list,
                 const std::vector<std::array<size_t, 2>>& t_ccd_tri_list,
                 const std::vector<std::array<size_t, 2>>& t_spectrometer_tri_list);

          private:
            //  -- Initialisation --
            std::vector<std::array<size_t, 2>> init_entity_tri_list() const;
            std::vector<std::array<size_t, 2>> init_entity_tri_list(
                const std::vector<std::array<size_t, 2>>& t_entity_tri_list) const;
            std::vector<std::array<size_t, 2>> init_light_tri_list() const;
            std::vector<std::array<size_t, 2>> init_light_tri_list(
                const std::vector<std::array<size_t, 2>>& t_light_tri_list) const;
            std::vector<std::array<size_t, 2>> init_ccd_tri_list() const;
            std::vector<std::array<size_t, 2>> init_ccd_tri_list(
                const std::vector<std::array<size_t, 2>>& t_ccd_tri_list) const;
            std::vector<std::array<size_t, 2>> init_spectrometer_tri_list() const;
            std::vector<std::array<size_t, 2>> init_spectrometer_tri_list(
                const std::vector<std::array<size_t, 2>>& t_light_spectrometer_list) const;
            bool init_leaf(unsigned int t_min_depth, unsigned int t_max_depth, unsigned int t_max_tri) const;
            std::array<std::unique_ptr<Cell>, 8> init_child(unsigned int t_min_depth, unsigned int t_max_depth,
                                                            unsigned int t_max_tri) const;


            //  == METHODS ==
          public:
            //  -- Getters --
            double get_vol() const { return ((m_half_width[X] * 2.0) * (m_half_width[Y] * 2.0) * (m_half_width[Z] * 2.0)); }
            double get_energy_density() const;
            std::vector<std::vector<std::vector<double>>> get_data_cube(size_t t_depth) const;
            bool is_leaf() const { return (m_leaf); }
            const std::unique_ptr<Cell>& get_child(const size_t t_index) const { return (m_child[t_index]); }
            unsigned long int get_total_cells() const;
            size_t get_max_tri() const;
            Cell* get_leaf(const math::Vec<3>& t_pos);
            bool is_within(const math::Vec<3>& t_pos) const;
            math::Vec<3> get_min_bound() const { return (m_center - m_half_width); }
            math::Vec<3> get_max_bound() const { return (m_center + m_half_width); }
            double get_dist_to_wall(const math::Vec<3>& t_pos, const math::Vec<3>& t_dir) const;
            std::tuple<bool, double, size_t, size_t> entity_dist(const math::Vec<3>& t_pos, const math::Vec<3>& t_dir) const;
            std::tuple<bool, double, size_t, size_t> ccd_dist(const math::Vec<3>& t_pos, const math::Vec<3>& t_dir) const;
            std::tuple<bool, double, size_t, size_t> spectrometer_dist(const math::Vec<3>& t_pos,
                                                                       const math::Vec<3>& t_dir) const;

            //  -- Setters --
            void add_energy(double t_energy);

          private:
            //  -- Overlap Test --
            bool tri_overlap(const geom::Triangle& t_tri) const;
            bool plane_overlap(const math::Vec<3>& t_norm, const math::Vec<3>& t_point) const;
        };



    } // namespace tree
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_TREE_CELL_HPP
