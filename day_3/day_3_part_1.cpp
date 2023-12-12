#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <regex>

using namespace std;

bool IsAdjacent(string line, string number, string lineAbove, string lineBelow)
{
    string symbols = "~!@#$%^&*_-+=/?";
    string adjacentStr;
    bool isAdjacent = false;

    int pos = line.find(number);
    if (pos > 0)
    {
        adjacentStr += line[pos - 1];
    }
    if ((pos + number.length()) <= line.length())
    {
        adjacentStr += line[pos + number.length()];
    }
    if (!lineAbove.empty())
    {
        if (pos > 0)
        {
            adjacentStr += lineAbove.substr(pos - 1, number.length() + 2);
        }
        else
        {
            adjacentStr += lineAbove.substr(pos, number.length() + 1);
        }
    }
    if (!lineBelow.empty())
    {
        if (pos > 0)
        {
            adjacentStr += lineBelow.substr(pos - 1, number.length() + 2);
        }
        else
        {
            adjacentStr += lineBelow.substr(pos, number.length() + 1);
        }
    }


    if (adjacentStr.find_first_of(symbols) != string::npos)
    {
        isAdjacent = true;
    }

    return isAdjacent;
}

int main()
{
    ifstream file("day_3.in");
    vector<string> lines;
    string str;
    map<int, vector<string>> numbers; // line number, vector of extracted numbers
    int lineNumber = 0;
    int result = 0;

    std::regex numberRegex(R"(\d+)");
    std::smatch matches;

    while (getline(file, str))
    {
        lines.push_back(str);

        int pos = 0;
        while (std::regex_search(str.cbegin() + pos, str.cend(), matches, numberRegex))
        {
            for (auto& match : matches)
            {
                numbers[lineNumber].push_back(string(match));
            }

            pos += matches.position() + matches.length();
        }
        lineNumber++;
    }

    for (size_t i = 0; i < lines.size(); i++)
    {
        for (size_t j = 0; j < numbers[i].size(); j++)
        {
            string lineAbove = (i == 0) ? string() : lines[i - 1];
            string lineBelow = (i == lines.size() - 2) ? string() : lines[i + 1];

            if (IsAdjacent(lines[i], numbers[i][j], lineAbove, lineBelow))
            {
                result += std::stoi(numbers[i][j]);
                cout << numbers[i][j] << " ";
            }
        }
        cout << endl;
    }

    cout << result;

    return 0;
}