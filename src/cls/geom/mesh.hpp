/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   28/01/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_GEOM_MESH_HPP
#define ARCTORUS_SRC_CLS_GEOM_MESH_HPP



//  == INCLUDES ==
//  -- System --



//  == NAMESPACE ==
namespace arc
{
    namespace geom
    {



        //  == CLASS ==
        /**
         *  Triangular mesh class used to form the boundary of objects.
         */
        class Mesh
        {
            //  == FIELDS ==
          private:
            //  -- Properties --
            const size_t m_num_verts;   //! Number of vertex positions.
            const size_t m_num_norms;   //! Number of vertex normals.
            const size_t m_num_tris;    //! Number of triangle faces.

            //  -- Triangle Data --
            const std::vector <geom::Triangle> m_tri;    //! List of triangles forming the mesh.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --

          private:
            //  -- Initialisation --


            //  == OPERATORS ==
          private:


            //  == METHODS ==
          private:
        };



    } // namespace geom
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GEOM_MESH_HPP
