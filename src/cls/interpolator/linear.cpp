/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   25/01/2018.
 */



//  == HEADER ==
#include "cls/interpolator/linear.hpp"



//  == INCLUDES ==
//  -- System --
#include <sstream>

//  -- Utility --
#include "utl/vector.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace interpolator
    {



        //  == INSTANTIATION ==
        //  -- Constructors --
        /**
         *  Construct a linear interpolator from a pair of data vectors.
         *
         *  @param  t_x X data values to be interpolated between.
         *  @param  t_y X data values to be interpolated from.
         *
         *  @post   m_min_bound must be less than m_max_bound.
         */
        Linear::Linear(const std::vector<double>& t_x, const std::vector<double>& t_y) :
            m_min_bound(t_x.front()),
            m_max_bound(t_x.back()),
            m_x(t_x),
            m_y(t_y),
            m_grad(init_grad())
        {
            assert(m_min_bound < m_max_bound);
        }


        //  -- Initialisation --
        /**
         *  Initialise the vector of node gradients.
         *
         *  @pre    m_x and m_y data vectors must be the same size.
         *  @pre    m_x size must be greater than one.
         *  @pre    m_y size must be greater than one.
         *  @pre    m_x data must be ascending.
         *
         *  @return The initialised vector of node gradients.
         */
        std::vector<double> Linear::init_grad() const
        {
            assert(m_x.size() == m_y.size());
            assert(m_x.size() > 1);
            assert(m_y.size() > 1);
            assert(utl::is_ascending(m_x));

            std::vector<double> r_grad(m_x.size() - 1);
            for (size_t         i = 0; i < r_grad.size(); ++i)
            {
                r_grad[i] = (m_y[i + 1] - m_y[i]) / (m_x[i + 1] - m_x[i]);
            }

            return (r_grad);
        }



        //  == OPERATORS ==
        //  -- Interpolation --
        /**
         *  Interpolate a value from between the data nodes.
         *
         *  @param  t_val   X value to be interpolated.
         *
         *  @pre    t_val must be greater than or equal to m_min_bound and less than or equal to m_max_bound.
         *
         *  @return The interpolated y value.
         */
        double Linear::operator()(const double t_val) const
        {
            assert((t_val >= m_min_bound) && (t_val <= m_max_bound));

            static size_t index = 0;
            index = utl::lower_index(m_x, t_val, index);

            return (m_y[index] + ((t_val - m_x[index]) * m_grad[index]));
        }



        //  == METHODS ==
        //  -- Serialisation --
        /**
         *  Create a string representation of the linear interpolator.
         *
         *  @param  t_intermediates Number of samples to take between nodes.
         *
         *  @return A string representation of the linear interpolator.
         */
        std::string serialise(const size_t t_intermediates) const
        {
            std::stringstream stream;

//            data::Column x("x", t_samples), y("y", std)


            return (stream.str());
        }



    } // namespace interpolator
} // namespace arc
