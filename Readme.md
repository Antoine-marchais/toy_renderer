# Toy Renderer: A basic renderer to learn computer graphics

## Installing

### Prerequisites

For building the project, cmake and a c++ must be available on the system

This project uses `libpng` and the `png++` wrapper. `libpng` should be installed on the system, but the `png++`
headers must be downloaded and installed from the [png++ website](https://www.nongnu.org/pngpp/doc/0.2.9/)

### Building the project

Once cmake is installed you can simply run the following command in the root directory to configure and build the project.
```
cmake -B build
cmake --build build
```

## Running

After building, the main executable will be located in the binary `build/src/bin/ToyRenderer`. You can then execute with
`gdb` for debugging.

## Testing

Tests are created with [GoogleTest](http://google.github.io/googletest/). The tests can be run and debugged by launching
the binary `build/src/bin/ToyRendere` with `gdb`
