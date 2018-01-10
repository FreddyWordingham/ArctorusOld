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

#define VAL(x)                                  \
{                                               \
    term::Logger::get_instance().val(#x, x);    \
}                                               \




//  == GUARD END ==
#endif // ARCTORUS_SRC_GEN_LOG_HPP
