#include <iostream>
#include <vector>
#include <string>
#include <queue>

struct Beam {
    int row{0};
    int column{0};
};

long long count_all_timelines(const std::vector<std::string>& grid){
    const char START_CHAR = 'S';
    const char SPLIT_CHAR = '^';

    std::size_t n = grid.size();
    std::size_t m = grid[0].size();

    std::queue<Beam> q;
    std::vector<std::vector<long long>> timelines(n, std::vector<long long>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == START_CHAR) {
                timelines[i][j] = 1;
                q.push({i, j});
                break;
            }
        }
    }

    std::vector<std::vector<bool>> visited(n, std::vector<bool>(m));
    long long total_timelines = 0;

    while (!q.empty()) {
        auto [row, column] = q.front();
        q.pop();

        if (visited[row][column]) {
            continue;
        }
        visited[row][column] = true;

        if (row + 1 == n) {
            total_timelines += timelines[row][column];
            continue;
        }
    
        char next_cell = grid[row + 1][column];
        if (next_cell == SPLIT_CHAR) {
            if (column > 0) {
                timelines[row + 1][column - 1] += timelines[row][column];
                q.push({row + 1, column - 1});
            }
            if (column < m - 1) {
                timelines[row + 1][column + 1] += timelines[row][column];
                q.push({row + 1, column + 1});
            }
        } else {
            timelines[row + 1][column] += timelines[row][column];
            q.push({row + 1, column});
        }
    }

    return total_timelines;
}

int main() {
    std::vector<std::string> grid;
    std::string line;

    while (std::cin >> line) {
        grid.push_back(line);
    }

    std::cout << count_all_timelines(grid) << '\n';
}

