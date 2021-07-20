#include <fstream>
#include <iostream>
#include <string>

#include "BMPFile.hpp"

int main(int argc, char** argv) {
    if (argc <= 1) {
        std::cerr << "Please specify the input file!" << std::endl;
        return EXIT_FAILURE;
    }

    std::string f_name(argv[1]);
    if (f_name.size() <= 4 || !f_name.compare(f_name.size() - 4, 4, ".bmp") == 0) {
        std::cerr << f_name << " is not a valid bitmap file!" << std::endl;
        return EXIT_FAILURE;
    }

    std::ofstream ofile("output.txt");

    BMPFile img(f_name);   
    img.convert_to_ascii(ofile);

    std::cout << argv[1] << ": " << img.get_width() << "x" << img.get_height() << 
                    " with " << img.get_bytes_per_pixel() << " bytes per pixel\n";
    std::cout << "Saved output.txt next to binary\n";

    return EXIT_SUCCESS;
}