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
#include "cls/data/table.hpp"



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
            std::vector <Column> m_col;  //! Vector of data columns.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            Table();

          private:
            //  -- Initialisation --


            //  == OPERATORS ==
          private:


            //  == METHODS ==
          private:
        };



    } // namespace data
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_DATA_TABLE_HPP
