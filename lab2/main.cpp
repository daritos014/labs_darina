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
        long long x = number;      // копия числа, чтобы не менять введённое
        int sum = 0;               // сумма цифр
        int minDigit = 10;         // пока больше любой цифры
        int maxDigit = -1;         // пока меньше любой цифры
        std::cout << "Разложение на цифры в обратном порядке:";  // начиная с последней
        while (x != 0) {
            int digit = x % 10;      // берём последнюю цифру
            std::cout << ' ' << digit;
            sum = sum + digit;       // добавляем цифру к сумме
            if (digit < minDigit) minDigit = digit;  // запоминаем минимум
            if (digit > maxDigit) maxDigit = digit;  // запоминаем максимум
            x = x / 10;              // отбрасываем последнюю цифру
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
