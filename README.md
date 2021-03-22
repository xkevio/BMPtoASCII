# BMPtoASCII

This little project will try to read in `.bmp` files and convert them to lovely ASCII art with the given
set of characters ordered from "fullest" to "empty" (black to white).

This will only work for 24 bit bitmap images, so transparency is not allowed for now.
Furthermore, this assumes the origin at the lower left corner of the image which may be changed later on.

---

To use this, simply clone this repository by doing
`git clone https://github.com/xkevio/BMPtoASCII.git`
and then compile the `main.cpp` file with any compiler that supports `#pragma pack`.
Afterwards, you can run the program from the command line and specify the image you want to convert as the first argument.