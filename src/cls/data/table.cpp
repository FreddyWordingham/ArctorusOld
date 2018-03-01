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
#include "gen/math.hpp"

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
         *  Construct a data table from a given serialised string.
         *
         *  @param  t_serial  Data table as a serialised string.
         */
        Table::Table(const std::string& t_serial) :
            m_col(init_col(t_serial))
        {
        }

        /**
         *  Construct a populated data table using a vector of data columns.
         *  Each of the columns must contain the same number of rows.
         *
         *  @param  t_col   Vector of data columns.
         *
         *  @post   m_col must not be empty.
         */
        Table::Table(const std::vector<Column>& t_col) :
            m_col(t_col)
        {
            assert(!m_col.empty());

            // Check that the columns contain the same number of rows.
            const size_t num_rows = m_col.front().size();
            for (size_t  i        = 1; i < m_col.size(); ++i)
            {
                if (m_col[i].size() != num_rows)
                {
                    ERROR("Unable to construct data::Column object.", "Columns must all contain the same number of rows.");
                }
            }
        }

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
         *  Initialise the vector of data columns from the serialised string.
         *
         *  @param  t_serial  Data table as a serialised string.
         *
         *  @pre    t_serial must not be empty.
         *
         *  @return The initialised vector of data columns.
         */
        std::vector<Column> Table::init_col(const std::string& t_serial) const
        {
            assert(!t_serial.empty());

            std::stringstream stream(t_serial);

            // Read column titles.
            std::vector<std::string> title;

            std::string line;
            if (!std::getline(stream, line))
            {
                ERROR("Unable to construct data::Table from serialised string.",
                      "Readable string does not contain a row of titles.");
            }

            std::stringstream title_stream(line);
            std::string       word;
            while (std::getline(title_stream, word, file::DELIMIT_CHAR))
            {
                utl::strip_whitespace(&word);
                title.push_back(word);
            }

            // Read column data.
            std::vector<std::vector<double>> data(title.size());
            while (std::getline(stream, line))
            {
                std::stringstream data_stream(line);

                for (size_t i = 0; i < title.size(); ++i)
                {
                    if (!std::getline(data_stream, word, file::DELIMIT_CHAR))
                    {
                        ERROR("Unable to construct data::Table from serialised string.",
                              "Line: '" << line << "', does not contain: '" << title.size() << "' values as required.");
                    }

                    data[i].push_back(math::str_to<double>(word));
                }

                if (data_stream.rdbuf()->in_avail() != 0)
                {
                    ERROR("Unable to construct data::Table from serialised string.",
                          "Line: '" << line << "', does not contain: '" << title.size() << "' values as required.");
                }
            }

            // Form data columns.
            std::vector<Column> r_col;
            for (size_t         i = 0; i < title.size(); ++i)
            {
                r_col.emplace_back(Column(title[i], data[i]));
            }

            return (r_col);
        }

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
         *
         *  @return The initialised vector of data columns.
         */
        std::vector<Column> Table::init_col(const std::vector<std::string>& t_col_title,
                                            const std::vector<std::vector<double>>& t_col_data) const
        {
            assert(!t_col_title.empty());
            assert(!t_col_data.empty());
            assert(t_col_title.size() == t_col_data.size());

            const size_t rows     = t_col_data.front().size();
            for (size_t  i        = 1; i < t_col_data.size(); ++i)
            {
                if (t_col_data[i].size() != rows)
                {
                    ERROR("Unable to construct data::Column object.", "Columns must all contain the same number of rows.");
                }
            }

            std::vector<Column> r_col;
            for (size_t         i = 0; i < t_col_title.size(); ++i)
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
            t_stream << t_tab.serialise();

            return (t_stream);
        }



        //  == METHODS ==
        //  -- Setters --
        /**
         *  Append a data column to the data table.
         *  The size of the column must match that of any columns that are already stored within the table.
         *
         *  @param  t_col   Data column to be appended to the table.
         *
         *  @pre    t_col size must match that of existing data columns.
         */
        void Table::append_col(const Column& t_col)
        {
            assert(!t_col.empty() || (t_col.size() == m_col.front().size()));

            m_col.push_back(t_col);
        }

        /**
         *  Append a data row to the data table.
         *  The size of the row must match the number of columns already stored within the table.
         *
         *  @param  t_row   Data column to be appended to the table.
         *
         *  @pre    t_row size must match the number of data columns.
         */
        void Table::append_row(const std::vector<double>& t_row)
        {
            assert(t_row.size() == m_col.size());

            for (size_t i = 0; i < t_row.size(); ++i)
            {
                m_col[i].push_back(t_row[i]);
            }
        }


        //  -- Serialisation --
        /**
         *  Create a string representation of the table.
         *
         *  @return A string representation of the table.
         */
        std::string Table::serialise() const
        {
            std::stringstream stream;

            if (m_col.empty())
            {
                WARN("No data to print in data::Table object.", "Table does not contain any data columns.");

                return (stream.str());
            }

            // Print column titles.
            for (size_t i = 0; i < (m_col.size() - 1); ++i)
            {
                stream << std::setw(file::PRINT_WIDTH) << m_col[i].get_title() << file::DELIMIT_CHAR;
            }
            stream << std::setw(file::PRINT_WIDTH) << m_col.back().get_title();

            // Print column data.
            if (m_col.front().empty())
            {
                return (stream.str());
            }

            stream << "\n";
            for (size_t i = 0; i < (m_col.front().size() - 1); ++i)
            {
                for (size_t j = 0; j < (m_col.size() - 1); ++j)
                {
                    stream << std::setw(file::PRINT_WIDTH) << m_col[j][i] << file::DELIMIT_CHAR;
                }
                stream << std::setw(file::PRINT_WIDTH) << m_col.back()[i] << "\n";
            }
            for (size_t i = 0; i < (m_col.size() - 1); ++i)
            {
                stream << std::setw(file::PRINT_WIDTH) << m_col[i].back() << file::DELIMIT_CHAR;
            }
            stream << std::setw(file::PRINT_WIDTH) << m_col.back().back();

            return (stream.str());
        }


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
            else
            {
                file.comment() << "Rows: 0\n";
            }

            file << serialise();
        }



    } // namespace data
} // namespace arc
