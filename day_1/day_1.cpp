#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main()
{
    vector<string> input;
    string str;
    string digits = "0123456789";
    map<string, string> meltedDigitsMap = {
        {"oneight", "18"},
        {"twone", "21"},
        {"threeight", "38"},
        {"fiveeight", "58"},
        {"sevenine", "79"},
        {"eightwo", "82"},
        {"eightree", "83"},
        {"nineight", "98"}
    };

    map<string, string> digitsMap = {
        {"zero", "0"},
        {"one", "1"},
        {"two", "2"},
        {"three", "3"},
        {"four", "4"},
        {"five", "5"},
        {"six", "6"},
        {"seven", "7"},
        {"eight", "8"},
        {"nine", "9"}
    };

    ifstream file("day_1.in");
    unsigned int result = 0;

    while (getline(file, str))
    {
        for (auto& pair : meltedDigitsMap)
        {
            size_t pos = str.find(pair.first);
            while (pos != string::npos)
            {
                str.replace(pos, pair.first.length(), pair.second);
                pos = str.find(pair.first, pos + pair.second.length());
            }
        }
        
        for (auto& pair : digitsMap)
        {
            size_t pos = str.find(pair.first);
            while (pos != string::npos)
            {
                str.replace(pos, pair.first.length(), pair.second);
                pos = str.find(pair.first, pos + 1);
            }
        }

        input.push_back(str);
    }

    for (auto& s : input)
    {
        int a, b;

        if (s.find_first_of(digits) != string::npos)
        {
            a = s[s.find_first_of(digits)] - '0';
        }

        if (s.find_last_of(digits) != string::npos)
        {
            b = s[s.find_last_of(digits)] - '0';
        }

        result += (a * 10) + b;
    }

    cout << result;

    return 0;
}