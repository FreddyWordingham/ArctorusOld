/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   13/02/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_RANDOM_STEP_HPP
#define ARCTORUS_SRC_CLS_RANDOM_STEP_HPP



//  == INCLUDES ==
//  -- System --



//  == NAMESPACE ==
namespace arc
{
    namespace random
    {



        //  == CLASS ==
        /**
         *  A generator class which generates random numbers according to a given step probability distribution.
         */
        class Step
        {
            //  == FIELDS ==
          private:
            //  -- Data --
            const std::vector<double> m_x;      //! Vector of values
            const std::vector<double> m_p;      //! Vector of corresponding probabilities.
            const std::vector<double> m_cdf;    //! The normalised cumulative distribution of the probabilities.


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



    } // namespace random
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_RANDOM_STEP_HPP
