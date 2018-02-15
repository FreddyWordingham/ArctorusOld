/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   15/02/2018.
 */



//  == HEADER ==
#include "cls/setup/sim.hpp"



//  == INCLUDES ==
//  -- Utility --
#include "utl/conversion.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace setup
    {



        //  == INSTANTIATION ==
        //  -- Constructors --
        Sim::Sim(const data::Json& t_json) :
            m_light(init_light(t_json["lights"]))
        {
        }

        Sim::Sim(const std::string& t_serial) :
            Sim(data::Json("sim", t_serial))
        {
        }


        //  -- Initialisation --
        /**
         *  Initialise the vector of light objects.
         *
         *  @param  t_json Json setup file.
         *
         *  @return The initialise vector of light objects.
         */
        std::vector<equip::Light> Sim::init_light(const data::Json& t_json) const
        {
            // Create the return vector of lights.
            std::vector<equip::Light> r_light;

            // Get list of light names.
            std::vector<std::string> light_name = t_json.get_child_names();

            // Construct the light objects.
            for (size_t i = 0; i < light_name.size(); ++i)
            {
                LOG("Constructing light : " << light_name[i]);

                // Create a json object of the light.
                const data::Json json_light = t_json[light_name[i]];

                // Get the transformation values.
                const math::Vec<3> trans = json_light.parse_child<math::Vec<3>>("trans", math::Vec<3>({{0.0, 0.0, 0.0}}));
                const math::Vec<3> dir   = json_light.parse_child<math::Vec<3>>("dir", math::Vec<3>({{0.0, 0.0, 0.0}}));
                const double       rot   = utl::deg_to_rad(json_light.parse_child<double>("rot", 0.0));
                const math::Vec<3> scale = json_light.parse_child<math::Vec<3>>("scale", math::Vec<3>({{0.0, 0.0, 0.0}}));
            }

            return (r_light);
        }



    } // namespace setup
} // namespace arc
