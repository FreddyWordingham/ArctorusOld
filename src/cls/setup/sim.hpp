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
//  -- Classes --
#include "cls/data/json.hpp"
#include "cls/detector/ccd.hpp"
#include "cls/detector/spectrometer.hpp"
#include "cls/equip/entity.hpp"
#include "cls/equip/light.hpp"
#include "cls/mesh/grid.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace setup
    {



        //  == SETTINGS ==
        //  -- Numerical Simultion --
        constexpr const double SMOOTHING_LENGTH = 1E-12; //! Smoothing length applied to stop photons getting stuck.



        //  == CLASS ==
        /**
         *  Simulation class which holds all objects required to run a simulation.
         */
        class Sim
        {
            //  == FIELDS ==
          private:
            //  -- Settings --
            const unsigned long int m_num_phot; //! Number of photons to simulate.

            //  -- Roulette --
            const double m_roulette_weight;     //! Roulette threshold.
            const double m_roulette_chambers;   //! Number of roulette chambers.

            //  -- Equipment --
            const phys::Material                m_aether;       //! Aether material.
            const std::vector<equip::Entity>    m_entity;       //! Vector of entity objects.
            const std::vector<equip::Light>     m_light;        //! Vector of light objects.
            std::vector<detector::Ccd>          m_ccd;          //! Vector of ccd objects.
            std::vector<detector::Spectrometer> m_spectrometer; //! Vector of spectrometer objects.

            //  -- Tools --
            const random::Index m_light_select; //! Light selector.

            //  -- Data --
            mesh::Grid                                         m_grid;  //! Simulation grid.
            std::vector<std::vector<graphical::point::Photon>> m_path;  //! Vector of photon paths.


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
            //  -- Saving --
            void save_grid_images() const;
            void save_ccd_images() const;
            void save_spectrometer_data() const;

            //  -- Rendering --
            void render() const;

            //  -- Running --
            void run();
        };



    } // namespace setup
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_SETUP_SIM_HPP
