#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <regex>

#define MAX_DIGITS 3

using namespace std;

bool IsNearMiddle(string match, int pos, string str)
{
    bool isNearMid = false;
    int len = match.length() - 1;
    int middle = str.length() / 2;

    if (pos == middle - 1 || pos == middle || pos == middle + 1 ||
        pos + len == middle - 1 || pos + len == middle || pos + len == middle + 1)
    {
        isNearMid = true;
    }
    
    return isNearMid;
}

int GetGearRatio(string line, int gearPos, string lineAbove, string lineBelow)
{
    vector<int> adjacentNumbers;
    vector<string> adjacentStrings;
    int left, right;
    std::regex numberRegex(R"(\d+)");
    std::smatch matches;

    left = (gearPos - MAX_DIGITS >= 0) ? (gearPos - MAX_DIGITS) : 0;
    right = (gearPos + MAX_DIGITS + 1 <= line.length()) ? (gearPos + MAX_DIGITS + 1) : line.length();

    adjacentStrings.push_back(line.substr(left, (right - left)));
    if (!lineAbove.empty())
    {
        adjacentStrings.push_back(lineAbove.substr(left, (right - left)));
    }
    if (!lineBelow.empty())
    {
        adjacentStrings.push_back(lineBelow.substr(left, (right - left)));
    }

    for (auto &str : adjacentStrings)
    {
        int pos = 0;
        while (std::regex_search(str.cbegin() + pos, str.cend(), matches, numberRegex))
        {
            for (auto &match : matches)
            {
                int position = std::distance(str.cbegin(), match.first);
                if (IsNearMiddle(match, position, str))
                {
                    adjacentNumbers.push_back(std::stoi(string(match)));
                }
            }

            pos += matches.position() + matches.length();
        }
    }

    if (adjacentNumbers.size() == 2)
    {
        cout << " " << adjacentNumbers[0] << " " << adjacentNumbers[1];
        return adjacentNumbers[0] * adjacentNumbers[1];
    }

    return 0;
}

int main()
{
    ifstream file("day_3.in");
    vector<string> lines;
    string str;
    map<int, vector<int>> gearPositions; // line number, gear positions
    int lineNumber = 0;
    int result = 0;

    while (getline(file, str))
    {
        lines.push_back(str);

        int pos = str.find('*');
        while (pos != std::string::npos) {
            gearPositions[lineNumber].push_back(pos);
            pos = str.find('*', pos + 1);
        }

        lineNumber++;
    }

    for (size_t i = 0; i < lines.size(); i++)
    {   
        cout << "line: " << i << endl;
        for (size_t j = 0; j < gearPositions[i].size(); j++)
        {
            string lineAbove = (i == 0) ? string() : lines[i - 1];
            string lineBelow = (i == lines.size() - 1) ? string() : lines[i + 1];

            cout << "  gearPos: " << gearPositions[i][j];
            result += GetGearRatio(lines[i], gearPositions[i][j], lineAbove, lineBelow);
            cout << endl;
        }
    }

    cout << result;

    return 0;
}