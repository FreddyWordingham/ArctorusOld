/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   22/01/2018.
 */



//  == HEADER ==
#include "cls/data/column.hpp"



//  == INCLUDES ==
//  -- System --
#include <cassert>
#include <iomanip>

//  -- General --
#include "gen/log.hpp"

//  -- Utility --

//  -- Classes --
#include "cls/file/handle.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace data
    {



        //  == INSTANTIATION ==
        //  -- Constructors --
        /**
         *  Construct a data column from a given title and data vector.
         *
         *  @param  t_title Column title.
         *  @param  t_data  Column data.
         */
        Column::Column(const std::string& t_title, const std::vector<double>& t_data) :
            m_title(init_title(t_title)),
            m_data(t_data)
        {
        }


        //  -- Initialisation --
        /**
         *  Initialise the title string.
         *  If the title string exceeds the file print width, cut it down to size.
         *  Remove any leading or trailing whitespace.
         *
         *  @param  t_title Column title.
         *
         *  @pre    t_title must not be empty after removing whitespace.
         *  @pre    t_title must not be numerical.
         *
         *  @post   r_title must not exceed the file::PRINT_WIDTH.
         *
         *  @return The initialised column title string.
         */
        std::string Column::init_title(const std::string& t_title) const
        {
            assert(!t_title.empty());
            assert(!utl::is_numerical(t_title));

            std::string r_title(t_title);

            if (r_title.size() > file::PRINT_WIDTH)
            {
                WARN("data::Column title string must be resized.",
                     "Title width of '" << t_title.size() << "' must be resized to fit within the allocated print width of: '"
                                        << file::PRINT_WIDTH << ".");
            }

            assert(r_title.size() <= file::PRINT_WIDTH);

            return (r_title);
        }



        //  == OPERATORS ==
        //  -- Printing --
        /**
         *  Enable printing of a data column to a given ostream.
         *
         *  @param  t_stream    Stream to write to.
         *  @param  t_col       Column to be written.
         *
         *  @return A reference to the stream post-write.
         */
        std::ostream& operator<<(std::ostream& t_stream, const Column& t_col)
        {
            t_stream << std::setw(file::PRINT_WIDTH) << t_col.m_title;

            for (size_t i = 0; i < t_col.m_data.size(); ++i)
            {
                t_stream << "\n" << std::setw(file::PRINT_WIDTH) << t_col.m_data[i];
            }

            return (t_stream);
        }



        //  == METHODS ==
        //  -- Saving --
        /**
         *  Save the state of the column to a given file path.
         *
         *  @param  t_path  Path to the save location of the file.
         */
        void Column::save(const std::string& t_path) const
        {
            file::Handle file(t_path, std::fstream::out);

            //file.comment() << "Rows: " << m_data.size() << "\n";

            file << (*this);
        }



    } // namespace data
} // namespace arc
