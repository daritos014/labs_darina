// lab3 - массивы: сортировки, матрица, удаление и дублирование чисел.
#include <algorithm>
#include <iostream>
#include <vector>
#ifdef _WIN32
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

// Сумма цифр числа: 123 -> 1 + 2 + 3 = 6.
int digitSum(long long number) {
    int sum = 0;
    while (number > 0) {
        sum += int(number % 10); // добавляем последнюю цифру
        number /= 10;            // убираем последнюю цифру
    }
    return sum;
}

// Наименьшая цифра числа: 583 -> 3.
int minDigit(long long number) {
    int minimum = 10; // 10 больше любой цифры
    while (number > 0) {
        int digit = int(number % 10);
        if (digit < minimum) minimum = digit;
        number /= 10;
    }
    return minimum;
}

// true, если все цифры числа одинаковые: 111 -> true, 121 -> false.
bool sameDigits(long long number) {
    int firstDigit = int(number % 10);
    while (number > 0) {
        if (int(number % 10) != firstDigit) return false;
        number /= 10;
    }
    return true;
}

// true, если в числе есть повторяющиеся цифры: 121 -> true, 123 -> false.
bool repDigits(long long number) {
    int counts[10] = {}; // counts[d] — сколько раз встретилась цифра d
    while (number > 0) {
        int digit = int(number % 10);
        ++counts[digit];
        number /= 10;
    }
    for (int digit = 0; digit < 10; ++digit) {
        if (counts[digit] > 1) return true;
    }
    return false;
}

// Читает n чисел с клавиатуры и возвращает их в векторе.
std::vector<long long> read(int n) {
    std::vector<long long> numbers(n);
    for (auto& value : numbers) {
        std::cin >> value;
    }
    return numbers;
}

// Печатает подпись и числа через пробел.
void print(const std::vector<long long>& numbers, const char* label) {
    std::cout << label;
    for (size_t i = 0; i < numbers.size(); ++i) {
        if (i > 0) std::cout << ' ';
        std::cout << numbers[i];
    }
    std::cout << '\n';
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8); // корректная кириллица в консоли Windows
#endif
    int n;
    std::cout << "n — это количество чисел, которые нужно ввести.\n";

    // 1) Если чисел с одинаковыми цифрами не меньше трёх, отсортировать всё по убыванию.
    std::cout << "\n1) Сортировка чисел с одинаковыми цифрами. Сколько чисел ввести? n (от 1 до 10000): ";
    std::cin >> n;
    if (n <= 0) std::cout << "Ошибка: n должно быть больше 0.\n";
    else {
        std::cout << "Введите числа (всего " << n << ") через пробел: ";
        auto a = read(n);
        auto k = std::count_if(a.begin(), a.end(), sameDigits);
        std::cout << "Чисел с одинаковыми цифрами: " << k << ".\n";
        if (k >= 3) std::sort(a.begin(), a.end(), std::greater<long long>());
        print(a, k >= 3 ? "Результат по убыванию: " : "Порядок не изменён: ");
    }
    // 2) Сортировка по сумме цифр, затем по наименьшей цифре, затем по значению.
    std::cout << "\n2) Сортировка по сумме цифр. Сколько чисел ввести? n (от 1 до 1000): ";
    std::cin >> n;
    if (n <= 0) std::cout << "Ошибка: n должно быть больше 0.\n";
    else {
        std::cout << "Введите числа (всего " << n << ") через пробел: ";
        auto a = read(n);
        std::sort(a.begin(), a.end(), [](long long x, long long y) {
            int sx = digitSum(x), sy = digitSum(y); if (sx != sy) return sx < sy;
            int mx = minDigit(x), my = minDigit(y); if (mx != my) return mx < my;
            return x < y; });
        print(a, "Результат: ");
    }
    // 3) Столбец матрицы с наибольшим произведением элементов уменьшить на 3.
    int m;
    std::cout << "\n3) В матрице найти столбец с наибольшим произведением элементов и уменьшить его на 3.\n"
                 "Введите количество строк n и столбцов m (каждое от 1 до 100): ";
    std::cin >> n >> m;
    if (n <= 0 || m <= 0) std::cout << "Ошибка: n и m должны быть больше 0.\n";
    else {
        std::vector<std::vector<long long>> A(n, std::vector<long long>(m));
        std::cout << "Введите элементы матрицы (всего " << n * m << ", по " << m << " в строке): ";
        for (auto& r : A) for (auto& v : r) std::cin >> v;
        int bc = 0; long double bp = 0; // произведение в long double — без переполнения
        for (int j = 0; j < m; ++j) { long double p = 1; for (int i = 0; i < n; ++i) p *= A[i][j]; if (j == 0 || p > bp) { bp = p; bc = j; } }
        for (auto& r : A) r[bc] -= 3;
        std::cout << "Столбец " << bc + 1 << " (произведение " << double(bp) << ") уменьшен на 3:\n";
        for (auto& r : A) { std::cout << "  "; for (int j = 0; j < m; ++j) std::cout << (j ? " " : "") << r[j]; std::cout << "\n"; }
    }
    // 4) Удалить числа с суммой цифр, кратной 7, затем продублировать числа с повторяющимися цифрами.
    std::cout << "\n4) Удаление и дублирование чисел. Сколько чисел ввести? n (от 1 до 10000): ";
    std::cin >> n;
    if (n <= 0) std::cout << "Ошибка: n должно быть больше 0.\n";
    else {
        std::vector<long long> a(2 * n);
        std::cout << "Введите числа (всего " << n << ") через пробел: ";
        for (int i = 0; i < n; ++i) std::cin >> a[i];
        int c = 0; for (int i = 0; i < n; ++i) if (digitSum(a[i]) % 7) a[c++] = a[i]; // сжатие на месте
        int o = 2 * c; // пишем результат с конца, чтобы не затереть непрочитанное
        for (int i = c - 1; i >= 0; --i) { long long v = a[i]; if (repDigits(v)) { a[--o] = v; a[--o] = v; } else a[--o] = v; }
        std::cout << "Результат:"; for (int i = o; i < 2 * c; ++i) std::cout << " " << a[i]; std::cout << "\n";
    }
    return 0;
}
