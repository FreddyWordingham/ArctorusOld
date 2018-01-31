/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   28/01/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_GEOM_TRIANGLE_HPP
#define ARCTORUS_SRC_CLS_GEOM_TRIANGLE_HPP



//  == INCLUDES ==
//  -- Classes --
#include "cls/geom/vertex.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace geom
    {



        //  == CLASS ==
        /**
         *  Triangle class used to form triangular meshes.
         */
        class Triangle
        {
            //  == FIELDS ==
          private:
            //  -- Vertices --
            const std::array<Vertex, 3> m_vert; //! Vertices of the triangle.

            //  -- Properties --
            const double m_area;    //! Area of the triangle.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            explicit Triangle(const std::array<Vertex, 3>& t_vert);


            //  == METHODS ==
          public:
            //  -- Getters --
            inline const Vertex& get_vert(size_t t_index) const;
            double get_area() const { return (m_area); }
        };



        //  == METHODS ==
        //  -- Getters --
        /**
         *  Retrieve a const reference to a vertex of the triangle,
         *
         *  @param  t_index Index of the vertex to retrieve.
         *
         *  @return A const reference to a vertex of the triangle.
         */
        inline const Vertex& Triangle::get_vert(const size_t t_index) const
        {
            assert(t_index < m_vert.size());

            return (m_vert[t_index]);
        }



    } // namespace geom
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GEOM_TRIANGLE_HPP
