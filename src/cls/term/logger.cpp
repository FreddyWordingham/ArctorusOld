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
#include <cassert>
#include <unistd.h>

//  -- General --
#include <gen/ansi.hpp>

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

            print_text(num_warnings == 0 ? GREEN : YELLOW, num_warnings == 0 ? LOG : WARN,
                       "Total warnings: " + std::to_string(num_warnings));
            print_text(num_errors == 0 ? GREEN : RED, num_errors == 0 ? LOG : ERROR,
                       "Total errors  : " + std::to_string(num_errors));

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
        //  -- Logging --
        /**
         *  Log a standard message.
         *
         *  @param  text    Message text to be logged.
         */
        void Logger::log(const std::string& text) const
        {
            print_text(CYAN, LOG, text);
        }

        /**
         *  Log a verbose message.
         *
         *  @param  text    Message text to be logged.
         */
        void Logger::verb(const std::string& text) const
        {
#ifdef VERBOSE_MESSAGES
            print_text(CYAN, LOG, text);
#endif
        }


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

        /**
         *  Print the given text string in a formatted, coloured message.
         *
         *  @param  col     Colour to print the text in.
         *  @param  type    Type string to be prepended to the message.
         *  @param  text    Text to be printed.
         *
         *  @pre    col must be a valid cols enumeration.
         *  @pre    type must be a valid types enumeration.
         */
        void Logger::print_text(const size_t col, const size_t type, const std::string& text) const
        {
            assert(col < TOTAL_COLS);
            assert(type < TOTAL_TYPES);

            std::vector<std::string> lines     = form_lines(text);
            std::string              timestamp = "[" + utl::create_timestamp() + "]";
            timestamp.resize(TIME_WIDTH, ' ');

            stream << timestamp << text_cols[col] << log_types[type] << lines[0];
            for (size_t i = 1; i < lines.size(); ++i)
            {
                stream << "\n" << padding_string << lines[i];
            }
            stream << text_cols[RESET] << "\n";
        }


        //  -- Formatting --
        /**
         *  Form a given text string into separate formatted lines.
         *
         *  @param  text    Text string to be formatted.
         *
         *  @return Vector of text lines.
         */
        std::vector<std::string> Logger::form_lines(std::string text) const
        {
            text += '\n';

            utl::find_and_replace(text, "\t", "    ");

            std::vector<std::string> lines;
            size_t                   newline_pos;
            while ((newline_pos = text.find_first_of('\n')) != std::string::npos)
            {
                std::string line = text.substr(0, newline_pos);
                text.erase(0, newline_pos + 1);

                if (line.size() <= TEXT_WIDTH)
                {
                    lines.push_back(line);
                }
                else
                {
                    lines.push_back(line.substr(0, static_cast<size_t>(TEXT_WIDTH)));
                    line.erase(0, static_cast<size_t>(TEXT_WIDTH));

                    while (line.size() > (TEXT_WIDTH - WRAP_INDENT))
                    {
                        lines.push_back(indent_string + line.substr(0, static_cast<size_t>(TEXT_WIDTH - WRAP_INDENT)));
                        line.erase(0, static_cast<size_t>(TEXT_WIDTH - WRAP_INDENT));
                    }

                    lines.push_back(indent_string + line.substr(0, static_cast<size_t>(TEXT_WIDTH - WRAP_INDENT)));
                }
            }

            return (lines);
        }



    } // namespace term
} // namespace arc
