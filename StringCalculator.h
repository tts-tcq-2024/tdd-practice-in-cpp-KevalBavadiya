#ifndef STRINGCALCULATOR_H
#define STRINGCALCULATOR_H

#include <string>
#include <vector>

class StringCalculator {
public:
    // Method to add numbers from the input string
    int add(const std::string &numbers);

private:
    // Helper method to split the input string by a delimiter
    std::vector<int> split(const std::string &input, const std::string &delimiter);

    // Helper method to parse a string into an integer and handle ignoring numbers > 1000
    int parseNumber(const std::string &numStr);

    // Method to check for negative numbers and throw an exception if found
    void checkForNegatives(const std::vector<int> &numbers);

    // Method to sum the numbers in the vector
    int sumNumbers(const std::vector<int> &numbers);
};

#endif // STRINGCALCULATOR_H

