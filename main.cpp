#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

constexpr int cm_size = 10;

#pragma pack(push, 1)
struct BMPFileHeader {
    std::uint16_t file_type{0x4D42};
    std::uint32_t file_size{0};
    std::uint16_t reserved1{0};
    std::uint16_t reserved2{0};
    std::uint32_t data_offset{0};
};

struct BMPInfoHeader {
    std::uint32_t size{0};
    std::int32_t width{0};
    std::int32_t height{0};

    std::uint16_t planes{1};
    std::uint16_t bits_per_pixel{0};
    std::uint32_t compression{0};
    std::uint32_t size_image{0};

    std::int32_t x_ppm{0};
    std::int32_t y_ppm{0};
    std::uint32_t colors_used{0};
    std::uint32_t colors_important{0};
};
#pragma pack(pop)

std::vector<std::uint8_t> get_pixel_table(std::ifstream& file, std::int32_t& height, std::int32_t& width, std::int32_t& bytes_per_pixel) {
    BMPFileHeader file_header;
    BMPInfoHeader info_header;

    std::vector<std::uint8_t> pixel_table;

    file.read(reinterpret_cast<char*>(&file_header), sizeof(file_header));
    file.read(reinterpret_cast<char*>(&info_header), sizeof(info_header));

    height = info_header.height;
    width = info_header.width;
    bytes_per_pixel = info_header.bits_per_pixel / 8;

    pixel_table.resize(width * height * bytes_per_pixel);
    file.seekg(file_header.data_offset, file.beg);

    if (width % 4 == 0) {
        file.read(reinterpret_cast<char*>(pixel_table.data()), pixel_table.size());
    } else {
        auto row_stride = width * bytes_per_pixel;
        auto new_stride = row_stride;
        while (new_stride % 4 != 0) new_stride++;

        std::vector<std::uint8_t> padding_rows(new_stride - row_stride);
        for (int y = 0; y < height; ++y) {
            file.read(reinterpret_cast<char*>(pixel_table.data() + (y * row_stride)), row_stride);
            file.read(reinterpret_cast<char*>(padding_rows.data()), padding_rows.size());
        }
    }

    return pixel_table;
}

void convert_to_ascii(std::ofstream& file, const std::vector<std::uint8_t>& grey_values, std::int32_t width, std::int32_t height) {
    std::array<char, cm_size> char_map{'@', '#', '%', 'x', 'o', ';', ':', ',', '.', ' '};
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            file << char_map[static_cast<int>(grey_values[(i * width) + j] / 255.0f * (cm_size - 1))] << " ";
        }
        file << "\n";
    }
}

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

    std::ifstream file(argv[1], std::ifstream::binary);
    std::ofstream ofile("output.txt");

    std::int32_t width;
    std::int32_t height;
    std::int32_t bytes_per_pixel;

    auto pixel_table = get_pixel_table(file, height, width, bytes_per_pixel);
    assert(!pixel_table.empty());
    if (bytes_per_pixel != 3) {
        std::cerr << "Only support for 24 bit bitmap files!" << std::endl;
        return EXIT_FAILURE;
    }

    std::vector<std::uint8_t> grey_values(width * height);

    std::cout << argv[1] << ": " << width << "x" << height << " with " << bytes_per_pixel << " bytes per pixel" << std::endl;

    for (int i = height - 1; i >= 0; i--) {
        for (int j = 0; j < width * bytes_per_pixel; j += 3) {
            int index = (i * width * bytes_per_pixel) + j;

            float g = 0.299f * pixel_table[index + 2] + 0.587f * pixel_table[index + 1] + 0.114f * pixel_table[index];
            grey_values.push_back(std::round(g));
        }
    }
    convert_to_ascii(ofile, grey_values, width, height);

    ofile.close();
    file.close();
    return EXIT_SUCCESS;
}