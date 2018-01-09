/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   09/01/2018.
 */



//  == HEADER ==
#include "cls/term/logger.hpp"



//  == INCLUDES ==
//  -- System --



//  == NAMESPACE ==
namespace arc
{
    namespace term
    {



        //  == INSTANTIATION ==
        //  -- Singleton --
        /**
         *  Retrieve an instance of the logger class.
         *  Implements a singleton whereby only one logger may be created.
         *  Uses lazy initialisation.
         *
         *  @param  stream  Output stream to write the log to.
         *
         *  @return A reference to the initialised logger object.
         */
        Logger& Logger::get_instance(std::ostream& stream)
        {
            static Logger log(output);

            return (log);
        }


        //  -- Constructors --
        Logger::Logger(std::ostream& stream);


        //  -- Destructors --
        Logger::~Logger();


        //  -- Initialisation --
        std::array<std::string, TOTAL_COLS> Logger::init_text_cols() const;
        std::array<std::string, TOTAL_TYPES> Logger::init_log_types() const;



    } // namespace term
} // namespace arc
