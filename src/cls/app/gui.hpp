/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   01/02/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_APP_GUI_HPP
#define ARCTORUS_SRC_CLS_APP_GUI_HPP



//  == INCLUDES ==
//  -- System --



//  == NAMESPACE ==
namespace arc
{
    namespace app
    {



        //  == CLASS ==
        /**
         *  Application graphical user interface.
         */
        class Gui : public wxApp
        {
            //  == FIELDS ==
          private:


            //  == INSTANTIATION ==
          public:
            //  -- Initialisation --
            virtual bool OnInit();


            //  == METHODS ==
          private:
        };



    } // namespace app
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_APP_GUI_HPP
