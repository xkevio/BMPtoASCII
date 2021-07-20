#ifndef BMPFILE_HPP
#define BMPFILE_HPP

#include <fstream>
#include <vector>

#include "BMPHeader.hpp"

class BMPFile {
   private:
    BMPFileHeader file_header;
    BMPInfoHeader info_header;

    std::int32_t width;
    std::int32_t height;
    std::int32_t bytes_per_pixel;

    std::vector<std::uint8_t> pixel_table;
    std::vector<std::uint8_t> grey_values;
    void convert_to_grey();

   public:
    explicit BMPFile(const std::string& file_name);
    void convert_to_ascii(std::ofstream& file);

    [[nodiscard]] std::int32_t get_width() const;
    [[nodiscard]] std::int32_t get_height() const;
    [[nodiscard]] std::int32_t get_bytes_per_pixel() const;
};
#endif