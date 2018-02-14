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


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --

          private:
            //  -- Initialisation --


            //  == OPERATORS ==
          private:


            //  == METHODS ==
          private:
        };



    } // namespace sim
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_SIM_LIGHT_LIST_HPP
