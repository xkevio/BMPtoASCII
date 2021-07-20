#ifndef BMPHEADER_HPP
#define BMPHEADER_HPP

#include <cstdint>

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

#endif