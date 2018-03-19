#   == ALIASES ==
alias arctorus=$ARCTORUS_DIR/bin/arctorus



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
