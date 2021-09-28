#include "BMPFile.hpp"

#include <array>
#include <cmath>
#include <fstream>

constexpr std::array<char, 10> char_map{'@', '#', '%', 'x', 'o', ';', ':', ',', '.', ' '};

BMPFile::BMPFile(const std::string& file_name) {
    std::ifstream file(file_name, std::ifstream::binary);

    file.read(reinterpret_cast<char*>(&file_header), sizeof(file_header));
    file.read(reinterpret_cast<char*>(&info_header), sizeof(info_header));

    height = info_header.height;
    width = info_header.width;
    bytes_per_pixel = info_header.bits_per_pixel / 8;

    pixel_table.resize(width * height * bytes_per_pixel);
    file.seekg(file_header.data_offset, std::ifstream::beg);

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
}

void BMPFile::convert_to_gray() {
    gray_values.reserve(width * height);

    for (auto i = height - 1; i >= 0; --i) {
        for (auto j = 0; j < width * bytes_per_pixel; j += 3) {
            std::int32_t index = (i * width * bytes_per_pixel) + j;
            float g = 0.299f * pixel_table[index + 2] + 0.587f * pixel_table[index + 1] + 0.114f * pixel_table[index];
            gray_values.push_back(std::round(g));
        }
    }
}

std::string BMPFile::convert_to_ascii() {
    convert_to_gray();
    std::string ascii_string;

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            ascii_string += char_map[std::round(gray_values[(i * width) + j] / 255.0f * 9)];
            ascii_string += " ";
        }
        ascii_string += "\n";
    }

    return ascii_string;
}

[[nodiscard]] std::int32_t BMPFile::get_width() const {
    return width;
}

[[nodiscard]] std::int32_t BMPFile::get_height() const {
    return height;
}

[[nodiscard]] std::int32_t BMPFile::get_bytes_per_pixel() const {
    return bytes_per_pixel;
}
