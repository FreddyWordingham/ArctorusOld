/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   08/01/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_GEN_ENUM_HPP
#define ARCTORUS_SRC_GEN_ENUM_HPP



//  == NAMESPACE ==
namespace arc
{



    //  == ENUMERATIONS ==
    //  -- Dimensions --
    /**
     *  Enumeration of the cartesian dimensions.
     *  Used for index consistency.
     */
    enum cartesian
    {
        X,  //! X spatial dimension.
        Y,  //! Y spatial dimension.
        Z   //! Z spatial dimension.
    };


    //  -- Colours --
    /**
     *  Enumeration of the colour channels.
     *  Used for index consistency.
     */
    enum colours
    {
        R,  //! Red colour channel.
        G,  //! Green colour channel.
        B,  //! Blue colour channel.
        A   //! Transparency colour channel.
    };



} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_GEN_ENUM_HPP
