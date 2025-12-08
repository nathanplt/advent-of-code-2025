#include <iostream>
#include <sstream>
#include <vector>
#include <string>

struct Range {
    long long low{0};
    long long high{0};
};

int count_ids_in_range(const std::vector<long long>& ids, const std::vector<Range>& ranges) {
    int count_in_range = 0;
    for (long long id : ids) {
        for (const Range& r : ranges) {
            if (id >= r.low && id <= r.high) {
                count_in_range++;
                break;
            }
        }
    }
    return count_in_range;
}

int main() {
    std::vector<Range> ranges;
    std::vector<long long> ids;
    std::string token;

    while (std::cin >> token) {
        int dash_index = token.find('-');
        if (dash_index != std::string::npos) {
            std::istringstream ss(token);

            std::string low_str, high_str;
            if (!std::getline(ss, low_str, '-') ||
                !std::getline(ss, high_str)) {
                continue;
            }
        
            ranges.push_back({std::stoll(low_str), std::stoll(high_str)});
        } else {
            ids.push_back(std::stoll(token));
        }
    }

    std::cout << count_ids_in_range(ids, ranges) << '\n';
}

