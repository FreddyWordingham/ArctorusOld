/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   28/01/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_UTL_STREAM_HPP
#define ARCTORUS_SRC_UTL_STREAM_HPP



//  == INCLUDES ==
//  -- System --



//  == NAMESPACE ==
namespace arc
{
    namespace utl
    {



        //  == FUNCTION PROTOTYPES ==
        //  -- Manipulation --
        template <typename T>
        inline void rewind(T& t_stream);



        //  == FUNCTIONS ==
        //  -- Manipulation --
        /**
         *  Rewind a given stream.
         *  Clear the state of the stream.
         *  Place the get an put pointers to the start of the stream.
         *
         *  @tparam T   Type of stream to be rewound.
         *
         *  @param  t_stream    Stream to be rewound.
         */
        template <typename T>
        inline void rewind(T& t_stream)
        {
            t_stream.clear();
            t_stream.seekg(0);
            t_stream.seekp(0);
        }



    } // namespace utl
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_UTL_STREAM_HPP
