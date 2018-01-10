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
#include <ostream>

//  -- Classes --
#include "cls/term/logger.hpp"



//  == MACROS ==
//  -- Logging --

#define LOG(text)                                           \
{                                                           \
    std::stringstream text_stream;                          \
    text_stream << std::boolalpha << (text);                \
    term::Logger::get_instance().log(text_stream.str());    \
}                                                           \



//  == GUARD END ==
#endif // ARCTORUS_SRC_GEN_LOG_HPP
