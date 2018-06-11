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
#define ENABLE_LOG_COLOUR
#define ENABLE_LOG_VERBOSE
#define ENABLE_GRAPHICS
#define ENABLE_PHOTON_PATHS



//  == NAMESPACE ==
namespace arc
{
    namespace config
    {



        //  == SETTINGS ==
        //  -- Build Info --
        constexpr const char* ARCTORUS_DIR = "/Users/lm579/Arctorus/";     //! Arctorus directory path.
        constexpr const char* BUILD_INFO   = "raman_mat_benchmark-7785381e-2730"
            " : Clang : debug : 2018-04-19";    //! Arctorus build information.



    } // namespace config
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_RES_SRC_GEN_CONFIG_HPP_IN

