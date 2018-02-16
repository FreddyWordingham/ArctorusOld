/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   15/02/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_PARSER_JSON_HPP
#define ARCTORUS_SRC_CLS_PARSER_JSON_HPP



//  == INCLUDES ==
//  -- General --
#include "gen/log.hpp"

//  -- Library --
#include "lib/nlohmann.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace parser
    {



        //  == SETTINGS ==
        //  -- Printing --
        constexpr const int INDENT_WIDTH = 4;   //! Number of indentation spaces to use when printing the json object.



        //  == CLASS ==
        /**
         *  A reader class used to read data from json files.
         */
        class Json
        {
            //  == FIELDS ==
          private:
            //  -- Data --
            const std::string    m_name;    //! Name of the base object.
            const nlohmann::json m_data;    //! Base json data object to parse from.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            Json(const std::string& t_name, const std::string& t_serial);
            Json(const std::string& t_name, const nlohmann::json& t_data);

          private:
            //  -- Initialisation --
            nlohmann::json init_data(const std::string& t_serial) const;


            //  == OPERATORS ==
          public:
            //  -- Access --
            Json operator[](const std::string& t_child) const;

            //  -- Printing --
            friend std::ostream& operator<<(std::ostream& t_stream, const Json& t_json);


            //  == METHODS ==
          public:
            //  -- Parsing --
            std::vector<std::string> parse_child_names() const;
            template <typename T>
            T parse() const;

            //  -- Properties --
            bool has_child(const std::string& t_child) const { return (!(m_data.find(t_child) == m_data.end())); }

            //  -- Serialisation --
            std::string serialise() const;

            //  -- Saving --
            void save(const std::string& t_path) const;
        };



        //  == METHODS ==
        //  -- Parsing --
        /**
         *  Parse a value from the json data object.
         *
         *  @tparam T   Type to be parsed from the base json data object.
         *
         *  @return The value from the json data object.
         */
        template <typename T>
        T Json::parse() const
        {
            try
            {
                return (m_data.get<T>());
            }
            catch (...)
            {
                ERROR("Unable to parse value from data::Json object.",
                      "Base data::Json object: '" << m_name << "' could not be converted to type: '" << typeid(T).name()
                                                  << "' as required.");
            }
        }



    } // namespace parser
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_PARSER_JSON_HPP
