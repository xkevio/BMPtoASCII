#include <fstream>
#include <iostream>
#include <string>

#include "bmp_file.hpp"

void usage() {
    std::cout << "Usage:\n bmptoascii [filepath] [output (OPTIONAL)]" << std::endl;
}

int main(int argc, char** argv) {
    if (argc <= 1) {
        usage();
        return EXIT_SUCCESS;
    }

    std::string f_name(argv[1]);
    if (f_name.size() <= 4 || f_name.compare(f_name.size() - 4, 4, ".bmp") != 0) {
        std::cerr << f_name << " is not a valid bitmap file!" << std::endl;
        return EXIT_FAILURE;
    }

    BMPFile img(f_name);
    std::string ascii_art = img.convert_to_ascii();

    if (argc >= 3) {
        std::ofstream ofile(argv[2]);
        ofile << ascii_art;

        std::cout << argv[1] << ": " << img.get_width() << "x" << img.get_height() << " with " << img.get_bytes_per_pixel() << " bytes per pixel\n";
        std::cout << "Successfully saved ASCII art in " << argv[2] << "!\n";
    } else {
        std::cout << ascii_art;
    }

    return EXIT_SUCCESS;
}