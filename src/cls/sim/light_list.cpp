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
            m_light(t_light)
        {
        }



    } // namespace sim
} // namespace arc
