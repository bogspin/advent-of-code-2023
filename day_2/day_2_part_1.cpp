#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <regex>

using namespace std;

class Set {
public:
    int red = 0;
    int green = 0;
    int blue = 0;

    Set(int r, int g, int b)
    {
        red = r;
        green = g;
        blue = b;
    }

    Set(const string& setStr)
    {
        std::regex pattern(R"((\d+)\s*(red|blue|green))");
        std::smatch matches;

        int pos = 0;
        while (std::regex_search(setStr.begin() + pos, setStr.end(), matches, pattern))
        {
            int quantity = std::stoi(matches[1]);
            std::string color = matches[2];

            if (color == "red") {
                red = quantity;
            }
            else if (color == "green")
            {
                green = quantity;
            }
            else if (color == "blue")
            {
                blue = quantity;
            }

            pos += matches.position() + matches.length();
        }
    }

    bool operator>(const Set& other)
    {
        if (this->red > other.red || this->green > other.green || this->blue > other.blue)
        {
            return true;
        }
        return false;
    }
};

int main()
{
    ifstream file("day_2.in");
    string game;
    int gameID = 1;
    int result = 0;
    Set limitSet(12, 13, 14);

    while (getline(file, game))
    {
        vector<string> setStrArray;
        bool isGamePossible = true;

        size_t startPos = 0, endPos = game.find(';');
        while (endPos != string::npos)
        {
            setStrArray.push_back(game.substr(startPos, endPos - startPos));
            startPos = endPos + 1;
            endPos = game.find(';', startPos);
        }
        setStrArray.push_back(game.substr(startPos));

        for (auto& setStr : setStrArray)
        {
            Set setData(setStr);

            if (setData > limitSet)
            {
                isGamePossible = false;
                break;
            }
        }

        if (isGamePossible)
        {
            result += gameID;
            //cout << gameID << endl;
        }
        gameID++;
    }

    cout << result;

    return 0;
}