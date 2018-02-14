/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   26/01/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_RANDOM_LINEAR_HPP
#define ARCTORUS_SRC_CLS_RANDOM_LINEAR_HPP



//  == INCLUDES ==
//  -- System --
#include <vector>



//  == NAMESPACE ==
namespace arc
{
    namespace random
    {



        //  == CLASS ==
        /**
         *  A generator class which generates random numbers according to a given discrete probability distribution.
         */
        class Linear
        {
            //  == FIELDS ==
          private:
            //  -- Bounds --
            const double m_min_bound;   //! Minimum bound of the generation range.
            const double m_max_bound;   //! Maximum bound of the generation range.

            //  -- Data --
            const std::vector<double> m_x;      //! Vector of X positions.
            const std::vector<double> m_p;      //! Vector of corresponding probabilities.
            const std::vector<double> m_grad;   //! Vector of probability gradients.
            const std::vector<double> m_inter;  //! Vector of probability intersections.
            const std::vector<double> m_cdf;    //! The normalised cumulative distribution of the probabilities.
            const std::vector<double> m_frac;   //! Vector of the fractions of the triangular interpolation range.


            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            Linear(const std::vector<double>& t_x, const std::vector<double>& t_p);

          private:
            //  -- Initialisation --
            std::vector<double> init_grad() const;
            std::vector<double> init_inter() const;
            std::vector<double> init_cdf() const;
            std::vector<double> init_frac() const;


            //  == OPERATORS ==
          public:
            //  -- Generation --
            double operator()() const;
            double operator()(double t_min, double t_max) const;



            //  == METHODS ==
          public:
            //  -- Interpolation --
            double get_cdf(double t_x) const;
        };



    } // namespace random
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_RANDOM_LINEAR_HPP
