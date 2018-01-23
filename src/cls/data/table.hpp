/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   22/01/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_DATA_TABLE_HPP
#define ARCTORUS_SRC_CLS_DATA_TABLE_HPP



//  == INCLUDES ==
//  -- Classes --
#include "cls/data/column.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace data
    {



        //  == CLASS ==
        /**
         *  Class used to store tabulated data.
         */
        class Table
        {
            //  == FIELDS ==
          private:
            //  -- Data --
            std::vector<Column> m_col;  //! Vector of data columns.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            Table() = default;
            explicit Table(const std::string& t_readable);
            Table(const std::vector<Column>& t_col);
            Table(const std::vector<std::string>& t_col_title, const std::vector<std::vector<double>>& t_col_data);

          private:
            //  -- Initialisation --
            std::vector<Column> init_col(const std::string& t_readable) const;
            std::vector<Column> init_col(const std::vector<std::string>& t_col_title,
                                         const std::vector<std::vector<double>>& t_col_data) const;


            //  == OPERATORS ==
          public:
            //  -- Access --
            Column& operator[](const size_t t_index) { return (m_col[t_index]); }
            const Column& operator[](const size_t t_index) const { return (m_col[t_index]); }

            //  -- Printing --
            friend std::ostream& operator<<(std::ostream& t_stream, const Table& t_tab);


            //  == METHODS ==
          public:
            //  -- Getters --
            size_t get_num_cols() const { return (m_col.size()); }
            size_t get_num_rows() const { return (m_col.empty() ? 0 : m_col.front().size()); }

            //  -- Setters --
            void append_col(const Column& t_col);
            void append_row(const std::vector<double>& t_row);

            //  -- Saving --
            void save(const std::string& t_path) const;
        };



    } // namespace data
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_DATA_TABLE_HPP
