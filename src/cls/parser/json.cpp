/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   15/02/2018.
 */



//  == HEADER ==
#include "cls/parser/json.hpp"



//  == INCLUDES ==
//  -- General --
#include "gen/log.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace parser
    {



        //  == INSTANTIATION ==
        //  -- Constructors --
        /**
         *  Construct a json object from a serialised json object.
         *
         *  @param  t_name      Name of the base json object.
         *  @param  t_serial    Serialised json object.
         */
        Json::Json(const std::string& t_name, const std::string& t_serial) :
            m_name(t_name),
            m_data(init_data(t_serial))
        {
        }

        /**
         *  Construct a json object using a given name and a sub-json data object.
         *
         *  @param  t_name  Name of the new json object.
         *  @param  t_data  New json data.
         */
        Json::Json(const std::string& t_name, const nlohmann::json& t_data) :
            m_name(t_name),
            m_data(t_data)
        {
        }


        //  -- Initialisation --
        /**
         *  Initialise the base json data object using the serialised json data object.
         *  Parsing errors are not tolerated.
         *
         *  @param  t_serial    Serialised json data object.
         *
         *  @return The initialised json data object.
         */
        nlohmann::json Json::init_data(const std::string& t_serial) const
        {
            // Create the base json data object.
            nlohmann::json r_base;

            // Attempt to parse in the serialised json data.
            try
            {
                std::stringstream(t_serial) >> r_base;
            }
            catch (...)
            {
                ERROR("Unable to construct parser::Json object.", "Unable to parse serialised data of: '" << m_name << "'.");
            }

            return (r_base);
        }



        //  == OPERATORS ==
        //  -- Printing --
        /**
         *  Enable printing of a json object to a given ostream.
         *
         *  @param  t_stream    Stream to write to.
         *  @param  t_json      Json object to be written.
         *
         *  @return A reference to the stream post-print.
         */
        std::ostream& operator<<(std::ostream& t_stream, const Json& t_json)
        {
            t_stream << t_json.m_data.dump(INDENT_WIDTH);

            return (t_stream);
        }



    } // namespace parser
} // namespace arc
