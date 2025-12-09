#include <iostream>
#include <algorithm>
#include <sstream>
#include <unordered_set>
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

    std::tuple<int, int, int> get_top_3_sizes() {
        std::unordered_set<int> roots;
        for (int i = 0; i < n; ++i) {
            roots.insert(find(i));
        }

        int first_max = 1, second_max = 1, third_max = 1;
        for (int x : roots) {
            if (size[x] > first_max) {
                third_max = second_max;
                second_max = first_max;
                first_max = size[x];
            } else if (size[x] > second_max) {
                third_max = second_max;
                second_max = size[x];
            } else if (size[x] > third_max) {
                third_max = size[x];
            }
        } 

        return {first_max, second_max, third_max};
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


int sum_three_largest_circuits(const std::vector<Coord>& coordinates,
                                     int num_wires) {
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

    DSU graph(n);
    for (int i = 0; i < num_wires; ++i) {
        graph.unite(edges[i].a, edges[i].b);        
    }

    auto [first_max, second_max, third_max] = graph.get_top_3_sizes();
    return first_max * second_max * third_max;
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

    std::cout << sum_three_largest_circuits(coordinates, 1000) << '\n';
}

