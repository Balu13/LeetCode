#include "Solution.h"

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

//                    if (!check)
//                    {
//                        check = true;
//                        for (size_t t1 = 0; t1 < tracking[t].size(); ++t1)
//                        {
//                            if (tracking[t][t1] != str2[t1])
//                            {
                                word += requiredChar;
                                check = true;
//                                break;
//                            }
//                        }
//                    }
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
