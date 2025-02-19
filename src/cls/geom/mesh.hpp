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
#include <vector>

//  -- Classes --
#include "cls/geom/triangle.hpp"
#include "cls/math/vec.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace geom
    {



        //  == SETTINGS ==
        //  -- Wavefront Keywords --
        constexpr const char* POS_KEYWORD  = "v";   //! Wavefront file keyword identifying vertex positions.
        constexpr const char* NORM_KEYWORD = "vn";  //! Wavefront file keyword identifying vertex normals.
        constexpr const char* FACE_KEYWORD = "f";   //! Wavefront file keyword identifying a face.



        //  == CLASS ==
        /**
         *  Triangular mesh class used to form the boundary of objects.
         */
        class Mesh
        {
            //  == FIELDS ==
          private:
            //  -- Properties --
            const size_t m_num_vert;    //! Number of vertex positions.
            const size_t m_num_norm;    //! Number of vertex normals.
            const size_t m_num_tri;     //! Number of triangle faces.

            //  -- Triangle Data --
            const std::vector<geom::Triangle> m_tri;  //! List of triangles forming the mesh.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            explicit Mesh(const std::string& t_serial, const math::Vec<3>& t_trans = math::Vec<3>(0.0, 0.0, 0.0),
                          const math::Vec<3>& t_dir = math::Vec<3>(0.0, 0.0, 1.0), double t_spin = 0.0,
                          const math::Vec<3>& t_scale = math::Vec<3>(1.0, 1.0, 1.0));

          private:
            //  -- Constructors --
            Mesh(const std::string& t_serial, const math::Mat<4, 4>& t_trans_mat);

            //  -- Initialisation --
            size_t init_num(const std::string& t_serial, const std::string& t_type_string) const;
            std::vector<geom::Triangle> init_tri(const std::string& t_serial, const math::Mat<4, 4>& t_trans_mat) const;


            //  == METHODS ==
          public:
            //  -- Getters --
            size_t get_num_vert() const { return (m_num_vert); }
            size_t get_num_norm() const { return (m_num_norm); }
            size_t get_num_tri() const { return (m_num_tri); }
            const Triangle& get_tri(const size_t t_index) const { return (m_tri[t_index]); }
        };



    } // namespace geom
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GEOM_MESH_HPP
