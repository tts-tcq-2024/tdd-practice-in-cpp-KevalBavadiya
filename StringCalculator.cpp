#include "StringCalculator.h"
#include <sstream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <numeric>

int StringCalculator::add(const std::string &numbers) {
    if (numbers.empty()) {
        return 0;
    }

    std::string delimiter = ",";
    std::string numString = numbers;

    // Check for custom delimiter
    if (numbers.rfind("//", 0) == 0) {
        size_t delimiter_end = numbers.find("\n");
        delimiter = numbers.substr(2, delimiter_end - 2);
        numString = numbers.substr(delimiter_end + 1);
    }

    // Replace newline with the delimiter
    std::replace(numString.begin(), numString.end(), '\n', delimiter[0]);

    std::vector<int> nums = split(numString, delimiter);
    checkForNegatives(nums);

    return sumNumbers(nums);
}

std::vector<int> StringCalculator::split(const std::string &input, const std::string &delimiter) {
    std::vector<int> numbers;
    size_t start = 0;
    size_t end = input.find(delimiter);

    while (end != std::string::npos) {
        numbers.push_back(parseNumber(input.substr(start, end - start)));
        start = end + delimiter.length();
        end = input.find(delimiter, start);
    }

    numbers.push_back(parseNumber(input.substr(start)));
    return numbers;
}

int StringCalculator::parseNumber(const std::string &numStr) {
    int num = std::stoi(numStr);
    return (num > 1000) ? 0 : num;
}

std::string buildNegativeExceptionMessage(const std::vector<int>& negatives) {
    std::stringstream ss;
    ss << "negatives not allowed: ";
    for (size_t i = 0; i < negatives.size(); ++i) {
        if (i != 0) ss << ", ";
        ss << negatives[i];
    }
    return ss.str();
}

void StringCalculator::checkForNegatives(const std::vector<int> &numbers) {
    std::vector<int> negatives;
    std::copy_if(numbers.begin(), numbers.end(), std::back_inserter(negatives), [](int n) { return n < 0; });

    if (!negatives.empty()) {
        throw std::runtime_error(buildNegativeExceptionMessage(negatives));
    }
}

int StringCalculator::sumNumbers(const std::vector<int> &numbers) {
    return std::accumulate(numbers.begin(), numbers.end(), 0);
}
