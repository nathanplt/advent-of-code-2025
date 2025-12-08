#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <string>

struct Range {
    long long low{0};
    long long high{0};
};

long long count_ids_in_ranges(std::vector<Range> ranges) {
    std::sort(ranges.begin(), ranges.end(), [](const Range& a, const Range& b) {
        return a.low < b.low;
    });

    long long count_unique_ids = 0;
    long long curr_low = ranges[0].low, curr_high = ranges[0].high;
    for (const Range& r : ranges) {
        if (r.low > curr_high) {
            count_unique_ids += curr_high - curr_low + 1;
            curr_low = r.low;
            curr_high = r.high;
        } else {
            curr_high = std::max(curr_high, r.high);
        }
    }
    count_unique_ids += curr_high - curr_low + 1;

    return count_unique_ids;
}

int main() {
    std::vector<Range> ranges;
    std::string token;

    while (std::cin >> token) {
        std::istringstream ss(token);

        std::string low_str, high_str;
        if (!std::getline(ss, low_str, '-') ||
            !std::getline(ss, high_str)) {
            continue;
        }
    
        ranges.push_back({std::stoll(low_str), std::stoll(high_str)});
    }

    std::cout << count_ids_in_ranges(ranges) << '\n';
}

