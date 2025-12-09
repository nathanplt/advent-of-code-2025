#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <string>

class DSU {
public:
    DSU (int n_) : n(n_) {
        size.resize(n, 1);
        parent.resize(n);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int find(int x) {
        return x == parent[x] ? x : parent[x] = find(parent[x]);
    }

    bool unite(int x, int y) {
        x = find(x);
        y = find(y);

        if (x == y) {
            return false;
        }
        if (size[x] < size[y]) {
            std::swap(x, y);
        }
        
        parent[y] = x;
        size[x] += size[y];
        return true;
    }

private:
    int n{0};
    std::vector<int> parent{};
    std::vector<int> size{};
};

struct Coord {
    long long x{0}, y{0}, z{0};
};

struct Edge {
    long long a{0}, b{0}, weight{0};
};


long long sum_last_two_boxes(const std::vector<Coord>& coordinates) {
    int n = static_cast<int>(coordinates.size());

    std::vector<Edge> edges;
    for (int i = 0; i < n - 1; ++i) {
        const Coord& a = coordinates[i];

        for (int j = i + 1; j < n; ++j) {
            const Coord& b = coordinates[j];

            long long x_dist = (a.x - b.x) * (a.x - b.x);
            long long y_dist = (a.y - b.y) * (a.y - b.y);
            long long z_dist = (a.z - b.z) * (a.z - b.z);

            edges.push_back({i, j, x_dist + y_dist + z_dist});
        }
    }

    std::sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
    });

    int m = static_cast<int>(edges.size());
    DSU graph(n);
    int components = n;

    long long product_last_two = 0;
    for (int i = 0; i < m && components > 1; ++i) {
        int a = edges[i].a, b = edges[i].b;

        if (graph.unite(a, b)) {
            components--;
        }

        product_last_two = coordinates[a].x * coordinates[b].x;
    }

    return product_last_two;
}

int main() {
    std::vector<Coord> coordinates;

    std::string line;
    while (std::getline(std::cin, line)) {
        std::istringstream ss(line);

        std::string x_str, y_str, z_str;
        if (!std::getline(ss, x_str, ',') ||
            !std::getline(ss, y_str, ',') ||
            !std::getline(ss, z_str))
            continue;
        
        long long x = std::stoll(x_str);
        long long y = std::stoll(y_str);
        long long z = std::stoll(z_str);
        coordinates.push_back({x, y, z});
    }

    std::cout << sum_last_two_boxes(coordinates) << '\n';
}

