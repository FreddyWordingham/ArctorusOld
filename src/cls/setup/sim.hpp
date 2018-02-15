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
#include "cls/equip/entity.hpp"
#include "cls/equip/light.hpp"
#include "cls/data/json.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace setup
    {



        //  == CLASS ==
        /**
         *  Simulation class which holds all objects required to run a simulation.
         */
        class Sim
        {
            //  == FIELDS ==
          private:
            //  -- Equipment --
            const std::vector<equip::Light>  m_light;   //! Vector of light objects.
            const std::vector<equip::Entity> m_entity;  //! Vector of entity objects.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            Sim(const data::Json& t_param);
            Sim(const std::string& t_serial);

          private:
            //  -- Initialisation --
            std::vector<equip::Light> init_light(const data::Json& t_param) const;


            //  == OPERATORS ==
          private:


            //  == METHODS ==
          public:
            //  -- Rendering --
            void render() const;
        };



    } // namespace setup
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_SETUP_SIM_HPP
