#   == ALIASES ==
alias arc=$ARCTORUS_DIR/bin/arctorus



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
    rm -r bin/*;
    rm -r build/debug/*;
    rm -r build/release/*;
    rm src/hdr/config.hpp;

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
        echo "build <type> <c compiler> <c++ compiler> <colour> <verbose> <graphics> <photon paths>";
        return;
    fi

    # Change directory.
    cd $ARCTORUS_DIR/build/release > /dev/null;

    # Clean.
    clean;

    # Run cmake.
    cmake -j 4 -DCMAKE_BUILD_TYPE=$1 -DCMAKE_C_COMPILER=$2 -DCMAKE_CXX_COMPILER=$3 -DLOG_COLOUR=$4 -DLOG_VERBOSE=$5 -DGRAPHICS=$6 -DPHOTON_PATHS=$7 ../..;

    # Run make.
    make -j 4;

    # Change to previous directory.
    cd - > /dev/null;
}
