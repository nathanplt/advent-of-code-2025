#include <iostream>
#include <sstream>
#include <vector>
#include <string>

struct Range {
    long long low{0};
    long long high{0};
};

bool is_invalid_id(long long id) {
    std::string id_str = std::to_string(id);
    size_t n = id_str.size();
    if (n % 2 != 0) {
        return false;
    }

    for (size_t i = 0; i < n / 2; ++i) {
        if (id_str[i] != id_str[i + n / 2]) {
            return false;
        }
    }
    return true;
}

long long sum_invalid_ids(const std::vector<Range>& ranges) {
    long long sum_invalid = 0;
    for (const auto& [low, high] : ranges) {
        for (long long curr = low; curr <= high; ++curr) {
            if (is_invalid_id(curr)) {
                sum_invalid += curr;
            }
        }
    }
    return sum_invalid;
}

int main() {
    std::vector<Range> ranges;
    std::string range_str;
    while (std::getline(std::cin, range_str, ',')) {
        std::istringstream ss(range_str);
        std::string low_str, high_str;
        if (!std::getline(ss, low_str, '-') ||
            !std::getline(ss, high_str)) {
            std::cerr << "Error parsing " << range_str;
            continue;
        }
        ranges.push_back({std::stoll(low_str), std::stoll(high_str)});
    }
    std::cout << sum_invalid_ids(ranges) << '\n';
}

