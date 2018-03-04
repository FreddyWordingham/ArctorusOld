/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   09/01/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_TERM_LOGGER_HPP
#define ARCTORUS_SRC_CLS_TERM_LOGGER_HPP



//  == INCLUDES ==
//  -- System --
#include <array>
#include <cassert>
#include <chrono>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <vector>

//  -- General --
#include "gen/config.hpp"

//  -- Utility --
#include "utl/array.hpp"
#include "utl/string.hpp"
#include "utl/vector.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace term
    {



        //  == SETTINGS ==
        //  -- Title --
        constexpr const char* TITLE_CARD = R"(                              llrr                              )"
            R"(                             lllrrr                             )"
            R"(                            llllrrrr                            )"
            R"(                      ~~~~~lllllrrrrrMBBGGGYYYYRRRRRRRRRRRRRRRRR)"
            R"(              ~~~~~~~~    lllll  rrrrrMMMMBBBBGGGGGGGYYYYYYYYYYY)"
            R"(      ~~~~~~~~           lllll    rrrrr     MMMMMMMBBBGGGGGGGGGG)"
            R"(~~~~~~                  llll        rrrr          MMMMMMBBBBBBBB)"
            R"(                       lll            rrr               MMMMMMMM)"
            R"(   __     ____    ____   ______   ____    ____   __  __   ____  )"
            R"(  //\\   ||__))  //  ``    ||    //  \\  ||__))  ||  ||  //____ )"
            R"( //--\\  ||  \\  \\__,,    ||    \\__//  ||  \\  \\__//   ___// )";  //! Arctorus title.

        //  -- Type Strings --
        constexpr const char* LOG_TYPE_STRING   = "[       ]";  //! String indicating a standard message.
        constexpr const char* VERB_TYPE_STRING  = "[verbose]";  //! String indicating a verbose message.
        constexpr const char* VAL_TYPE_STRING   = "[ value ]";  //! String indicating a value message.
        constexpr const char* TEMP_TYPE_STRING  = "[ tempo ]";  //! String indicating a temporary message.
        constexpr const char* WARN_TYPE_STRING  = "[warning]";  //! String indicating a warning message.
        constexpr const char* ERROR_TYPE_STRING = "[!ERROR!]";  //! String indicating an error message.

        //  -- Formatting --
        constexpr const int LINE_WIDTH       = 128;                                     //! Total width of a single line.
        constexpr const int TITLE_WIDTH      = 64;                                      //! Total width of the title.
        constexpr const int TIME_WIDTH       = 22;                                      //! Space allocated to the time buffer.
        constexpr const int TYPE_WIDTH       = 10;                                      //! Space allocated to the type buffer.
        constexpr const int MIN_TEXT_WIDTH   = 64;                                      //! Minimum guaranteed text width.
        constexpr const int TEXT_WIDTH       = LINE_WIDTH - (TIME_WIDTH + TYPE_WIDTH);  //! Width allocated to the text buffer.
        constexpr const int WRAP_INDENT      = 2;                                       //! Indentation width of wrapped lines.
        constexpr const int VALUE_NAME_WIDTH = 16;                                      //! Space allocated to the value name.

        //  -- Updating --
        constexpr const double MIN_UPDATE_DELAY = 1.0;  //! Minimum delay between temporary logs.



        //  == ASSERTIONS ==
        //  -- Validation --
        static_assert(TITLE_WIDTH <= LINE_WIDTH);
        static_assert((TIME_WIDTH + TYPE_WIDTH + TEXT_WIDTH) == LINE_WIDTH);
        static_assert(TEXT_WIDTH >= MIN_TEXT_WIDTH);
        static_assert(MIN_TEXT_WIDTH > WRAP_INDENT);
        static_assert(VALUE_NAME_WIDTH < TEXT_WIDTH);
        static_assert(TEXT_WIDTH > (VALUE_NAME_WIDTH - 3));



        //  == CLASS ==
        /**
         *  Terminal logger class which allows formatted printing of message logs.
         *  Messages are printed to the terminal by default.
         *  Coloured printing is enabled when cout is not being piped to a file.
         *  Should be used as a singleton class via the get_instance method.
         */
        class Logger
        {
            //  == ENUMERATIONS ==
          private:
            //  -- Colours --
            /**
             *  Enumeration of text colours available.
             */
            enum cols
            {
                RESET,      //! Reset text colouring.
                BLACK,      //! Black text colouring.
                RED,        //! Red text colouring.
                GREEN,      //! Green text colouring.
                YELLOW,     //! Yellow text colouring.
                BLUE,       //! Blue text colouring.
                MAGENTA,    //! Magenta text colouring.
                CYAN,       //! Cyan text colouring.
                WHITE,      //! White text colouring.
                TOTAL_COLS  //! Total number of text colours.
            };

            //  -- Log Types --
            /**
             *  Enumeration of the log types available.
             */
            enum types
            {
                LOG,        //! Standard log message.
                VERB,       //! Verbose log message.
                VAL,        //! Value log message.
                TEMP,       //! Temporary log message.
                WARN,       //! Warning log message.
                ERROR,      //! Error log message.
                TOTAL_TYPES //! Total number of log types.
            };


            //  == FIELDS ==
          private:
            //  -- Output Stream --
            const std::mutex m_stream_mutex;    //! Protects writes to the stream.
            std::ostream& m_stream;             //! Output stream to write to.

            //  -- Colouring --
            const std::array<std::string, TOTAL_COLS> m_text_col;   //! Array of colour escape strings.

            //  -- Type Strings --
            const std::array<std::string, TOTAL_TYPES> m_log_type;  //! Array of log type strings.

            //  -- Format Strings --
            const std::string m_indent_string;  //! Indentation string.
            const std::string m_padding_string; //! Padding string.

            //  -- Counters --
            int m_num_warnings; //! Count of the total number of reported warnings.
            int m_num_errors;   //! Count of the total number of reported errors.


            //  == INSTANTIATION ==
          public:
            //  -- Singleton --
            static Logger& get_instance(std::ostream& t_stream = std::cout);

          public:
            //  -- Constructors --
            Logger(const Logger& /*unused*/) = delete;
            Logger(const Logger&& /*unused*/) = delete;

          private:
            //  -- Constructors --
            explicit Logger(std::ostream& t_stream);

            //  -- Destructors --
            ~Logger();

            //  -- Initialisation --
            std::array<std::string, TOTAL_COLS> init_text_col() const;
            std::array<std::string, TOTAL_TYPES> init_log_type() const;


            //  == OPERATORS ==
          public:
            //  -- Copy --
            Logger& operator=(const Logger& /*unused*/) = delete;
            Logger& operator=(const Logger&& /*unused*/) = delete;


            //  == METHODS ==
          public:
            //  -- Logging --
            void log(const std::string& t_text) const;
            void sec(const std::string& t_text) const;
            void verb(const std::string& t_text) const;
            template <typename T>
            void val(const std::string& t_name, const T& t_val) const;
            template <typename T>
            void temp(const std::string& t_name, const T& t_val) const;
            void warn(const std::string& t_symptom, const std::string& t_cause);
            [[noreturn]] void error(const std::string& t_file, const std::string& t_line, const std::string& t_symptom,
                                    const std::string& t_cause);

          private:
            //  -- Printing --
            void print_hr(char t_hr_char = '-') const;
            void print_title_card() const;
            void print_text(size_t t_col, size_t t_type, const std::string& t_text) const;

            //  -- Formatting --
            std::vector<std::string> form_lines(std::string t_text) const;
        };



        //  == METHODS ==
        //  -- Logging --
        /**
         *  Log a name-value pair message.
         *
         *  @tparam T   Type of value to be printed.
         *
         *  @param  t_name  Name of the value.
         *  @param  t_val   Value of the value.
         *
         *  @pre    name must not be empty.
         */
        template <typename T>
        void Logger::val(const std::string& t_name, const T& t_val) const
        {
            assert(!t_name.empty());

            // Resize the name to the set length and add colon string.
            std::string text = t_name;
            text.resize(VALUE_NAME_WIDTH, ' ');
            text += " : ";

            // Add value to the stream.
            std::stringstream val_stream;
            val_stream << std::boolalpha << t_val;
            text += val_stream.str();

            // Print the value.
            print_text(MAGENTA, VAL, text);
        }

        /**
         *  Log a temporary name-value pair which will be overwritten by the next log.
         *  Log will only be written if within to cout and not being redirected to a file.
         *
         *  @tparam T   Type of value to be printed.
         *
         *  @param  t_name  Name of the value.
         *  @param  t_val   Value of the value.
         *
         *  @pre    name must not be empty.
         */
        template <typename T>
        void Logger::temp(const std::string& t_name, const T& t_val) const
        {
            assert(!t_name.empty());

            // If printing to a
            static const bool s_term                              = (&m_stream == &std::cout) && (isatty(fileno(stdout)) != 0);
            if (!s_term)
            {
                return;
            }

            // Return if minimum update time has not yet passed.
            static std::chrono::steady_clock::time_point last_update;
            const std::chrono::steady_clock::time_point  cur_time = std::chrono::steady_clock::now();
            if (std::chrono::duration_cast<std::chrono::duration<double>>(cur_time - last_update).count() < MIN_UPDATE_DELAY)
            {
                return;
            }
            last_update = cur_time;

            // Resize the name to the set length and add colon string.
            std::string text = t_name;
            text.resize(VALUE_NAME_WIDTH, ' ');
            text += " : ";

            // Store the value as a string and resize it to the set length.
            std::stringstream val_stream;
            val_stream << std::boolalpha << t_val;
            text += val_stream.str();
            text.resize(static_cast<size_t>(TEXT_WIDTH), ' ');

            // Create the timestamp.
            std::string timestamp = "[" + utl::create_timestamp() + "]";
            timestamp.resize(TIME_WIDTH, ' ');

            // Print the temporary message.
            m_mutex_stream
            m_stream << timestamp << m_text_col[YELLOW] << m_log_type[TEMP] << text << m_text_col[RESET] << "\r";
        }



    } // namespace term
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_TERM_LOGGER_HPP
