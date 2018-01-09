/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   09/01/2018.
 */



//  == GUARD ==
#ifndef ARCTORUS_SRC_CLS_TERM_LOGGER_HPP
#define ARCTORUS_SRC_CLS_TERM_LOGGER_HPP



//  == INCLUDES ==
//  -- System --



//  == NAMESPACE ==
namespace arc
{
    namespace term
    {



        //  == SETTINGS ==
        //  -- Title --
        constexpr const char* TITLE = R"(                              llrr                              )"
            R"(                             lllrrr                             )"
            R"(                            llllrrrr                            )"
            R"(                      ~~~~~lllllrrrrrMBBGGGYYYYRRRRRRRRRRRRRRRRR)"
            R"(              ~~~~~~~~    lllll  rrrrrMMMMBBBBGGGGGGGYYYYYYYYYYY)"
            R"(      ~~~~~~~~           lllll    rrrrr     MMMMMMMBBBGGGGGGGGGG)"
            R"(~~~~~~                  llll        rrrr          MMMMMMBBBBBBBB)"
            R"(                       lll            rrr               MMMMMMMM)"
            R"(   __     ____    ____   ______   ____    ____   __  __   ____  )"
            R"(  //\\   ||__))  //  ``    ||    //  \\  ||__))  ||  ||  //____ )"
            R"( //--\\  ||  \\  \\__,,    ||    \\__//  ||  \\  \\__//   ___// )";  //! Arctorus title.




        //  == CLASS ==
        /**
         *  Terminal logger class which allows formatted printing of message logs.
         *  Messages are printed to the terminal by default.
         *  Coloured printing is enabled when cout is not being piped to a file.
         *  Should be used as a singleton class via the get_instance method.
         */
        class Logger
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



    } // namespace term
} // namespace arc



//  == GUARD END ==
#endif // ARCTORUS_SRC_CLS_TERM_LOGGER_HPP
