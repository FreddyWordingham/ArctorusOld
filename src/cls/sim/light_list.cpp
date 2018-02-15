/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   14/02/2018.
 */



//  == HEADER ==
#include "cls/sim/light_list.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace sim
    {



        //  == INSTANTIATION ==
        //  -- Constructors --
        /**
         *  Construct a light-list object from a vector of lights.
         *
         *  @param  t_light Vector of light objects.
         */
        LightList::LightList(const std::vector<equip::Light>& t_light) :
            m_light(t_light),
            m_light_select(init_light_select())
        {
        }


        //  -- Initialisation --
        /**
         *  Initialise the light index selector.
         *
         *  @return The initialised light index selector.
         */
        random::Index LightList::init_light_select() const
        {
            // Create vector of light powers.
            std::vector<double> light_pow(m_light.size());

            // Store the light powers.
            for (size_t i=0; i<light_pow.size(); ++i)
            {
                light_pow[i] = m_light[i].get_power();
            }

            return (random::Index(light_pow));
        }



    } // namespace sim
} // namespace arc
