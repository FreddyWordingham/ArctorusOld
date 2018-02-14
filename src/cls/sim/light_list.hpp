/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   14/02/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_SIM_LIGHT_LIST_HPP
#define ARCTORUS_SRC_CLS_SIM_LIGHT_LIST_HPP



//  == INCLUDES ==
//  -- Classes --
#include "cls/equip/light.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace sim
    {



        //  == CLASS ==
        /**
         *  A class holding all of a simulation's light objects.
         */
        class LightList
        {
            //  == FIELDS ==
          private:
            //  -- Data --
            std::vector<equip::Light> m_light;  //! Vector of light objects.

            //  -- Pickers --
            random::Index m_light_select;   //! Light index selector.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            explicit LightList(const std::vector<equip::Light>& t_light);

            //  -- Initialisation --
            random::Index init_light_select() const;


            //  == METHODS ==
          public:
            //  -- Getters --
            double get_min_bound() const;
            double get_max_bound() const;
            const equip::Light& get_light(const size_t t_index) const { return (m_light[t_index]); }
        };



    } // namespace sim
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_SIM_LIGHT_LIST_HPP
