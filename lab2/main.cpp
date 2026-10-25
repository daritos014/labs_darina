// lab2 - Условия и циклы: простота, цифры числа, минимум и максимум.

#include <iostream>
#include <sstream>
#include <string>

#ifdef _WIN32
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

bool isPrime(long long n) {
    if (n < 2) return false;
    for (long long d = 2; d * d <= n; ++d)
        if (n % d == 0) return false;
    return true;
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    // 1. Простота числа
    long long n;
    std::cout << "1) Проверка на простоту. Число: ";
    std::cin >> n;
    std::cout << n << (isPrime(n) ? " — простое\n" : " — не простое\n");

    // 2. Разложение на цифры
    long long number;
    std::cout << "\n2) Разложение на цифры. Натуральное число: ";
    std::cin >> number;
    if (number <= 0) {
        std::cout << "Нужно число больше 0\n";
    } else {
        std::string s = std::to_string(number);
        int sum = 0, minDigit = 9, maxDigit = 0;
        std::cout << "Цифры:";
        for (char c : s) {
            int d = c - '0';
            std::cout << ' ' << d;
            sum += d;
            if (d < minDigit) minDigit = d;
            if (d > maxDigit) maxDigit = d;
        }
        std::cout << "\nСумма: " << sum << ", минимум: " << minDigit
                  << ", максимум: " << maxDigit << '\n';
    }

    // 3. Минимум и максимум последовательности
    std::cout << "\n3) Введите последовательность целых чисел через пробел: ";
    std::string line;
    std::getline(std::cin >> std::ws, line);  // читаем всю строку до Enter
    std::istringstream stream(line);          // разбираем числа из строки

    long long value, minValue = 0, maxValue = 0;
    int count = 0;
    while (stream >> value) {
        if (count == 0 || value < minValue) minValue = value;
        if (count == 0 || value > maxValue) maxValue = value;
        ++count;
    }
    if (count > 0)
        std::cout << "Минимум: " << minValue << ", максимум: " << maxValue << '\n';
    else
        std::cout << "Нужно хотя бы одно число\n";

    return 0;
}
