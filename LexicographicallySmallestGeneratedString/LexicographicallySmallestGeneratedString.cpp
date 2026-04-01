#include <iostream>

#include "Solution.h"

int main()
{
    Solution solution;
    std::string str1 = "TFTF";
    std::string str2 = "ab";
    std::string result = solution.generateString(str1, str2);
    std::cout << "Result: " << result << std::endl;

    str1 = "TTFFT";
    str2 = "fff";
    result = solution.generateString(str1, str2);
    std::cout << "Result: " << result << std::endl;

    str1 = "TTFFF";
    str2 = "bb";
    result = solution.generateString(str1, str2);
    std::cout << "Result: " << result << std::endl;

    str1 = "TFTFTFT";
    str2 = "xxxw";
    result = solution.generateString(str1, str2);
    std::cout << "Result: " << result << std::endl;
        
    str1 = "TFTF";
    str2 = "abc";
    result = solution.generateString(str1, str2);
    std::cout << "Result: " << result << std::endl;

    str1 = "F";
    str2 = "d";
    result = solution.generateString(str1, str2);
    std::cout << "Result: " << result << std::endl;

    str1 = "F";
    str2 = "da";
    result = solution.generateString(str1, str2);
    std::cout << "Result: " << result << std::endl;

    str1 = "FTF";
    str2 = "xww";
    result = solution.generateString(str1, str2);
    std::cout << "Result: " << result << std::endl;
}
