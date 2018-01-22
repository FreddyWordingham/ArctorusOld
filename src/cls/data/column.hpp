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
            explicit Column(const std::string& t_readable);
            Column(const std::string& t_title, const std::vector<double>& t_data);

          private:
            //  -- Initialisation --
            std::string init_title_from_readable(const std::string& t_readable) const;
            std::vector<double> init_data_from_readable(const std::string& t_readable) const;
            std::string init_title(const std::string& t_title) const;


            //  == OPERATORS ==
          public:
            //  -- Access --
            double& operator[](const size_t t_index) { return (m_data[t_index]); }
            const double& operator[](const size_t t_index) const { return (m_data[t_index]); }

            //  -- Printing --
            friend std::ostream& operator<<(std::ostream& t_stream, const Column& t_col);


            //  == METHODS ==
          public:
            //  -- Getters --
            std::string get_title() const { return (m_title); }
            size_t size() const { return (m_data.size()); }
            bool empty() const { return (m_data.empty()); }

            //  -- Manipulation --
            void push_back(const double t_element) { m_data.push_back(t_element); }

            //  -- Saving --
            void save(const std::string& t_path) const;
        };



    } // namespace data
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_DATA_COLUMN_HPP
