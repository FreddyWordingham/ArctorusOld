/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   15/02/2018.
 */



//  == HEADER ==
#include "cls/parser/json.hpp"



//  == INCLUDES ==
//  -- Classes --
#include "cls/file/handle.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace parser
    {



        //  == INSTANTIATION ==
        //  -- Constructors --
        /**
         *  Construct a json object from a serialised json object.
         *
         *  @param  t_name      Name of the base json object.
         *  @param  t_serial    Serialised json object.
         */
        Json::Json(const std::string& t_name, const std::string& t_serial) :
            m_name(t_name),
            m_data(init_data(t_serial))
        {
        }

        /**
         *  Construct a json object using a given name and a sub-json data object.
         *
         *  @param  t_name  Name of the new json object.
         *  @param  t_data  New json data.
         */
        Json::Json(const std::string& t_name, const nlohmann::json& t_data) :
            m_name(t_name),
            m_data(t_data)
        {
        }


        //  -- Initialisation --
        /**
         *  Initialise the base json data object using the serialised json data object.
         *  Parsing errors are not tolerated.
         *
         *  @param  t_serial    Serialised json data object.
         *
         *  @return The initialised json data object.
         */
        nlohmann::json Json::init_data(const std::string& t_serial) const
        {
            // Create the base json data object.
            nlohmann::json r_base;

            // Attempt to parse in the serialised json data.
            try
            {
                std::stringstream(t_serial) >> r_base;
            }
            catch (...)
            {
                ERROR("Unable to construct parser::Json object.", "Unable to parse serialised data of: '" << m_name << "'.");
            }

            return (r_base);
        }



        //  == OPERATORS ==
        /**
         *  Form a json parser child object.
         *
         *  @param  t_child Name of the child object to form the base of a new json parser.
         *
         *  @return A json parser child object.
         */
        Json Json::operator[](const std::string& t_child) const
        {
            if (!has_child(t_child))
            {
                ERROR("Unable to access child member of data::Json object.",
                      "Parent data::Json object: '" << m_name << "' has no child named: '" << t_child << "'.")
            }

            return (Json(m_name + "-" + t_child, m_data[t_child]));
        }


        //  -- Printing --
        /**
         *  Enable printing of a json object to a given ostream.
         *
         *  @param  t_stream    Stream to write to.
         *  @param  t_json      Json object to be written.
         *
         *  @return A reference to the stream post-print.
         */
        std::ostream& operator<<(std::ostream& t_stream, const Json& t_json)
        {
            t_stream << t_json.serialise();

            return (t_stream);
        }



        //  == METHODS ==
        //  -- Parsing --
        /**
         *  Parse the list of all the json data object's child member names.
         *
         *  @return The vector of all this json object's child member names.
         */
        std::vector<std::string> Json::parse_child_names() const
        {
            // Create return vector of name strings.
            std::vector<std::string> r_vec;

            // Added name keys to the name vector.
            for (auto i = m_data.begin(); i != m_data.end(); ++i)
            {
                r_vec.push_back(i.key());
            }

            return (r_vec);
        }


        //  -- Serialisation --
        /**
         *  Create a string representation of the json object.
         *
         *  @return A string representation of the json object.
         */
        std::string Json::serialise() const
        {
            // Create a stringstream to write to.
            std::stringstream stream;

            // Write the object to the stringstream.
            stream << m_data.dump(INDENT_WIDTH);

            return (stream.str());
        }


        //  -- Saving --
        /**
         *  Save the state of the json object to a given file path.
         *
         *  @param  t_path  Path to the save location of the file.
         */
        void Json::save(const std::string& t_path) const
        {
            // Create the output file handle.
            file::Handle file(t_path, std::fstream::out);

            // Write out the json data.
            file << serialise();
        }




    } // namespace parser
} // namespace arc
