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
 *  @param  text    Message text to be logged.
 */
#define LOG(text)                                           \
{                                                           \
    std::stringstream text_stream;                          \
    text_stream << std::boolalpha << text;                  \
    term::Logger::get_instance().log(text_stream.str());    \
}                                                           \

/**
 *  Macro used to log a verbose message.
 *
 *  @param  text    Message text to be logged.
 */
#define VERB(text)                                          \
{                                                           \
    std::stringstream text_stream;                          \
    text_stream << std::boolalpha << text;                  \
    term::Logger::get_instance().log(text_stream.str());    \
}                                                           \

/**
 *  Macro used to log a name-value pair message.
 *
 *  @param  x   Value to be named and logged.
 */
#define VAL(x)                                  \
{                                               \
    term::Logger::get_instance().val(#x, x);    \
}                                               \

/**
 *  Macro used to log a warning message.
 *
 *  @param  symptom Text describing the symptom of the warning.
 *  @param  cause   Text describing the cause of the warning.
 */
#define WARN(symptom, cause)                                                        \
{                                                                                   \
    std::stringstream symptom_stream, cause_stream;                                 \
    symptom_stream << std::boolalpha << symptom;                                    \
    cause_stream << std::boolalpha << cause;                                        \
    term::Logger::get_instance().warn(symptom_stream.str(), cause_stream.str());    \
}                                                                                   \

/**
 *  Macro used to log an error message.
 *
 *  @param  symptom Text describing the symptom of the error.
 *  @param  cause   Text describing the cause of the error.
 */
#define ERROR(symptom, cause)                                                                                           \
{                                                                                                                       \
    std::stringstream symptom_stream, cause_stream;                                                                     \
    symptom_stream << std::boolalpha << symptom;                                                                        \
    cause_stream << std::boolalpha << cause;                                                                            \
    term::Logger::get_instance().error(__FILE__, std::to_string(__LINE__), symptom_stream.str(), cause_stream.str());   \
}                                                                                                                       \



//  == GUARD END ==
#endif // ARCTORUS_SRC_GEN_LOG_HPP
