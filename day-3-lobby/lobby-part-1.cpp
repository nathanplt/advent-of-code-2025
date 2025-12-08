#include <iostream>
#include <string>

int joltage_of_bank(const std::string& digits) {
    const char EMPTY = '.';
    std::size_t n = digits.size();

    char first_digit = digits[0];
    char second_digit = EMPTY;
    for (std::size_t i = 1; i < n; ++i) {
        if (i < n - 1 && digits[i] > first_digit) {
            first_digit = digits[i];
            second_digit = EMPTY;
        } else if (second_digit == EMPTY || digits[i] > second_digit) {
            second_digit = digits[i];
        }
    }

    return (first_digit - '0') * 10 + (second_digit - '0');
}

int main() {
    long long total_joltage = 0;
    std::string digits_str;

    while (std::cin >> digits_str) {
        total_joltage += joltage_of_bank(digits_str);
    }
    
    std::cout << total_joltage << '\n';
}

