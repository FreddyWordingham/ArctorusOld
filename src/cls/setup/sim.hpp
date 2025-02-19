/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   15/02/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_SETUP_SIM_HPP
#define ARCTORUS_SRC_CLS_SETUP_SIM_HPP



//  == INCLUDES ==
//  -- System --
#include <mutex>
#include <random>
#include <thread>

//  -- Classes --
#include "cls/data/json.hpp"
#include "cls/detector/ccd.hpp"
#include "cls/detector/spectrometer.hpp"
#include "cls/equip/entity.hpp"
#include "cls/equip/light.hpp"
#include "cls/tree/cell.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace setup
    {



        //  == SETTINGS ==
        //  -- Numerical Simulation --
        constexpr const double SMOOTHING_LENGTH = 1E-12; //! Smoothing length applied to stop photons getting stuck.



        //  == CLASS ==
        /**
         *  Simulation class which holds all objects required to run a simulation.
         */
        class Sim
        {
            //  == ENUMERATIONS ==
            /**
             *  Enumeration of the main types of events a photon can undergo during the simulation.
             */
            enum class event
            {
                SCATTER,            //! Scattering event.
                CELL_CROSS,         //! Cell wall crossing.
                ENTITY_HIT,         //! Entity triangle hit.
                CCD_HIT,            //! Ccd triangle hit.
                SPECTROMETER_HIT    //! Spectrometer triangle hit.
            };


            //  == FIELDS ==
          private:
            //  -- Optimisations --
            const unsigned long int m_loop_limit;           //! Maximum number of loops a photon may make.
            const double            m_roulette_weight;      //! Roulette threshold.
            const double            m_roulette_chambers;    //! Number of roulette chambers.

            //  -- Equipment --
            const phys::Material                m_aether;       //! Aether material.
            const std::vector<equip::Entity>    m_entity;       //! Vector of entity objects.
            const std::vector<equip::Light>     m_light;        //! Vector of light objects.
            std::vector<detector::Ccd>          m_ccd;          //! Vector of ccd objects.
            std::vector<detector::Spectrometer> m_spectrometer; //! Vector of spectrometer objects.

            //  -- Tools --
            const random::Index m_light_select; //! Light selector.

            //  -- Tree --
            std::unique_ptr<tree::Cell> m_root;         //! Simulation cell tree.
            data::Histogram             m_scatters;     //! Histogram of photon total scatterings.
            data::Histogram             m_exit_weight;  //! Histogram of photon total scatterings.

            //  -- Data --
#ifdef ENABLE_PHOTON_PATHS
            std::vector<std::vector<graphical::point::Photon>> m_path;          //! Vector of photon paths.
            std::mutex                                         m_path_mutex;    //! Protects path data.
#endif

            //  -- Counters --
            double m_error_loop = 0.0;  //! Total weight of photons removed from sim due to running beyond max loop limit.
            double m_error_prox = 0.0;  //! Total weight of photons removed from sim due to proximity errors.

            //  -- Threads --
            std::mutex          m_ccd_mutex;            //! Protects the ccd objects data.
            std::mutex          m_spectrometer_mutex;   //! Protects the spectrometer objects data.
            std::mutex          m_cell_mutex;           //! Protects the cell data.
            std::mutex          m_counter_mutex;        //! Protects the error counters.
            std::mutex          m_hist_mutex;           //! Protects the data histograms.
            std::vector<double> m_thread_progress;      //! Current progress of each thread.
            const double        m_log_update_period;    //! Period with which to update a progress print.

            //  -- Random Number Generation --
            std::vector<std::mt19937>              m_rng_engine;    //! Random number generator engine.
            std::uniform_real_distribution<double> m_uniform_dist;  //! Distribution to draw random numbers from.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            explicit Sim(const data::Json& t_param);
            explicit Sim(const std::string& t_serial);

          private:
            //  -- Initialisation --
            phys::Material init_aether(const data::Json& t_json) const;
            std::vector<equip::Entity> init_entity(const data::Json& t_json) const;
            std::vector<equip::Light> init_light(const data::Json& t_json) const;
            std::vector<detector::Ccd> init_ccd(const data::Json& t_json) const;
            std::vector<detector::Spectrometer> init_spectrometer(const data::Json& t_json) const;
            random::Index init_light_select() const;


            //  == METHODS ==
          public:
            //  -- Getters --
            const data::Histogram& get_scatter_hist() const { return (m_scatters); }
            const data::Histogram& get_exit_weight_hist() const { return (m_exit_weight); }
            void get_error_report() const;

            //  -- Setters --
            void set_num_threads(unsigned int t_num_threads);

            //  -- Saving --
            void save_tree_images(const std::string& t_output_dir, size_t t_level) const;
            void save_ccd_images(const std::string& t_output_dir) const;
            void save_spectrometer_data(const std::string& t_output_dir) const;
            void save_histogram_data(const std::string& t_output_dir) const;

            //  -- Rendering --
            void render() const;

            //  -- Simulation --
            void run_photons(unsigned long int t_num_phot, size_t t_thread_index);

          private:
            //  -- Saving --
            void save_slices(const std::string& t_output_dir, size_t t_dimension,
                             const std::vector<std::vector<std::vector<double>>>& t_data) const;

            //  -- Simulation --
            std::tuple<event, double, size_t, size_t> determine_event(const phys::Photon& t_phot, const tree::Cell* t_cell,
                                                                      size_t t_thread_index);
            void log_progress() const;
        };



    } // namespace setup
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_SETUP_SIM_HPP
