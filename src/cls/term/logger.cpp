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
#include <unistd.h>



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
         *  @param  init_stream Output stream to write the log to.
         *
         *  @return A reference to the initialised logger object.
         */
        Logger& Logger::get_instance(std::ostream& init_stream)
        {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wexit-time-destructors"
            static Logger log(init_stream);
#pragma clang diagnostic pop

            return (log);
        }


        //  -- Constructors --
        /**
         *  Construct a logger object which will write to a given stream.
         *
         *  @param  init_stream Output stream to write the log to.
         */
        Logger::Logger(std::ostream& init_stream) :
            stream(init_stream),
            text_cols(init_text_cols()),
            log_types(init_log_types()),
            indent_string(WRAP_INDENT, ' '),
            padding_string(TIME_WIDTH + TYPE_WIDTH, ' '),
            num_warnings(0),
            num_errors(0)
        {
            // TODO Print title card.
        }


        //  -- Destructors --
        /**
         *  Destruct the logger object.
         *  Report the number of recorded warnings and errors.
         */
        Logger::~Logger()
        {
            // TODO Print exit info.
        }


        //  -- Initialisation --
        /**
         *  Initialise the array of colour escape strings.
         *  Colouring is enabled whilst writing to cout and not being redirected to a file.
         *
         *  @return The array of initialised colour escape codes.
         */
        std::array<std::string, Logger::TOTAL_COLS> Logger::init_text_cols() const
        {
            std::array<std::string, TOTAL_COLS> init_text_cols;

            if ((&stream == &std::cout) && (isatty(fileno(stdout)) != 0))
            {

            }

            return (init_text_cols);
        }

        std::array<std::string, Logger::TOTAL_TYPES> Logger::init_log_types() const
        {
            std::array<std::string, TOTAL_TYPES> init_log_types;

            return (init_log_types);
        }



    } // namespace term
} // namespace arc
