#include <array>
#include <cmath>
#include <cstdint>

namespace conversion {
    constexpr std::array<char, 10> char_map{'@', '#', '%', 'x', 'o', ';', ':', ',', '.', ' '};

    // r, g, b should be between 0 and 255
    [[nodiscard]] std::uint8_t convert_rgb_to_gray(std::uint8_t r, std::uint8_t g, std::uint8_t b) {
        float gray_value = 0.299f * r + 0.587f * g + 0.114f * b;
        return std::round(gray_value);
    }

    [[nodiscard]] char value_to_symbol(std::uint8_t gray_value) {
        return char_map[std::round(gray_value / 255.0f * 9)];
    }
}