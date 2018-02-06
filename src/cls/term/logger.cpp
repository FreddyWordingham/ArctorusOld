/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   09/01/2018.
 */



//  == HEADER ==
#include "cls/term/logger.hpp"



//  == INCLUDES ==
//  -- General --
#include <gen/ansi.hpp>



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
         *  @param  t_stream    Output stream to write the log to.
         *
         *  @return A reference to the initialised logger object.
         */
        Logger& Logger::get_instance(std::ostream& t_stream)
        {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wexit-time-destructors"
            static Logger s_log(t_stream);
#pragma clang diagnostic pop

            return (s_log);
        }


        //  -- Constructors --
        /**
         *  Construct a logger object which will write to a given stream.
         *
         *  @param  t_stream    Output stream to write the log to.
         */
        Logger::Logger(std::ostream& t_stream) :
            m_stream(t_stream),
            m_text_col(init_text_col()),
            m_log_type(init_log_type()),
            m_indent_string(WRAP_INDENT, ' '),
            m_padding_string(TIME_WIDTH + TYPE_WIDTH, ' '),
            m_num_warnings(0),
            m_num_errors(0)
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
            // Print leading horizontal rule.
            print_hr('=');

            // Print number of reported warnings and errors.
            print_text(m_num_warnings == 0 ? GREEN : YELLOW, m_num_warnings == 0 ? LOG : WARN,
                       "Total warnings: " + std::to_string(m_num_warnings));
            print_text(m_num_errors == 0 ? GREEN : RED, m_num_errors == 0 ? LOG : ERROR,
                       "Total errors  : " + std::to_string(m_num_errors));

            // Print trailing horizontal rule.
            print_hr('=');
        }


        //  -- Initialisation --
        /**
         *  Initialise the array of colour escape strings.
         *  Colouring is enabled whilst writing to cout and not being redirected to a file.
         *
         *  @return The array of initialised colour escape codes.
         */
        std::array<std::string, Logger::TOTAL_COLS> Logger::init_text_col() const
        {
            // Create return array of text colour ansi escape codes.
            std::array<std::string, TOTAL_COLS> r_text_col;

            // If not printing to a terminal, or the terminal is being piped to a file, do not initialise the ansi codes.
            if (config::COLOUR_LOG && (&m_stream == &std::cout) && (isatty(fileno(stdout)) != 0))
            {
                r_text_col[RESET]   = ansi::RESET;
                r_text_col[BLACK]   = ansi::BLACK;
                r_text_col[RED]     = ansi::RED;
                r_text_col[GREEN]   = ansi::GREEN;
                r_text_col[YELLOW]  = ansi::YELLOW;
                r_text_col[BLUE]    = ansi::BLUE;
                r_text_col[MAGENTA] = ansi::MAGENTA;
                r_text_col[CYAN]    = ansi::CYAN;
                r_text_col[WHITE]   = ansi::WHITE;
            }

            return (r_text_col);
        }

        /**
         *  Initialise the array of log type string identifiers.
         *
         *  @return The array of initialised log type string identifiers.
         */
        std::array<std::string, Logger::TOTAL_TYPES> Logger::init_log_type() const
        {
            // Create return array of log type strings.
            std::array<std::string, TOTAL_TYPES> r_log_type;

            // Initialise the log strings using the settings.
            r_log_type[LOG]   = std::string(LOG_TYPE_STRING);
            r_log_type[VERB]  = std::string(VERB_TYPE_STRING);
            r_log_type[VAL]   = std::string(VAL_TYPE_STRING);
            r_log_type[TEMP]  = std::string(TEMP_TYPE_STRING);
            r_log_type[WARN]  = std::string(WARN_TYPE_STRING);
            r_log_type[ERROR] = std::string(ERROR_TYPE_STRING);

            // Resize the strings to the set width.
            for (size_t i = 0; i < TOTAL_TYPES; ++i)
            {
                r_log_type[i].resize(TYPE_WIDTH, ' ');
            }

            return (r_log_type);
        }



        //  == METHODS ==
        //  -- Logging --
        /**
         *  Log a standard message.
         *
         *  @param  t_text  Message text to be logged.
         */
        void Logger::log(const std::string& t_text) const
        {
            print_text(CYAN, LOG, t_text);
        }

        /**
         *  Log a verbose message.
         *
         *  @param  t_text  Message text to be logged.
         */
        void Logger::verb(const std::string& t_text) const
        {
            // If verbose message printing is enabled print the message.
            if (config::VERBOSE_LOG)
            {
                print_text(CYAN, LOG, t_text);
            }
        }

        /**
         *  Log a warning message.
         *  Increment the number of recorded warnings.
         *
         *  @param  t_symptom   Description of the symptom of the warning.
         *  @param  t_cause     Description of the cause of the warning.
         *
         *  @pre    t_symptom must not be empty.
         *  @pre    t_cause must not be empty.
         */
        void Logger::warn(const std::string& t_symptom, const std::string& t_cause)
        {
            assert(!t_symptom.empty());
            assert(!t_cause.empty());

            // Increment the number of recorded warnings.
            ++m_num_warnings;

            // Create the text string.
            std::string text = t_symptom + "\n" + t_cause;
            print_text(YELLOW, WARN, text);
        }

        /**
         *  Log an error message.
         *  Increment the number of recorded errors.
         *  Program will then exit.
         *
         *  @param  t_file      File path where the error occurred.
         *  @param  t_line      Line where the error occurred.
         *  @param  t_symptom   Description of the symptom of the error.
         *  @param  t_cause     Description of the cause of the error.
         *
         *  @pre    t_file must not be empty.
         *  @pre    t_line must not be empty.
         *  @pre    t_symptom must not be empty.
         *  @pre    t_cause must not be empty.
         */
        void Logger::error(const std::string& t_file, const std::string& t_line, const std::string& t_symptom,
                           const std::string& t_cause)
        {
            assert(!t_file.empty());
            assert(!t_line.empty());
            assert(!t_symptom.empty());
            assert(!t_cause.empty());

            // Increment the number of recorded errors.
            ++m_num_errors;

            // Create the text string.
            std::string text = "File: " + t_file + "\nLine: " + t_line + "\n" + t_symptom + "\n" + t_cause;
            print_text(RED, ERROR, text);

            // Exit the program with an error signal.
            std::exit(1);
        }


        //  -- Printing --
        /**
         *  Print a horizontal rule using a given character.
         *
         *  @param  t_hr_char   Character used to draw the horizontal rule.
         */
        void Logger::print_hr(const char t_hr_char) const
        {
            m_stream << std::string(LINE_WIDTH, t_hr_char) << "\n";
        }

        /**
         *  Print the Arctorus title card.
         */
        void Logger::print_title_card() const
        {
            // Print leading horizontal rule.
            print_hr('=');

            // Get title card string and determine the amount of padding required.
            std::string       title = TITLE_CARD;
            const std::string pre_title_pad((LINE_WIDTH - TITLE_WIDTH) / 2, ' ');
            const std::string post_title_pad(LINE_WIDTH - (TITLE_WIDTH + pre_title_pad.size()), ' ');

            // Loop until all lines of the title card have been printed.
            while (!title.empty())
            {
                // Take a line of the title string.
                std::string line = title.substr(0, TITLE_WIDTH);
                title.erase(0, TITLE_WIDTH);

                // Colour and format the printing line string.
                utl::find_and_replace(&line, "l", m_text_col[CYAN] + "/" + m_text_col[RESET]);
                utl::find_and_replace(&line, "r", m_text_col[CYAN] + R"(\)" + m_text_col[RESET]);
                utl::find_and_replace(&line, "M", m_text_col[MAGENTA] + "~" + m_text_col[RESET]);
                utl::find_and_replace(&line, "B", m_text_col[BLUE] + "~" + m_text_col[RESET]);
                utl::find_and_replace(&line, "G", m_text_col[GREEN] + "~" + m_text_col[RESET]);
                utl::find_and_replace(&line, "Y", m_text_col[YELLOW] + "~" + m_text_col[RESET]);
                utl::find_and_replace(&line, "R", m_text_col[RED] + "~" + m_text_col[RESET]);

                // Print the line with padding either side.
                m_stream << pre_title_pad << line << post_title_pad << "\n";
            }

            // Print middle horizontal rule.
            print_hr('=');

            // Form the build information string.
            std::string       build = config::BUILD_INFO;
            const std::string pre_build_pad((LINE_WIDTH - build.size()) / 2, ' ');
            const std::string post_build_pad(LINE_WIDTH - (build.size() + pre_build_pad.size()), ' ');

            // Print the build information string.
            m_stream << pre_build_pad << build << post_build_pad << "\n";

            // Print trailing horizontal rule.
            print_hr('=');
        }

        /**
         *  Print the given text string in a formatted, coloured message.
         *
         *  @param  t_col   Colour to print the text in.
         *  @param  t_type  Type string to be prepended to the message.
         *  @param  t_text  Text to be printed.
         *
         *  @pre    t_col must be a valid cols enumeration.
         *  @pre    t_type must be a valid types enumeration.
         */
        void Logger::print_text(const size_t t_col, const size_t t_type, const std::string& t_text) const
        {
            assert(t_col < TOTAL_COLS);
            assert(t_type < TOTAL_TYPES);

            // Form the text into lines.
            std::vector<std::string> lines     = form_lines(t_text);

            // Create the timestamp string.
            std::string              timestamp = "[" + utl::create_timestamp() + "]";
            timestamp.resize(TIME_WIDTH, ' ');

            // Print the lines.
            m_stream << timestamp << m_text_col[t_col] << m_log_type[t_type] << lines[0];
            for (size_t i = 1; i < lines.size(); ++i)
            {
                m_stream << "\n" << m_padding_string << lines[i];
            }
            m_stream << m_text_col[RESET] << "\n";
        }


        //  -- Formatting --
        /**
         *  Form a given text string into separate formatted lines.
         *
         *  @param  t_text  Text string to be formatted.
         *
         *  @return Vector of text lines.
         */
        std::vector<std::string> Logger::form_lines(std::string t_text) const
        {
            t_text += '\n';

            utl::find_and_replace(&t_text, "\t", "    ");

            std::vector<std::string> r_line;
            size_t                   newline_pos;
            while ((newline_pos = t_text.find_first_of('\n')) != std::string::npos)
            {
                std::string line = t_text.substr(0, newline_pos);
                t_text.erase(0, newline_pos + 1);

                if (line.size() <= TEXT_WIDTH)
                {
                    r_line.push_back(line);
                }
                else
                {
                    r_line.push_back(line.substr(0, static_cast<size_t>(TEXT_WIDTH)));
                    line.erase(0, static_cast<size_t>(TEXT_WIDTH));

                    while (line.size() > (TEXT_WIDTH - WRAP_INDENT))
                    {
                        r_line.push_back(m_indent_string + line.substr(0, static_cast<size_t>(TEXT_WIDTH - WRAP_INDENT)));
                        line.erase(0, static_cast<size_t>(TEXT_WIDTH - WRAP_INDENT));
                    }

                    r_line.push_back(m_indent_string + line.substr(0, static_cast<size_t>(TEXT_WIDTH - WRAP_INDENT)));
                }
            }

            return (r_line);
        }



    } // namespace term
} // namespace arc
