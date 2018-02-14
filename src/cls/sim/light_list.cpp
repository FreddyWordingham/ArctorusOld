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
         *  Get the min bound of wavelengths created by the lights.
         *
         *  @return The min bound of wavelengths created by the lights.
         */
        double LightList::get_min_bound() const
        {
            // Determine the value of the min bound.
            double r_min_bound = m_light[0].get_min_bound();
            for (size_t i=1; i<m_light.size(); ++i)
            {
                if (m_light[i].get_min_bound() < r_min_bound)
                {
                    r_min_bound = m_light[i].get_min_bound();
                }
            }

            return (r_min_bound);
        }

        /**
         *  Get the max bound of wavelengths created by the lights.
         *
         *  @return The max bound of wavelengths created by the lights.
         */
        double LightList::get_max_bound() const
        {
            // Determine the value of the max bound.
            double r_max_bound = m_light[0].get_max_bound();
            for (size_t i=1; i<m_light.size(); ++i)
            {
                if (m_light[i].get_max_bound() < r_max_bound)
                {
                    r_max_bound = m_light[i].get_max_bound();
                }
            }

            return (r_max_bound);
        }



    } // namespace sim
} // namespace arc
