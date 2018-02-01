/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   01/02/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_GRAPHICAL_SCENE_HPP
#define ARCTORUS_SRC_CLS_GRAPHICAL_SCENE_HPP



//  == INCLUDES ==
//  -- System --



//  == NAMESPACE ==
namespace arc
{
    namespace graphical
    {



        //  == CLASS ==
        /**
         *  Graphical window class.
         *  Used to visualise three-dimensional simulation data.
         */
        class Scene
        {
            //  == FIELDS ==
          private:
            //  -- Window Handle --
            GLFWwindow* m_window;   //! Handle to the main graphical window.



            //  == INSTANTIATION ==
          public:
            //  -- Constructors --
            Scene();

          private:
            //  -- Initialisation --


            //  == OPERATORS ==
          private:


            //  == METHODS ==
          private:
        };



    } // namespace graphical
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_GRAPHICAL_SCENE_HPP
