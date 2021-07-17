#include "Console.h"

#include <iostream>
#include <Windows.h>

void Console::WriteLine(std::string_view message) noexcept {
	Write(message);
	Write("\n");
}

void Console::Write(std::string_view message) noexcept {
	std::cout << message;
}

void Console::SetTextColor(ConsoleColor clr) noexcept {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(clr));
}
