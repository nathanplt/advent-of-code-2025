#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>

int count_reachable_rolls(const std::vector<std::string>& grid) {
    const int MAX_ADJACENT = 3;
    const int DIRECTIONS = 8;
    static const std::vector<int> dr = {0, 1, 0, -1, 1, 1, -1, -1};
    static const std::vector<int> dc = {1, 0, -1, 0, 1, -1, 1, -1};

    std::size_t n = grid.size();
    std::size_t m = grid[0].size();
    
    int count_reachable = 0;
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            if (grid[r][c] != '@') {
                continue;
            }

            int count_adjacent = 0;
            for (int dir = 0; dir < DIRECTIONS; ++dir) {
                int new_r = r + dr[dir];
                int new_c = c + dc[dir];

                if (new_r < 0 || new_c < 0 || new_r == n || new_c == m) {
                    continue;
                }

                count_adjacent += grid[new_r][new_c] == '@';
            }

            count_reachable += count_adjacent <= MAX_ADJACENT;
        }
    }

    return count_reachable;
}

int main() {
    std::vector<std::string> grid;
    std::string row;

    while (std::cin >> row) {
        grid.push_back(row);
    }
    
    std::cout << count_reachable_rolls(grid);
}

