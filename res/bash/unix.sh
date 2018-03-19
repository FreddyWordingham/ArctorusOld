#   == ALIASES ==
alias arc=$ARCTORUS_DIR/bin/arctorus
alias plot='python3 ~/Arctorus/res/python/plot.py'



#   == FUNCTIONS ==
#   -- Cleaning --
#
#   Remove temporary Arctorus build files.
#
clean_arc()
{
    # Change directory.
    cd $ARCTORUS_DIR > /dev/null;

    # Remove files.
    rm -r bin/* > /dev/null;
    rm -r build/debug/* > /dev/null;
    rm -r build/release/* > /dev/null;
    rm src/hdr/config.hpp > /dev/null;

    # Change to previous directory.
    cd - > /dev/null;
}

#   -- Building --
#
#   Build Arctorus.
#   Previous build files are deleted prior to building.
#
build_arc()
{
    # Check number of command line arguments.
    if [ "$#" -ne 7 ]; then
        echo "Invalid build call:";
        echo "build_arc <type> <c compiler> <c++ compiler> <colour> <verbose> <graphics> <photon paths>";
        return;
    fi

    # Change directory.
    cd $ARCTORUS_DIR/build/$1 > /dev/null;

    # Run cmake.
    cmake -j 4 -DCMAKE_BUILD_TYPE=$1 -DCMAKE_C_COMPILER=$2 -DCMAKE_CXX_COMPILER=$3 -DLOG_COLOUR=$4 -DLOG_VERBOSE=$5 -DGRAPHICS=$6 -DPHOTON_PATHS=$7 ../..;

    # Change to previous directory.
    cd - > /dev/null;
}

#
#   Re-make Arctorus.
#   Previous build files are deleted prior to building.
#
make_arc()
{
    # Check number of command line arguments.
    if [ "$#" -ne 1 ]; then
        echo "Invalid make call:";
        echo "make_arc <type>";
        return;
    fi

    # Change directory.
    cd $ARCTORUS_DIR/build/$1 > /dev/null;

    # Remove arctorus binary.
    rm $ARCTORUS_DIR/bin/arctorus;

    # Run make.
    make -j 4;

    # Change to previous directory.
    cd - > /dev/null;
}
