#include <iostream>
#include <vector>
#include <string>

long long joltage_of_bank(const std::string& bank) {
    const std::size_t TOTAL_DIGITS = 12;
    std::size_t n = bank.size();

    std::vector<char> curr_digits(TOTAL_DIGITS);
    std::size_t empty_mark = 0;
    for (std::size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < TOTAL_DIGITS; ++j) {
            std::size_t count_after = TOTAL_DIGITS - j - 1;
            if (i >= n - count_after) {
                continue;
            }

            if (j >= empty_mark || curr_digits[j] < bank[i]) {
                curr_digits[j] = bank[i];
                empty_mark = j + 1;
                break;
            }
        }
    } 
    
    long long joltage = 0;
    for (char c : curr_digits) {
        joltage *= 10;
        joltage += c - '0';
    }
    return joltage;
}

int main() {
    long long total_joltage = 0;
    std::string bank_str;

    while (std::cin >> bank_str) {
        total_joltage += joltage_of_bank(bank_str);
    }

    std::cout << total_joltage << '\n';
}

