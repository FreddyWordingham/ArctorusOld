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



        //  == METHODS ==
        //  -- Getters --
        /**
         *  Get the lower bound of wavelengths created by the lights.
         *
         *  @return The lower bound of wavelengths created by the lights.
         */
        double LightList::get_lower_bound() const
        {
            // Determine the value of the lower bound.
            double r_lower_bound = m_light[0].get_lower_bound();
            for (size_t i=1; i<m_light.size(); ++i)
            {
                if (m_light[i].get_lower_bound() < r_lower_bound)
                {
                    r_lower_bound = m_light[i].get_lower_bound();
                }
            }

            return (r_lower_bound);
        }

        /**
         *  Get the upper bound of wavelengths created by the lights.
         *
         *  @return The upper bound of wavelengths created by the lights.
         */
        double LightList::get_upper_bound() const
        {
            // Determine the value of the upper bound.
            double r_upper_bound = m_light[0].get_upper_bound();
            for (size_t i=1; i<m_light.size(); ++i)
            {
                if (m_light[i].get_upper_bound() < r_upper_bound)
                {
                    r_upper_bound = m_light[i].get_upper_bound();
                }
            }

            return (r_upper_bound);
        }



    } // namespace sim
} // namespace arc
