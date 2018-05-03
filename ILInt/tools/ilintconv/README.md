# ILIntConv

## Description

The **ILIntConv** is a simple command line tool designed to make convertions between the
ILInt format and numerical values and vice-versa.

## Usage

```
ilintconv [-c] [-d] [-x] [-h] [<value>]
```

* -c: Reads the output from the standard input;
* -d: Decodes the value;
* -h: Prints the help screen;
* -x: Outputs/inputs numeric values as hexadecimal instead of decimal;
* <value>: The value to be converted

When encoding, the value must be a valid decimal and/or hexadecimal (if -x is used)
value that can be stored inside an unsigned 64-bit integer. When decoding, the input
must be a valid hexadecimal string with 2 to 18 charactes.

### Return codes

 Code | Meaning
 ---- | -------
  0 | Success
  1 | Unknown option
  2 | Too many options
  3 | The input value is too long
  4 | No input value
  5 | The input value is invalid
  6 | Unable to convert/decode the value due to a runtime error

## How to build

In order to build **ILIntConv**, it is necessary to have 
[**cmake**](https://cmake.org/) and a C99 compiler compatible with it.

For **Linux** and **MacOS**, both **GNU GCC** and **CLang** may be used. For **Windows**,
it is possible to use the **Microsoft Visual Studio**, **MingW** or **CLang**. 
**GNU GCC** and **CLang**, will also require **GNU Make** or **Ninja**.

Once all dependencies are ready, execute the following procedure to build **ILIntConv**:

1. Create a directory called build parallel to this directory (e.g.: ```mkdir ../build```);
1. Goto the newly created directory (e.g.: ```cd ../build```);
1. Run **cmake** inside this directory, pointing to the src directory (```cmake ../ilintconv```)
1. Execute ```cmake --build . --clean-first``` to execute the build;

On **Windows** it will generate an executable called **ilintconv.exe**. The binary for
all other platforms will be called **ilintconv**.

## Development environment

In order to create the development environment for  **ILIntConv**, run all steps of the
build procedure but change the **cmake** generation command on step 3 to one of the
commands available for your favorit IDE.

### Code::Blocks

Platform | Command
-------- | -------
With Ninja | ```$ cmake ../ilintconv -G"CodeBlocks - Ninja" -DCMAKE_BUILD_TYPE=Debug```
With Makefile | ```$ cmake ../ilintconv -G"CodeBlocks - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug```

### Eclipse

In order to create the **Eclipse CDT** project, create a directory called **build**
side by side of the directory **src**. Go to this directory and run the command:

Platform | Command
-------- | -------
Neon with Ninja | ```cmake ../ilintconv -G"Eclipse CDT4 - Ninja" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_ECLIPSE_VERSION=4.6```
Neon with Makefile | ```cmake ../ilintconv -G"Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_ECLIPSE_VERSION=4.6```
Oxygen with Ninja | ```cmake ../ilintconv -G"Eclipse CDT4 - Ninja" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_ECLIPSE_VERSION=4.7```
Oxygen with Makefile | ```cmake ../ilintconv -G"Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_ECLIPSE_VERSION=4.7```

### Microsoft Visual Studio

In order to create the **Microsoft Visual Studio** project, run the command:

```
cmake ../ilintconv -G"Visual Studio 15 2017 Win64"
```
