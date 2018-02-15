/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   15/02/2018.
 */



//  == HEADER ==
#include "cls/reader/json.hpp"



//  == INCLUDES ==
//  -- System --



//  == NAMESPACE ==
namespace arc
{
    namespace reader
    {



        //  == INSTANTIATION ==
        //  -- Constructors --
        Json::Json(const std::string& t_name, const std::string& t_serial) :
            m_name(t_name),
            m_data(init_data(t_serial))
        {
        }


        //  -- Initialisation --



    } // namespace reader
} // namespace arc
