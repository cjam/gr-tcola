SCRIPT_DIR=`dirname $0`
BUILD_DIR="build/"

CMD=$1

build_project()
{
    cd $SCRIPT_DIR
    mkdir -p $BUILD_DIR
    cd $SCRIPT_DIR/$BUILD_DIR
    cmake ..
    make
}

clean_project(){
    cd $SCRIPT_DIR
    rm -rf $BUILD_DIR
}


case $CMD in
    build)
        build_project
        ;;
    rebuild)
        echo "Rebuilding"
        clean_project
        build_project
        ;;
    test)
        echo "Testing"
        cd $SCRIPT_DIR
        mkdir -p $BUILD_DIR
        cd $SCRIPT_DIR/$BUILD_DIR
        ctest --force-new-ctest-process -V $2 $3
        ;;
    install)
        echo "Installing"
        cd $SCRIPT_DIR/$BUILD_DIR
        sudo make install
        ;;
    uninstall)
        echo "Uninstalling"
        cd $SCRIPT_DIR/$BUILD_DIR
        sudo make uninstall
        ;;
    *)
        echo "
        Available Commands
        ------------------
        build
        rebuild
        test
        install
        uninstall
        "
        ;;
esac
