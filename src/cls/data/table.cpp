/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   22/01/2018.
 */



//  == HEADER ==
#include "cls/data/table.hpp"



//  == INCLUDES ==
//  -- System --
#include <iomanip>

//  -- General --
#include "gen/log.hpp"

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
         *  Construct a populated data table by forming the given column titles and data vectors into data columns.
         *
         *  @param  t_col_title Vector of column titles.
         *  @param  t_col_data  Vector of data vectors.
         */
        Table::Table(const std::vector<std::string>& t_col_title, const std::vector<std::vector<double>>& t_col_data) :
            m_col(init_col(t_col_title, t_col_data))
        {
        }


        //  -- Initialisation --
        /**
         *  Construct a populated data table by forming the given column titles and data vectors into data columns.
         *
         *  @param  t_col_title Vector of column titles.
         *  @param  t_col_data  Vector of data vectors.
         *
         *  @pre    t_col_title must not be empty.
         *  @pre    t_col_data must not be empty.
         *  @pre    t_col_title size must match the t_col_data size.
         *  @pre    t_col_data vectors must all be of the same length.
         */
        std::vector<Column> Table::init_col(const std::vector<std::string>& t_col_title,
                                            const std::vector<std::vector<double>>& t_col_data) const
        {
            assert(!t_col_title.empty());
            assert(!t_col_data.empty());
            assert(t_col_title.size() == t_col_data.size());

            const size_t rows = t_col_data.front().size();
            for (size_t  i    = 1; i < t_col_data.size(); ++i)
            {
                assert(t_col_data[i].size() == rows);
            }

            std::vector<Column> r_col;

            for (size_t i = 0; i < t_col_title.size(); ++i)
            {
                r_col.emplace_back(Column(t_col_title[i], t_col_data[i]));
            }

            return (r_col);
        }



        //  == OPERATORS ==
        //  -- Printing --
        /**
         *  Enable printing of a data table to a given ostream.
         *
         *  @param  t_stream    Stream to write to.
         *  @param  t_tab       Table to be written.
         *
         *  @return A reference to the stream post-write.
         */
        std::ostream& operator<<(std::ostream& t_stream, const Table& t_tab)
        {
            if (t_tab.m_col.empty())
            {
                WARN("Unable to print data::Table object.", "Table does not contain any data columns.");

                return (t_stream);
            }

            // Print column titles.
            for (size_t i = 0; i < (t_tab.m_col.size() - 1); ++i)
            {
                t_stream << std::setw(file::PRINT_WIDTH) << t_tab.m_col[i].get_title() << file::DELIMIT_CHAR;
            }
            t_stream << std::setw(file::PRINT_WIDTH) << t_tab.m_col.back().get_title() << "\n";

            // Print column data.
            if (t_tab.m_col.front().empty())
            {
                return (t_stream);
            }

            for (size_t i = 0; i < (t_tab.m_col.front().size() - 1); ++i)
            {
                for (size_t j = 0; j < (t_tab.m_col.size() - 1); ++j)
                {
                    t_stream << std::setw(file::PRINT_WIDTH) << t_tab.m_col[j][i] << file::DELIMIT_CHAR;
                }
                t_stream << std::setw(file::PRINT_WIDTH) << t_tab.m_col.back()[i] << "\n";
            }
            for (size_t i = 0; i < (t_tab.m_col.size() - 1); ++i)
            {
                t_stream << std::setw(file::PRINT_WIDTH) << t_tab.m_col[i].back() << file::DELIMIT_CHAR;
            }
            t_stream << std::setw(file::PRINT_WIDTH) << t_tab.m_col.back().back();

            return (t_stream);
        }



        //  == METHODS ==
        //  -- Saving --
        /**
         *  Save the state of the table to a given file path.
         *
         *  @param  t_path  Path to the save location of the file.
         */
        void Table::save(const std::string& t_path) const
        {
            file::Handle file(t_path, std::fstream::out);

            file.comment() << "Cols: " << m_col.size() << "\n";
            if (!m_col.empty())
            {
                file.comment() << "Rows: " << m_col.front().size() << "\n";
            }

            file << (*this);
        }



    } // namespace data
} // namespace arc
