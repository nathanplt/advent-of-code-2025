#include <iostream>
#include <sstream>
#include <vector>
#include <string>

long long evaluate_problems(const std::vector<std::string>& problem_lines,
                            const std::vector<std::string>& ops) {
    std::size_t max_width = 0;
    for (const std::string& line : problem_lines) {
        max_width = std::max(max_width, line.size());
    }

    long long sum_answers = 0;
    long long curr_answer = ops[0] == "+" ? 0 : 1;

    std::size_t problem_index = 0;
    bool in_problem = true;
    for (std::size_t i = 0; i < max_width; ++i) {
        long long operand = 0;
        bool digit_seen = false;

        for (const std::string& line : problem_lines ){
            if (i >= line.size() || line[i] == ' ') {
                continue;
            }
            operand *= 10;
            operand += line[i] - '0';
            digit_seen = true;
        }

        if (!digit_seen) {
            if (in_problem) {
                sum_answers += curr_answer;
                problem_index++;
                in_problem = false;
            }
            continue;
        }

        if (!in_problem) {
            curr_answer = ops[problem_index] == "+" ? 0 : 1;
            in_problem = true;
        }

        if (ops[problem_index] == "+") {
            curr_answer += operand;
        } else {
            curr_answer *= operand;
        }
    }
    sum_answers += curr_answer;

    return sum_answers;
}

int main() {
    std::vector<std::string> problem_lines;
    std::vector<std::string> ops;

    std::string line;
    while (std::getline(std::cin, line)) {
        std::size_t add_index = line.find('+');
        std::size_t multiply_index = line.find('*');

        if (add_index != std::string::npos ||
            multiply_index != std::string::npos) {
            std::istringstream ss(line);

            std::string token;
            while (ss >> token) {
                ops.push_back(token);
            }
        } else {
            problem_lines.push_back(line);
        }
    }

    std::cout << evaluate_problems(problem_lines, ops) << '\n';
}

