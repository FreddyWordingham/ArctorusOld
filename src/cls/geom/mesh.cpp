/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   28/01/2018.
 */



//  == HEADER ==
#include "cls/geom/mesh.hpp"



//  == INCLUDES ==
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
         *  Construct a mesh from a given serialised string and transformations.
         *
         *  @param  t_serial    Mesh as a serialised string.
         *  @param  t_trans Vector of translation.
         *  @param  t_dir   Direction to face.
         *  @param  t_spin  Spin angle.
         *  @param  t_scale Vector of scaling values.
         *
         *  @pre    t_dir's magnitude must be greater than zero.
         *  @pre    t_scale elements must all be non-zero.
         */
        Mesh::Mesh(const std::string& t_serial, const math::Vec<3>& t_trans, const math::Vec<3>& t_dir, double t_spin,
                   const math::Vec<3>& t_scale) :
            Mesh(t_serial, math::create_trans_mat(t_trans, t_dir, t_spin, t_scale))
        {
            assert(t_dir.magnitude() > 0.0);
            assert(t_scale[X] != 0.0);
            assert(t_scale[Y] != 0.0);
            assert(t_scale[Z] != 0.0);
        }

        /**
         *  Construct a mesh from a given serialised string and transformation matrix.
         *
         *  @param  t_serial    Mesh as a serialised string.
         *  @param  t_trans_mat Transformation matrix.
         */
        Mesh::Mesh(const std::string& t_serial, const math::Mat<4, 4>& t_trans_mat) :
            m_num_vert(init_num(t_serial, POS_KEYWORD)),
            m_num_norm(init_num(t_serial, NORM_KEYWORD)),
            m_num_tri(init_num(t_serial, FACE_KEYWORD)),
            m_tri(init_tri(t_serial, t_trans_mat))
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
         *  Initialise the vector of triangles forming the mesh from a serialised mesh and transformation matrices.
         *
         *  @param  t_serial    Mesh as a serialised string.
         *  @param  t_trans_mat Transformation matrix.
         *
         *  @post   Number of read vertex positions must equal that read initially.
         *  @post   Number of read vertex normals must equal that read initially.
         *  @post   Number of read faces must equal that read initially.
         *
         *  @return The initialised vector of triangle faces.
         */
        std::vector<geom::Triangle> Mesh::init_tri(const std::string& t_serial, const math::Mat<4, 4>& t_trans_mat) const
        {
            // Create the transposed inverted transformation matrix.
            math::Mat<4, 4> trans_inv_mat = math::transpose(math::inverse(t_trans_mat));

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
                    // Read in the position vector.
                    math::Vec<4> pos;
                    line_stream >> pos[X] >> pos[Y] >> pos[Z];
                    pos[3] = 1.0;

                    // Transform it using the position transformation matrix.
                    pos = t_trans_mat * pos;

                    // Add the three-dimensional position to the vertex position list.
                    vert_pos.push_back(math::Vec<3>({{pos[X], pos[Y], pos[Z]}}));
                }
                else if (word == NORM_KEYWORD)
                {
                    // Read in the normal vector.
                    math::Vec<4> norm;
                    line_stream >> norm[X] >> norm[Y] >> norm[Z];
                    norm[3] = 1.0;

                    // Transform it using the transverse-inverted-transformation matrix.
                    norm = trans_inv_mat * norm;

                    // Add the three-dimensional normal to the vertex normal list.
                    vert_norm.push_back(math::normalise(math::Vec<3>({{norm[X], norm[Y], norm[Z]}})));
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
                                  "Unable to parse serialised wavefront object line: '" << line << "'.");
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
