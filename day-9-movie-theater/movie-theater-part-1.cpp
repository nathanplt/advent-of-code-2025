#include <iostream>
#include <sstream>
#include <vector>
#include <string>

struct Coord {
    long long x{0}, y{0};
};

long long area_of_largest_rectangle(const std::vector<Coord>& coordinates) {
    int n = static_cast<int>(coordinates.size());

    long long max_area = 0;
    for (int i = 0; i < n - 1; ++i) {
        const Coord& a = coordinates[i];

        for (int j = i + 1; j < n; ++j) {
            const Coord& b = coordinates[j];

            long long height = std::abs(a.y - b.y) + 1;
            long long width = std::abs(a.x - b.x) + 1;

            max_area = std::max(max_area, height * width);
        }
    }

    return max_area;
}

int main() {
    std::vector<Coord> coordinates;

    std::string line;
    while (std::getline(std::cin, line)) {
        std::istringstream ss(line);

        std::string x_str, y_str;
        if (!std::getline(ss, x_str, ',') ||
            !std::getline(ss, y_str))
            continue;

        coordinates.push_back({std::stoll(x_str), std::stoll(y_str)});
    }

    std::cout << area_of_largest_rectangle(coordinates) << '\n';
}

