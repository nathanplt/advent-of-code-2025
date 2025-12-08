i#include <iostream>
#include <sstream>
#include <vector>
#include <string>

long long evaluate_problems(const std::vector<std::vector<long long>>& problems,
                       const std::vector<std::string>& ops) {
    long long sum_answers = 0;
    for (size_t i = 0; i < problems.size(); ++i) {
        long long curr_answer = ops[i] == "+" ? 0 : 1;

        for (long long x : problems[i]) {
            if (ops[i] == "+") {
                curr_answer += x;
            } else {
                curr_answer *= x;
            }
        }

        sum_answers += curr_answer;
    }
    return sum_answers;
}

int main() {
    std::vector<std::vector<long long>> problems;
    std::vector<std::string> ops;

    std::string line;
    while (std::getline(std::cin, line)) {
        std::istringstream ss(line);

        std::size_t index = 0;
        std::string token;
        while (ss >> token) {
            if (token == "+" || token == "*") {
                ops.push_back(token);
            } else {
                if (index == problems.size()) {
                    problems.push_back({});
                }
                problems[index].push_back(std::stoll(token));
            }
            index++;
        }
    }

    std::cout << evaluate_problems(problems, ops) << '\n';
}

