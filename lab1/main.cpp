// lab1 - Типы данных в C++: размеры, диапазоны значений и примеры операций.

#include <iostream>
#include <iomanip>
#include <limits>
#include <string>

#ifdef _WIN32
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

// Печатает целочисленный тип: имя, размер в байтах и диапазон значений.
// Унарный "+" превращает char/bool в int, чтобы они печатались как числа.
template <typename T>
void showInteger(const std::string& name) {
    std::cout << std::left << std::setw(20) << name
              << sizeof(T) << " байт, диапазон: "
              << +std::numeric_limits<T>::min() << " .. "
              << +std::numeric_limits<T>::max() << '\n';
}

// Печатает вещественный тип.
template <typename T>
void showFloat(const std::string& name) {
    std::cout << std::left << std::setw(20) << name
              << sizeof(T) << " байт, диапазон: "
              << std::numeric_limits<T>::lowest() << " .. "
              << std::numeric_limits<T>::max() << '\n';
}

int main() {
#ifdef _WIN32
    // Чтобы кириллица в консоли Windows выводилась правильно (без «кракозябр»).
    SetConsoleOutputCP(CP_UTF8);
#endif

    std::cout << "Типы данных:\n";
    showInteger<bool>("bool");
    showInteger<char>("char");
    showInteger<short>("short");
    showInteger<int>("int");
    showInteger<long>("long");
    showInteger<long long>("long long");
    showInteger<unsigned int>("unsigned int");
    showInteger<unsigned long long>("unsigned long long");
    showFloat<float>("float");
    showFloat<double>("double");

    std::cout << "\nДеление:\n";
    std::cout << "7 / 2   = " << 7 / 2 << "   (целочисленное, дробная часть отбрасывается)\n";
    std::cout << "7 % 2   = " << 7 % 2 << "     (остаток от деления)\n";
    std::cout << "7 / 2.0 = " << 7 / 2.0 << " (вещественное)\n";

    std::cout << "\nПереполнение:\n";
    unsigned int u = std::numeric_limits<unsigned int>::max();
    std::cout << "UINT_MAX + 1 = " << u + 1 << " (беззнаковое: заворот по модулю)\n";
    int i = std::numeric_limits<int>::max();
    std::cout << "INT_MAX + 1  = " << i + 1 << " (знаковое: неопределённое поведение)\n";

    return 0;
}
