#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

int main()
{
    std::ifstream file("day_4.in");
    std::map<int, std::vector<int>> winningNumbers;
    std::vector<int> cardPoints;
    std::string line;
    int cardNumber = 0;
    int result = 0;

    while (getline(file, line))
    {
        line.erase(0, line.find(':') + 1);
        std::istringstream buffer(line);
        int number, points = 0;

        while (buffer >> number && number != '|')
        {
            winningNumbers[cardNumber].push_back(number);
        }

        size_t pos = line.find('|');
        if (pos != std::string::npos)
        {
            std::istringstream remainingBuffer(line.substr(pos + 1));
            while (remainingBuffer >> number)
            {
                if (std::find(winningNumbers[cardNumber].cbegin(), winningNumbers[cardNumber].cend(), number) != winningNumbers[cardNumber].end())
                {
                    if (points == 0)
                        points = 1;
                    else
                        points *= 2;
                }
            }
        }
        cardPoints.push_back(points);
        cardNumber++;
    }

    for (size_t i = 0; i < cardPoints.size(); i++)
    {
        result += cardPoints[i];
    }
    std::cout << result;

    return 0;
}