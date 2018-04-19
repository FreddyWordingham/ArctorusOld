/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   07/01/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_RES_SRC_GEN_CONFIG_HPP_IN
#define ARCTORUS_RES_SRC_GEN_CONFIG_HPP_IN



//  == OPTIONS ==
//  -- Compile-Time --
// Coloured log is disabled.
// Verbose log is disabled.
// Graphics are disabled.
// Photon paths are disabled.

#define ENABLE_GRAPHICS
#define ENABLE_LOG_COLOUR
#define ENABLE_LOG_VERBOSE
#define ENABLE_PHOTON_PATHS



//  == NAMESPACE ==
namespace arc
{
    namespace config
    {



        //  == SETTINGS ==
        //  -- Build Info --
        constexpr const char* ARCTORUS_DIR = "/Users/lm579/Arctorus/";     //! Arctorus directory path.
        constexpr const char* BUILD_INFO   = "Raman-14462807-2729"
            " : Clang : release : 2018-04-05";    //! Arctorus build information.



    } // namespace config
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_RES_SRC_GEN_CONFIG_HPP_IN
