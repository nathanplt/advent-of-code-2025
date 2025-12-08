#include <iostream>
#include <sstream>
#include <vector>
#include <string>

struct Range {
    long long low{0};
    long long high{0};
};

bool is_repeated_pattern(const std::string& s, const std::string& p) {
    std::size_t n = s.size();
    std::size_t m = p.size();
    for (std::size_t i = 0; i < n; i += m) {
        if (s.substr(i, m) != p) {
            return false;
        }
    }
    return true;
}

bool is_invalid_id(long long id) {
    std::string id_str = std::to_string(id);
    std::size_t n = id_str.size();
    for (std::size_t len = 1; len <= n / 2; ++len) {
        if (n % len != 0) {
            continue;
        }

        std::string pattern = id_str.substr(0, len);
        if (is_repeated_pattern(id_str, pattern)) {
            return true;
        }
    }
    return false;
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

