/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   09/01/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_GEN_ANSI_HPP
#define ARCTORUS_SRC_GEN_ANSI_HPP



//  == NAMESPACE ==
namespace arc
{
    namespace ansi
    {



        //  == SETTINGS ==
        //  -- Ansi Colour Codes --
        constexpr const char* RESET   = "\033[0;0m";    //! Ansi reset text colour escape string.
        constexpr const char* BLACK   = "\033[0;30m";   //! Ansi black text colour escape string.
        constexpr const char* RED     = "\033[0;31m";   //! Ansi red text colour escape string.
        constexpr const char* GREEN   = "\033[0;32m";   //! Ansi green text colour escape string.
        constexpr const char* YELLOW  = "\033[0;33m";   //! Ansi yellow text colour escape string.
        constexpr const char* BLUE    = "\033[0;34m";   //! Ansi blue text colour escape string.
        constexpr const char* MAGENTA = "\033[0;35m";   //! Ansi magenta text colour escape string.
        constexpr const char* CYAN    = "\033[0;36m";   //! Ansi cyan text colour escape string.
        constexpr const char* WHITE   = "\033[0;37m";   //! Ansi white text colour escape string.



    } // namespace ansi
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_GEN_ANSI_HPP
