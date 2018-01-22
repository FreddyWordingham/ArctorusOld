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
            Table(const std::vector<std::string>& t_col_title, const std::vector<std::vector<double>>& t_col_data);

          private:
            //  -- Initialisation --
            std::vector<Column> init_col(const std::vector<std::string>& t_col_title,
                                         const std::vector<std::vector<double>>& t_col_data) const;


            //  == OPERATORS ==
          private:


            //  == METHODS ==
          private:
        };



    } // namespace data
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_DATA_TABLE_HPP
