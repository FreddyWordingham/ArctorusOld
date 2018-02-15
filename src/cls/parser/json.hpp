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
            Json(const std::string &t_name, const std::string& t_serial);
            Json(const std::string &t_name, const nlohmann::json& t_data);

          private:
            //  -- Initialisation --
            nlohmann::json init_data(const std::string& t_serial) const;


            //  == OPERATORS ==
          private:


            //  == METHODS ==
          private:
        };



    } // namespace parser
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_PARSER_JSON_HPP
