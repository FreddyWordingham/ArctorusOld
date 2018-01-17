/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   17/01/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_GEN_FILE_HPP
#define ARCTORUS_SRC_GEN_FILE_HPP



//  == INCLUDES ==
//  -- System --



//  == NAMESPACE ==
namespace arc
{
    namespace file
    {



        //  == SETTINGS ==
        //  -- Warnings --
        constexpr const int SIZE_WARNING = 10;  //! [bytes] Warning triggered when opening files larger than this size.

        //  -- Formatting --
        constexpr const char COMMENT_CHAR = '#';    //! Character used to comment file lines.
        constexpr const char DELIMIT_CHAR = ',';    //! Character used to delimit file data.
        constexpr const int  PRINT_WIDTH  = 16;     //! Space allocated to each data print.



    } // namespace file
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_GEN_FILE_HPP
