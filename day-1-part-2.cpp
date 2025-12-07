#include <iostream>
#include <string>

int count_dial_touches_zero() {
    const int full_cycle = 100;
    const int start = 50;
    
    int count_zero = 0;
    int curr_dial = start;
    std::string rotation;
    while (std::cin >> rotation) {
        char dir = rotation[0];
        int ticks = std::stoi(rotation.substr(1));

        int prev_dial = curr_dial;
        int net_diff = ticks % full_cycle;
        int count_full_cycles = ticks / full_cycle;

        if (dir == 'L') {
            curr_dial -= net_diff;
            if (curr_dial <= 0 && prev_dial > 0) {
                count_zero++;
            }
            if (curr_dial < 0) {
                curr_dial += full_cycle;
            }
        } else if (dir == 'R') {
            curr_dial += net_diff;
            if (curr_dial >= full_cycle) {
                curr_dial -= full_cycle;
                count_zero++;
            }
        } else {
            throw std::invalid_argument("Input has invalid direction");
        }
        count_zero += count_full_cycles;
    }
    return count_zero;
}

int main() {
    std::cout << count_dial_touches_zero() << '\n';
}

