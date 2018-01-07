/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   07/01/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_RES_SRC_GEN_CONFIG_HPP_IN
#define ARCTORUS_RES_SRC_GEN_CONFIG_HPP_IN



//  == NAMESPACE ==
namespace arc
{



    //  == SETTINGS ==
    //  -- Build Info --
    constexpr const char* ARCTORUS_DIR = "@ARCTORUS_DIR@/";     //! Arctorus directory path.
    constexpr const char* BUILD_INFO   = "@BUILD_BRANCH@-@BUILD_HASH@-@BUILD_PATCH@"
        " : @BUILD_COMPILER@ : @BUILD_TYPE@ : @BUILD_DATE@";    //! Arctorus build information.



} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_RES_SRC_GEN_CONFIG_HPP_IN
