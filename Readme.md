# gr-tcola

This is a GNU Radio Implementation of the Time-Compression / Overlap-Add spread spectrum technique.

> Thanks to Stephen Harrison for all of the great research and initial python implementation which was adapted to create GNU Radio Blocks.


## Getting Started

### Building 

The following shell commands will create the build directory and build the blocks.

```sh
mkdir -p build
cd ./build
cmake ..
make
```

### Testing

```sh
make test
```

or for verbose test output

```sh
ctest --force-new-ctest-process -V
```

or to rerun failed tests

```sh
ctest --force-new-ctest-process -V --rerun-failed
```


### Installing

```sh
sudo make install
```
