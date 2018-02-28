/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   17/02/2018.
 */



//  == HEADER ==
#include "cls/mesh/grid.hpp"



//  == INCLUDES ==
//  -- Utility --
#include "utl/colourmap.hpp"
#include "utl/file.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace mesh
    {



        //  == INSTANTIATION ==
        //  -- Constructors --
        /**
         *  Construct a grid within given bounds.
         *
         *  @param  t_min_bound     Minimum grid bound.
         *  @param  t_max_bound     Maximum grid bound.
         *  @param  t_num_cells     Number of cells across each dimension.
         *  @param  t_entity        Vector of entities which may be contained within the grid.
         *  @param  t_light         Vector of lights which may be contained within the grid.
         *  @param  t_ccd           Vector of ccds which may be contained within the grid.
         *  @param  t_spectrometer  Vector of spectrometers which may be contained within the grid.
         */
        Grid::Grid(const math::Vec<3>& t_min_bound, const math::Vec<3>& t_max_bound, const std::array<size_t, 3> t_num_cells,
                   const std::vector<equip::Entity>& t_entity, const std::vector<equip::Light>& t_light,
                   const std::vector<detector::Ccd>& t_ccd, const std::vector<detector::Spectrometer>& t_spectrometer) :
            m_min_bound(t_min_bound),
            m_max_bound(t_max_bound),
            m_num_cells(t_num_cells),
            m_grid_vol(
                (m_max_bound[X] - m_min_bound[X]) * (m_max_bound[Y] - m_min_bound[Y]) * (m_max_bound[Z] - m_min_bound[Z])),
            m_cell_size(
                {{(m_max_bound[X] - m_min_bound[X]) / m_num_cells[X], (m_max_bound[Y] - m_min_bound[Y]) / m_num_cells[Y], (m_max_bound[Z] - m_min_bound[Z]) / m_num_cells[Z]}}),
            m_cell_vol(m_grid_vol / (m_num_cells[X] * m_num_cells[Y] * m_num_cells[Z])),
            m_cell(init_cell(t_entity, t_light, t_ccd, t_spectrometer))
        {
        }


        //  -- Initialisation --
        /**
         *  Initialise the three-dimensional vector of cells.
         *
         *  @param  t_entity        Vector of entities which may be contained within the grid.
         *  @param  t_light         Vector of lights which may be contained within the grid.
         *  @param  t_ccd           Vector of ccds which may be contained within the grid.
         *  @param  t_spectrometer  Vector of spectrometers which may be contained within the grid.
         *
         *  @return The initialised three-dimensional vector of cells.
         */
        std::vector<std::vector<std::vector<Cell>>> Grid::init_cell(const std::vector<equip::Entity>& t_entity,
                                                                    const std::vector<equip::Light>& t_light,
                                                                    const std::vector<detector::Ccd>& t_ccd, const std::vector<
            detector::Spectrometer>& t_spectrometer) const
        {
            // Calculate cell dimensions.
            math::Vec<3> cell_size = m_max_bound - m_min_bound;
            cell_size[X] /= m_num_cells[X];
            cell_size[Y] /= m_num_cells[Y];
            cell_size[Z] /= m_num_cells[Z];

            // Create three-dimensional vector of cells.
            std::vector<std::vector<std::vector<Cell>>> r_cell;

            // Create the cells.
            const double total_cells       = m_num_cells[X] * m_num_cells[Y] * m_num_cells[Z];
            double       constructed_cells = 0;

            r_cell.reserve(m_num_cells[X]);
            for (size_t i = 0; i < m_num_cells[X]; ++i)
            {
                r_cell.emplace_back(std::vector<std::vector<Cell>>());
                r_cell[i].reserve(m_num_cells[Y]);
                for (size_t j = 0; j < m_num_cells[Y]; ++j)
                {
                    r_cell[i].emplace_back(std::vector<Cell>());
                    r_cell[i][j].reserve(m_num_cells[Z]);
                    for (size_t k = 0; k < m_num_cells[Z]; ++k)
                    {
                        r_cell[i][j].emplace_back(Cell(math::Vec<3>(
                            {{m_min_bound[X] + (i * cell_size[X]), m_min_bound[Y] + (j * cell_size[Y]), m_min_bound[Z] + (k * cell_size[Z])}}),
                                                       math::Vec<3>(
                                                           {{m_min_bound[X] + ((i + 1) * cell_size[X]), m_min_bound[Y] + ((j + 1) * cell_size[Y]), m_min_bound[Z] + ((k + 1) * cell_size[Z])}}),
                                                       t_entity, t_light, t_ccd, t_spectrometer));

                        // Report grid construction.
                        TEMP("Constructing grid", 100.0 * (constructed_cells / total_cells));
                        ++constructed_cells;
                    }
                }
            }

            LOG("Grid construction complete.");

            return (r_cell);
        }



        //  == METHODS ==
        //  -- Getters --
        /**
         *  Determine the maximum energy density of a single cell within the grid.
         *
         *  @post   r_max_energy_density must be non-negative.
         *
         *  @return The maximum energy density of any cell within the grid.
         */
        double Grid::get_max_energy_density() const
        {
            // Create return value.
            double r_max_energy_density = 0.0;

            // Loop over every cell.
            for (size_t i = 0; i < m_num_cells[X]; ++i)
            {
                for (size_t j = 0; j < m_num_cells[Y]; ++j)
                {
                    for (size_t k = 0; k < m_num_cells[Z]; ++k)
                    {
                        const double energy_density = m_cell[i][j][k].get_energy_density();

                        if (energy_density > r_max_energy_density)
                        {
                            r_max_energy_density = energy_density;
                        }
                    }
                }
            }

            assert(r_max_energy_density >= 0.0);

            return (r_max_energy_density);
        }


        //  -- Saving --
        /**
         *  Save the data of the grid cells as image files.
         *
         *  @param  t_output_dir    Directory to write the images to.
         */
        void Grid::save_images(const std::string& t_output_dir) const
        {
            // Get maximum energy density.
            const double max_energy_density = get_max_energy_density();

            // Calculate energy density fractions.
            std::vector<std::vector<std::vector<double>>> energy_density;
            energy_density.reserve(m_num_cells[X]);
            for (size_t i = 0; i < m_num_cells[X]; ++i)
            {
                energy_density.emplace_back(std::vector<std::vector<double>>());
                energy_density[i].reserve(m_num_cells[Y]);
                for (size_t j = 0; j < m_num_cells[Y]; ++j)
                {
                    energy_density[i].emplace_back(std::vector<double>());
                    energy_density[i][j].reserve(m_num_cells[Z]);
                    for (size_t k = 0; k < m_num_cells[Z]; ++k)
                    {
                        energy_density[i][j]
                            .emplace_back(std::sqrt(std::sqrt(m_cell[i][j][k].get_energy_density() / max_energy_density)));
                    }
                }
            }

            // Write the slices.
            save_slices(t_output_dir, X, energy_density);
            save_slices(t_output_dir, Y, energy_density);
            save_slices(t_output_dir, Z, energy_density);
        }

        /**
         *  Save the slices of one dimension of the grid.
         *
         *  @param  t_output_dir    Directory to write the images to.
         *  @param  t_dimension     Dimension to be sliced.
         *  @param  t_data          Data to be sliced into images.
         *
         *  @pre    t_dimension must be less than three.
         */
        void Grid::save_slices(const std::string& t_output_dir, const size_t t_dimension,
                               const std::vector<std::vector<std::vector<double>>>& t_data) const
        {
            assert(t_dimension < 3);

            // Set dimensions.
            size_t      x, y, z = t_dimension;
            std::string dim_name;
            switch (z)
            {
                case X:
                    x        = Y;
                    y        = Z;
                    dim_name = "X";
                    break;
                case Y:
                    x        = X;
                    y        = Z;
                    dim_name = "Y";
                    break;
                case Z:
                    x        = X;
                    y        = Y;
                    dim_name = "Z";
                    break;
                default: ERROR("Unable to save grid slice images.", "The given dimension: '" << z << "' is invalid.");
            }

            // Create sub-directory.
            const std::string sub_dir = t_output_dir + "grid_" + dim_name + "_slices/";
            utl::create_directory(sub_dir);

            // Write the images.
            for (size_t i = 0; i < m_num_cells[z]; ++i)
            {
                TEMP("Saving " + dim_name + " slices", 100.0 * i / m_num_cells[z]);

                // Create the image.
                data::Image img(m_num_cells[x], m_num_cells[y]);

                // Write each pixel.
                for (size_t j = 0; j < m_num_cells[x]; ++j)
                {
                    for (size_t k = 0; k < m_num_cells[y]; ++k)
                    {
                        img.add_to_pixel(j, k, utl::colourmap::transform_rainbow(t_data[j][k][i]));
                    }
                }

                // Save the image.
                img.save(sub_dir + dim_name + "_" + std::to_string(i) + ".ppm");
            }
        }



    } // namespace mesh
} // namespace arc
