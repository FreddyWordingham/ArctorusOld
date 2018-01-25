/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   25/01/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_INTERPOLATOR_LINEAR_HPP
#define ARCTORUS_SRC_CLS_INTERPOLATOR_LINEAR_HPP



//  == INCLUDES ==
//  -- System --
#include <vector>



//  == NAMESPACE ==
namespace arc
{
    namespace interpolator
    {



        //  == CLASS ==
        /**
         *  A linear interpolator class.
         *  Uses a given set of nodes to calculate intermediate values.
         */
        class Linear
        {
            //  == FIELDS ==
          private:
            //  -- Bounds --
            const double m_min_bound;   //! Minimum bound of the interpolation range.
            const double m_max_bound;   //! Maximum bound of the interpolation range.

            //  -- Data --
            const std::vector<double> m_x;      //! Vector of X positions of the nodes.
            const std::vector<double> m_y;      //! Vector of Y positions of the nodes.
            const std::vector<double> m_grad;   //! Vector of intermediate gradients.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            Linear(const std::vector<double>& t_x, const std::vector<double>& t_y);

          private:
            //  -- Initialisation --
            std::vector<double> init_grad() const;


            //  == OPERATORS ==
          public:
            //  -- Interpolation --
            double operator()(double t_val) const;


            //  == METHODS ==
          public:
            //  -- Serialisation --
            std::string serialise(size_t t_samples) const;
        };



    } // namespace interpolator
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_INTERPOLATOR_LINEAR_HPP
