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

//  -- Utility --
#include "utl/stream.hpp"



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

            // Read in the vertex positions and normals.
            std::stringstream serial_stream(t_serial);
            std::string(line);
            while (std::getline(serial_stream, line))
            {
                std::stringstream line_stream(line);
                std::string       word;
                line_stream >> word;

                if (word == POS_KEYWORD)
                {
                    math::Vec<3> pos;
                    line_stream >> pos[X] >> pos[Y] >> pos[Z];

                    vert_pos.push_back(pos);
                }
                else if (word == NORM_KEYWORD)
                {
                    math::Vec<3> norm;
                    line_stream >> norm[X] >> norm[Y] >> norm[Z];

                    norm.normalise();

                    vert_norm.push_back(norm);
                }

                if (line_stream.fail())
                {
                    ERROR("Unable to construct geom::Mesh object.", "Unable to parse serial line: '" << line << "'.");
                }
            }

            // Check the number of vertex positions and normals equals that expected.
            assert(vert_pos.size() == m_num_vert);
            assert(vert_norm.size() == m_num_norm);


            // Read in the triangular faces.
            utl::rewind(serial_stream);
            while (std::getline(serial_stream, line))
            {
                std::stringstream line_stream(line);
                std::string       word;
                line_stream >> word;

                if (word == FACE_KEYWORD)
                {
                    std::array<std::string, 3> face;
                    line_stream >> face[ALPHA] >> face[BETA] >> face[GAMMA];

                    if (line_stream.rdbuf()->in_avail() != 0)
                    {
                        ERROR("Unable to construct geom::Mesh object.",
                              "Non-triangular face located within line: '" << line << "'.");
                    }

                    std::array<size_t, 3> pos_index{}, norm_index{};
                    for (size_t           i = 0; i < 3; ++i)
                    {
                        const size_t first_slash = face[i].find_first_of('/');
                        const size_t last_slash  = face[i].find_last_of('/');

                        std::stringstream pos(face[i].substr(0, first_slash));
                        pos >> pos_index[i];
                        --pos_index[i];

                        std::stringstream norm(face[i].substr(last_slash + 1));
                        norm >> norm_index[i];
                        --norm_index[i];

                        if (pos.fail() || norm.fail())
                        {
                            ERROR("Unable to construct geom::Mesh object.",
                                  "Unable to parse stringified wavefront object line: '" << line << "'.");
                        }
                    }

                    r_tri.push_back(Triangle(
                        {{Vertex(vert_pos[pos_index[ALPHA]], vert_norm[norm_index[ALPHA]]), Vertex(vert_pos[pos_index[BETA]],
                                                                                                   vert_norm[norm_index[BETA]]), Vertex(
                            vert_pos[pos_index[GAMMA]], vert_norm[norm_index[GAMMA]])}}));
                }

                if (line_stream.fail())
                {
                    ERROR("Unable to construct geom::Mesh object.", "Unable to parse serial line: '" << line << "'.");
                }
            }

            // Check the number of faces equals that expected.
            assert(r_tri.size() == m_num_tri);

            return (r_tri);
        }



    } // namespace geom
} // namespace arc
