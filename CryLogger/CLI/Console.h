#pragma once
#include <cstdint>
#include <string>

enum class ConsoleColor : std::uint16_t {
    Red    = (0x0004 | 0x0008),
    Green  = (0x0002 | 0x0008),
    Yellow = (0x0004 | 0x0002 | 0x0008),
    White  = (0x0004 | 0x0002 | 0x0001),
};

class Console {
public:
    static void WriteLine(std::string_view message) noexcept;
    static void Write(std::string_view message) noexcept;
    static void SetTextColor(ConsoleColor clr) noexcept;
};