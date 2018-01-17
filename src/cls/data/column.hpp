/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   17/01/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_DATA_COLUMN_HPP
#define ARCTORUS_SRC_CLS_DATA_COLUMN_HPP



//  == INCLUDES ==
//  -- System --
#include <string>
#include <vector>



//  == NAMESPACE ==
namespace arc
{
    namespace data
    {



        //  == CLASS ==
        /**
         *  A data column with an associated header title.
         */
        class Column
        {
            //  == FIELDS ==
          private:
            //  -- Data --
            const std::string   title;    //! Title of the data column.
            std::vector<double> data;   //! Elements of the data column.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --

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
#endif // ARCTORUS_SRC_CLS_DATA_COLUMN_HPP
