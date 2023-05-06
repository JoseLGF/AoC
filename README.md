# AoC
My solutions to the Advent Of Code event.

## Run the 2020 Python solutions
Run the following command in a Windows Command Line:
```
./2020/Python/RunAllDays.bat
```

## 2021 C++ solutions

### Build
The 2021 AOC are written in C++ in Linux. To build using cmake, execute the following commands from `./2021/` as the root folder:
```
$ mkdir build
$ cd build
$ cmake ..
$ make
```
After this, the binary `AOC2021` will be built in the `build` directory.
### Run
To run the 2021 solutions, specify the location of the `input` files.
From the build folder:
```
$ ./AOC2021 ../input/
```

## Run the 2022 Rust solutions
The 2022 AoC solutions are written in Rust in Linux. They can be run by cding into the 2022 directory and running cargo:
```
$ cd 2022
$ cargo run
```
