/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   28/01/2018.
 */



//  == HEADER ==
#include "cls/geom/mesh.hpp"



//  == INCLUDES ==
//  -- System --
#include "gen/log.hpp"


//  == NAMESPACE ==
namespace arc
{
    namespace geom
    {



        //  == INSTANTIATION ==
        //  -- Constructors --
        /**
         *  Construct a mesh from a given serialised string.
         *
         *  @param  t_serial    Mesh as a serialised string.
         */
        Mesh::Mesh(const std::string& t_serial) :
            m_num_vert(init_num(t_serial, POS_KEYWORD)),
            m_num_norm(init_num(t_serial, NORM_KEYWORD)),
            m_num_tri(init_num(t_serial, FACE_KEYWORD)),
            m_tri(init_tri(t_serial))
        {
        }


        //  -- Initialisation --
        /**
         *  Determine the number of a given type of data within the wavefront mesh.
         *
         *  @param  t_serial        Mesh as a serialised string.
         *  @param  t_type_string   String identifying the type within the wavefront file.
         *
         *  @return The number of the type within the wavefront file.
         */
        size_t Mesh::init_num(const std::string& t_serial, const std::string& t_type_string) const
        {
            size_t r_num = 0;

            std::stringstream serial_stream(t_serial);

            std::string line;
            while (std::getline(serial_stream, line))
            {
                std::stringstream line_stream(line);

                std::string word;
                line_stream >> word;

                if (word == t_type_string)
                {
                    ++r_num;
                }
            }

            return (r_num);
        }

        /**
         *  Initialise the vector of triangles forming the mesh.
         *
         *  @param  t_serial        Mesh as a serialised string.
         *
         *  @post   Number of read vertex positions must equal that read initially.
         *  @post   Number of read vertex normals must equal that read initially.
         *  @post   Number of read faces must equal that read initially.
         *
         *  @return The initialised vector of triangle faces.
         */
        std::vector<geom::Triangle> Mesh::init_tri(const std::string& t_serial) const
        {
            // Create return vector of triangles.
            std::vector<geom::Triangle> r_tri;
            r_tri.reserve(m_num_tri);

            // Create vectors of vertex positions and normals.
            std::vector<math::Vec<3>> vert_pos, vert_norm;
            vert_pos.reserve(m_num_vert);
            vert_norm.reserve(m_num_norm);

            std::stringstream serial_stream(t_serial);
            std::string(line);
            while (std::getline(serial_stream, line))
            {

            }

            // Check the number of vertex positions and normals equals that expected.
            assert(vert_pos.size() == m_num_vert);
            assert(vert_norm.size() == m_num_norm);




            // Check the number of faces equals that expected.
            assert(r_tri.size() == m_num_tri);

            return (r_tri);
        }



    } // namespace geom
} // namespace arc
