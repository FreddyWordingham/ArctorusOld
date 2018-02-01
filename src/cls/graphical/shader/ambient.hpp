/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   01/02/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_GRAPHICAL_SHADER_AMBIENT_HPP
#define ARCTORUS_SRC_CLS_GRAPHICAL_SHADER_AMBIENT_HPP



//  == BASE CLASS ==
#include "cls/graphical/shader.hpp"



//  == NAMESPACE ==
namespace arc
{
    namespace graphical
    {
        namespace shader
        {



            //  == CLASS ==
            /**
             *  Ambient lighting shader.
             *  Props are uniformly luminescent.
             */
            class Ambient : public Shader
            {
                //  == FIELDS ==
              private:


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



        } // namespace shader
    } // namespace graphical
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GRAPHICAL_SHADER_AMBIENT_HPP
