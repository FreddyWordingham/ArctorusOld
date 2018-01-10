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
#include <gen/ansi.hpp>
#include <unistd.h>

//  -- Utility --
#include "utl/string.hpp"



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
            print_title_card();
        }


        //  -- Destructors --
        /**
         *  Destruct the logger object.
         *  Report the number of recorded warnings and errors.
         */
        Logger::~Logger()
        {
            print_hr('=');

            // TODO Print exit info.

            print_hr('=');
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
                init_text_cols[RESET]   = ansi::RESET;
                init_text_cols[BLACK]   = ansi::BLACK;
                init_text_cols[RED]     = ansi::RED;
                init_text_cols[GREEN]   = ansi::GREEN;
                init_text_cols[YELLOW]  = ansi::YELLOW;
                init_text_cols[BLUE]    = ansi::BLUE;
                init_text_cols[MAGENTA] = ansi::MAGENTA;
                init_text_cols[CYAN]    = ansi::CYAN;
                init_text_cols[WHITE]   = ansi::WHITE;
            }

            return (init_text_cols);
        }

        /**
         *  Initialise the array of log type string identifiers.
         *
         *  @return The array of initialised log type string identifiers.
         */
        std::array<std::string, Logger::TOTAL_TYPES> Logger::init_log_types() const
        {
            std::array<std::string, TOTAL_TYPES> init_log_types;

            init_log_types[LOG]   = std::string(LOG_TYPE_STRING);
            init_log_types[VERB]  = std::string(VERB_TYPE_STRING);
            init_log_types[VAL]   = std::string(VAL_TYPE_STRING);
            init_log_types[WARN]  = std::string(WARN_TYPE_STRING);
            init_log_types[ERROR] = std::string(ERROR_TYPE_STRING);

            for (size_t i = 0; i < TOTAL_TYPES; ++i)
            {
                init_log_types[i].resize(TYPE_WIDTH, ' ');
            }

            return (init_log_types);
        }



        //  == METHODS ==
        //  -- Printing --
        /**
         *  Print a horizontal rule using a given character.
         *
         *  @param  hr_char Character used to draw the horizontal rule.
         */
        void Logger::print_hr(const char hr_char) const
        {
            stream << std::string(LINE_WIDTH, hr_char) << "\n";
        }

        /**
         *  Print the Arctorus title card.
         */
        void Logger::print_title_card() const
        {
            print_hr('=');

            std::string       title = TITLE_CARD;
            const std::string pre_title_pad((LINE_WIDTH - TITLE_WIDTH) / 2, ' ');
            const std::string post_title_pad(LINE_WIDTH - (TITLE_WIDTH + pre_title_pad.size()), ' ');

            while (!title.empty())
            {
                std::string line = title.substr(0, TITLE_WIDTH);
                title.erase(0, TITLE_WIDTH);

                utl::find_and_replace(line, "l", text_cols[CYAN] + "/" + text_cols[RESET]);
                utl::find_and_replace(line, "r", text_cols[CYAN] + R"(\)" + text_cols[RESET]);
                utl::find_and_replace(line, "M", text_cols[MAGENTA] + "~" + text_cols[RESET]);
                utl::find_and_replace(line, "B", text_cols[BLUE] + "~" + text_cols[RESET]);
                utl::find_and_replace(line, "G", text_cols[GREEN] + "~" + text_cols[RESET]);
                utl::find_and_replace(line, "Y", text_cols[YELLOW] + "~" + text_cols[RESET]);
                utl::find_and_replace(line, "R", text_cols[RED] + "~" + text_cols[RESET]);

                stream << pre_title_pad << line << post_title_pad << "\n";
            }

            print_hr('=');

            std::string       build = BUILD_INFO;
            const std::string pre_build_pad((LINE_WIDTH - build.size()) / 2, ' ');
            const std::string post_build_pad(LINE_WIDTH - (build.size() + pre_build_pad.size()), ' ');

            stream << pre_build_pad << build << post_build_pad << "\n";

            print_hr('=');
        }



    } // namespace term
} // namespace arc
