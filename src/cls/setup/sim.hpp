/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   15/02/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_SETUP_SIM_HPP
#define ARCTORUS_SRC_CLS_SETUP_SIM_HPP



//  == INCLUDES ==
//  -- System --



//  == NAMESPACE ==
namespace arc
{
    namespace setup
    {



        //  == CLASS ==
        /**
         *  Simulation class which holds all objects required to run a simulation.
         */
        class Sim
        {
            //  == FIELDS ==
          private:
            //  -- Equipment --
            const std::vector<equip::Light> m_light;    //! Vector of light objects.


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



    } // namespace setup
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_SETUP_SIM_HPP
