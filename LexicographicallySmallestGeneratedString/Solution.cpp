#include "Solution.h"
#include <string>
#include <iostream>

std::string Solution::generateString(std::string str1, std::string str2)
{
    std::string word = "";
    unsigned int fixedSymbols = 0;
    std::string* tracking = new std::string[str1.size()];
    for (int t = 0; t < str1.size(); ++t)
    {
        tracking[t] = "";
    }

    const std::string abc = "abcdefghijklmnopqrstuvwxyz";

    for (size_t i = 0; i < str1.size(); ++i)
    {
        switch (str1[i])
        {
        case 'T':
        {
            bool check = true;
            for (int t = 0; t < str1.size(); ++t)
            {
                if (!tracking[t].empty() && tracking[t][0] != str2[0])
                {
                    check = false;
                    break;
                }
            }
            if (!check)
            {
                word = "";
                break;
            }

            word += str2[0];
            tracking[i] = str2;
        }
        break;
        case 'F':
        {
            bool check = false;
            bool allTrackingEmpty = true;
            char requiredChar = 0;
            for (int t = 0; t < str1.size(); ++t)
            {
                if (!tracking[t].empty())
                {
                    allTrackingEmpty = false;
                    if (requiredChar == 0)
                        requiredChar = tracking[t][0];

                    if (tracking[t][0] != requiredChar)
                    {
                        check = false;
                        break;
                    }

                    word += requiredChar;
                    check = true;
                }
            }

            if (allTrackingEmpty)
            {
                for (size_t a = 0; a < abc.size(); ++a)
                {
                    if (str2.size() > 1)
                    {
                        word += 'a';
                        check = true;
                        break;
                    }
                    else if (str2[0] != abc[a])
                    {
                        word += abc[a];
                        check = true;
                        break;
                    }
                }
            }

            if (!check)
            {
                word = "";
                break;
            }

        }
        break;
        }

        for (int t = 0; t < str1.size(); ++t)
        {
            tracking[t] = tracking[t].size() > 1 ? tracking[t].substr(1) : "";
        }

        if (word.empty())
        {
            break;
        }
    }

    if (!word.empty())
    {
        if (str1[str1.size() - 1] == 'T')
        {
            word += str2.size() > 1 ? str2.substr(1) : "";
        }
        else
        {
            bool shouldChangeLetter = false;
            if (word[word.size() - 1] == str2[0])
            {
                shouldChangeLetter = true;
            }
            for (size_t i2 = 1; i2 < str2.size(); ++i2)
            {
                bool allTrackingEmpty = true;
                char requiredChar = 0;
                for (int t = 0; t < str1.size(); ++t)
                {
                    if (!tracking[t].empty())
                    {
                        allTrackingEmpty = false;

                        if (requiredChar == 0)
                            requiredChar = tracking[t][0];

                        if (tracking[t][0] != requiredChar)
                        {
                            word = "";
                            break;
                        }
                    }
                }
                if (!word.empty())
                {
                    if (!allTrackingEmpty)
                    {
                        word += requiredChar;
                    }
                    else
                    {
                        if (shouldChangeLetter)
                        {
                            for (size_t a = 0; a < abc.size(); ++a)
                            {
                                if (str2[i2] != abc[a])
                                {
                                    word += abc[a];
                                    shouldChangeLetter = false;
                                    break;
                                }
                            }
                        }
                        else
                        {
                            word += 'a';
                        }
                    }
                }
                for (int t = 0; t < str1.size(); ++t)
                {
                    tracking[t] = tracking[t].size() > 1 ? tracking[t].substr(1) : "";
                }
            }
        }
    }

    delete[] tracking;
    return word;
}

std::string Solution::generateString2(std::string str1, std::string str2)
{
    std::string* tracking = new std::string[str1.size()];

    for (int t = 0; t < str1.size(); ++t)
    {
        tracking[t] = "";
        for (int i = 0; i < t; ++i)
        {
            tracking[t] += " ";
        }

        if (str1[t] == 'T')
            tracking[t] += str2;
        else
        {
            std::string upperStr2 = str2;
            for (char& c : upperStr2)
                c = static_cast<char>(toupper(static_cast<unsigned char>(c)));
            tracking[t] += upperStr2;
        }
        std::cout << "Tracking[" << t << "]: " << tracking[t] << std::endl;
    }

    size_t wordLength = str1.size() + str2.size() - 1;
    std::string word = "";
    word.reserve(wordLength);

    for (size_t i = 0; i < wordLength; ++i)
    {
        char mustChar = 0;      // required lowercase character for this position
        char mustNotChar = 0;   // forbidden character (from uppercase tracking entry)
        bool allTrackingEmpty = true;

        for (int t = 0; t < (int)str1.size(); ++t)
        {
            if (tracking[t].size() > i)
            {
                allTrackingEmpty = false;
                char c = tracking[t][i];

                if (c == ' ')
                {
                    // ANY: no constraint from this tracking entry
                    continue;
                }
                else if (islower(static_cast<unsigned char>(c)))
                {
                    // MUST match this lowercase letter
                    if (mustChar == 0)
                        mustChar = c;
                    else if (mustChar != c)
                    {
                        // conflicting MUST requirements
                        delete[] tracking;
                        return "";
                    }
                }
                else if (isupper(static_cast<unsigned char>(c)))
                {
                    // MUST NOT match the lowercase version of this letter
                    char forbidden = static_cast<char>(tolower(static_cast<unsigned char>(c)));
                    if (mustNotChar == 0)
                        mustNotChar = forbidden;
                    else if (mustNotChar != forbidden)
                    {
                        // multiple MUST-NOT constraints; keep the stricter one
                        // both are forbidden, so we just need to avoid both — handled below
                        // for simplicity treat as conflict only if they differ and we later resolve
                    }
                }
            }
        }

        if (allTrackingEmpty)
        {
            delete[] tracking;
            return "";
        }

        if (mustChar != 0)
        {
            // We have a MUST character; verify it doesn't conflict with MUST-NOT
            if (mustChar == mustNotChar)
            {
                delete[] tracking;
                return "";
            }
            word += mustChar;
        }
        else
        {
            // No MUST; pick the lexicographically smallest letter that is not mustNotChar
            bool found = false;
            for (char a = 'a'; a <= 'z'; ++a)
            {
                if (a != mustNotChar)
                {
                    word += a;
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                delete[] tracking;
                return "";
            }
        }
    }

    delete[] tracking;
    return word;
}