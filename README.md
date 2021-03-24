# BMPtoASCII

This little project will try to read in `.bmp` files and convert them to lovely ASCII art with the given
set of characters ordered from "fullest" to "empty" (black to white).

The ASCII art is saved externally in a newly generated `output.txt` file in the same location as this program.
Make sure to open the output as UTF-8 or otherwise it may not work.

This will only work for 24 bit bitmap images, so transparency is not allowed for now.
Furthermore, this assumes the origin at the lower left corner of the image which may be changed later on.

---

To use this, simply clone this repository by doing
`git clone https://github.com/xkevio/BMPtoASCII.git`
and then compile the `main.cpp` file with any compiler that supports `#pragma pack`.

For example, if you use `gcc`, compile with the following command: `g++ main.cpp` and you will either get a
`a.exe` or `a.out` file.
Afterwards, you can run the program from the command line and specify the image you want to convert as the first argument, like this:

`a.exe example.bmp`