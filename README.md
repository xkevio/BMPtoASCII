![GitHub](https://img.shields.io/github/license/xkevio/BMPtoASCII) ![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/xkevio/BMPtoASCII)
# BMPtoASCII

This little project will try to read in `.bmp` files and convert them to lovely ASCII art with the given
set of characters ordered from "fullest" to "empty" (black to white).

The ASCII art is saved externally in a newly generated `output.txt` file in the same location as this program.
Make sure to open the output as UTF-8 or otherwise it may not work.

This will only work for 24 bit bitmap images, so transparency is not allowed for now.
Furthermore, this assumes the origin at the lower left corner of the image which may be changed later on.

## Usage

To use this, simply clone this repository by doing
`git clone https://github.com/xkevio/BMPtoASCII.git`
and then compile the project with any compiler that supports `#pragma pack`.

### With CMake
First, create a `build` folder in the project in which the binary will go.
Then, head into that directory and type `cmake ..`.
To finally build the binary, type `make`.

### Compiling manually
If you do not use CMake or do not wish to install it, you can also compile this project manually with
your favorite compiler. With `gcc` it could look like this for example:
`g++ -o BMPtoASCII main.cpp BMPFile.cpp`

Now you can use the project by simply typing
`BMPtoASCII[.exe] img.bmp` in your terminal.
