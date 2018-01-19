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
            const std::string   m_title;    //! Title of the data column.
            std::vector<double> m_data;     //! Elements of the data column.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            Column(const std::string& t_title, const std::vector<double>& t_data);

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
