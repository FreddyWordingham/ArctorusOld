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
         *
         *  @post   r_title must not exceed the file::PRINT_WIDTH.
         *
         *  @return The initialised column title string.
         */
        std::string Column::init_title(const std::string& t_title) const
        {
            assert(!t_title.empty());

            std::string r_title(t_title);

            if (r_title.size() > file::PRINT_WIDTH)
            {
                // TODO
            }

            assert(r_title.size() <= file::PRINT_WIDTH);

            return (r_title);
        }



    } // namespace data
} // namespace arc
