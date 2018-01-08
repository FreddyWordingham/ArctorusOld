/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   08/01/2018.
 */


//  == GUARD ==
#ifndef ARCTORUS_SRC_UTL_VECTOR_HPP
#define ARCTORUS_SRC_UTL_VECTOR_HPP



//  == INCLUDES ==
//  -- System --
#include <vector>



//  == NAMESPACE ==
namespace arc
{
    namespace utl
    {



        //  == FUNCTION PROTOTYPES ==



    } // namespace utl



    //  == OPERATORS PROTOTYPES ==
    //  -- Printing --
    template <typename T>
    std::ostream& operator<<(std::ostream& stream, const std::vector<T>& vec);



    //  == OPERATORS ==
    //  -- Printing --
    /**
     *  Enable writing of a vector to a given ostream.
     *
     *  @tparam T   Type stored by the vector.
     *
     *  @param  stream  Stream to write to.
     *  @param  vec     Vector to be written.
     *
     *  @return A reference to the stream post-write.
     */
    template <typename T>
    std::ostream& operator<<(std::ostream& stream, const std::vector<T>& vec)
    {
        if (vec.empty())
        {
            stream << "[]";

            return (stream);
        }

        stream << "[" << vec[0];
        for (size_t i = 1; i < vec.size(); ++i)
        {
            stream << ", " << vec[i];
        }
        stream << "]";

        return (stream);
    }



} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_UTL_VECTOR_HPP
