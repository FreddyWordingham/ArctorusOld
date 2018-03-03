/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   10/01/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_GEN_LOG_HPP
#define ARCTORUS_SRC_GEN_LOG_HPP



//  == INCLUDES ==
//  -- System --
#include <sstream>

//  -- Classes --
#include "cls/term/logger.hpp"



//  == MACROS ==
//  -- Logging --
/**
 *  Macro used to log a standard message.
 *
 *  @param  t_text  Message text to be logged.
 */
#define LOG(t_text)                                             \
{                                                               \
    std::stringstream text_stream;                              \
    text_stream << std::boolalpha << t_text;                    \
    arc::term::Logger::get_instance().log(text_stream.str());   \
}

/**
 *  Macro used to log a section message.
 *
 *  @param  t_text  Text of the section.
 */
#define SEC(t_text)                                             \
{                                                               \
    std::stringstream text_stream;                              \
    text_stream << std::boolalpha << t_text;                    \
    arc::term::Logger::get_instance().sec(text_stream.str());   \
}                                                               \

/**
 *  Macro used to log a verbose message.
 *
 *  @param  t_text  Message text to be logged.
 */
#define VERB(t_text)                                            \
{                                                               \
    std::stringstream text_stream;                              \
    text_stream << std::boolalpha << t_text;                    \
    arc::term::Logger::get_instance().log(text_stream.str());   \
}                                                               \

/**
 *  Macro used to log a name-value pair message.
 *
 *  @param  t_x Value to be named and logged.
 */
#define VAL(t_x)                                        \
{                                                       \
    arc::term::Logger::get_instance().val(#t_x, t_x);   \
}                                                       \

/**
 *  Macro used to log a temporary string-value pair message.
 *
 *  @param  t_str   String to be logged.
 *  @param  t_val   Value to be logged.
 */
#define TEMP(t_str, t_val)                                  \
{                                                           \
    arc::term::Logger::get_instance().temp(t_str, t_val);   \
}                                                           \

/**
 *  Macro used to log a warning message.
 *
 *  @param  t_symptom   Text describing the symptom of the warning.
 *  @param  t_cause     Text describing the cause of the warning.
 */
#define WARN(t_symptom, t_cause)                                                        \
{                                                                                       \
    std::stringstream symptom_stream, cause_stream;                                     \
    symptom_stream << std::boolalpha << t_symptom;                                      \
    cause_stream << std::boolalpha << t_cause;                                          \
    arc::term::Logger::get_instance().warn(symptom_stream.str(), cause_stream.str());   \
}                                                                                       \

/**
 *  Macro used to log an error message.
 *
 *  @param  t_symptom   Text describing the symptom of the error.
 *  @param  t_cause     Text describing the cause of the error.
 */
#define ERROR(t_symptom, t_cause)                                                                                           \
{                                                                                                                           \
    std::stringstream symptom_stream, cause_stream;                                                                         \
    symptom_stream << std::boolalpha << t_symptom;                                                                          \
    cause_stream << std::boolalpha << t_cause;                                                                              \
    arc::term::Logger::get_instance().error(__FILE__, std::to_string(__LINE__), symptom_stream.str(), cause_stream.str());  \
}                                                                                                                           \



//  == GUARD END ==
#endif // ARCTORUS_SRC_GEN_LOG_HPP
