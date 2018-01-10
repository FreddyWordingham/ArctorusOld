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
#include <iostream>
#include <array>
#include <sstream>
#include <vector>

//  -- General --
#include "gen/config.hpp"



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
                WARN,       //! Warning log message.
                ERROR,      //! Error log message.
                TOTAL_TYPES //! Total number of log types.
            };


            //  == FIELDS ==
          private:
            //  -- Output Stream --
            std::ostream& stream;   //! Output stream to write to.

            //  -- Colouring --
            const std::array<std::string, TOTAL_COLS> text_cols;    //! Array of colour escape strings.

            //  -- Type Strings --
            const std::array<std::string, TOTAL_TYPES> log_types;   //! Array of log type strings.

            //  -- Format Strings --
            const std::string indent_string;    //! Indentation string.
            const std::string padding_string;   //! Padding string.

            //  -- Counters --
            int num_warnings;   //! Count of the total number of reported warnings.
            int num_errors;     //! Count of the total number of reported errors.


            //  == INSTANTIATION ==
          public:
            //  -- Singleton --
            static Logger& get_instance(std::ostream& init_stream = std::cout);

          private:
            //  -- Constructors --
            explicit Logger(std::ostream& init_stream);

            //  -- Destructors --
            ~Logger();

            //  -- Initialisation --
            std::array<std::string, TOTAL_COLS> init_text_cols() const;
            std::array<std::string, TOTAL_TYPES> init_log_types() const;


            //  == METHODS ==
          public:
            //  -- Logging --
            void log(const std::string& text) const;
            void verb(const std::string& text) const;
            template <typename T>
            void val(const std::string& name, const T& val) const;
            void warn(const std::string& symptom, const std::string& cause);
            [[noreturn]] void error(const std::string& file, const std::string& line, const std::string& symptom,
                                    const std::string& cause);

          private:
            //  -- Printing --
            void print_hr(char hr_char = '-') const;
            void print_title_card() const;
            void print_text(size_t col, size_t type, const std::string& text) const;

            //  -- Formatting --
            std::vector<std::string> form_lines(std::string text) const;
        };



        //  == METHODS ==
        //  -- Logging --
        /**
         *  Log a name-value pair message.
         *
         *  @tparam T   Type of value to be printed.
         *
         *  @param  name    Name of the value.
         *  @param  val     Value of the value.
         */
        template <typename T>
        void Logger::val(const std::string& name, const T& val) const
        {
            std::string text = name;
            text.resize(VALUE_NAME_WIDTH, ' ');
            text += " : ";

            std::stringstream val_stream;
            val_stream << std::boolalpha << val;
            text += val_stream.str();

            print_text(MAGENTA, VAL, text);
        }



    } // namespace term
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_TERM_LOGGER_HPP
