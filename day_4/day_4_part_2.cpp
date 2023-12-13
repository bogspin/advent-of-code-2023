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
    std::map<int, int> numberOfCards;
    std::vector<int> cardMatches;
    std::string line;
    int cardNumber = 0;
    int result = 0;

    while (getline(file, line))
    {
        line.erase(0, line.find(':') + 1);
        std::istringstream buffer(line);
        int number, matches = 0;

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
                    matches++;
                }
            }
        }
        cardMatches.push_back(matches);
        cardNumber++;
    }

    for (int i = 0; i < cardNumber; i++)
    {
        numberOfCards[i] = 1;
    }

    for (int i = 0; i < cardNumber; i++)
    {
        if (cardMatches[i] != 0)
        {
            for (int j = 1; j <= cardMatches[i]; j++)
            {
                if (i + j < cardNumber)
                {
                    numberOfCards[i + j] += numberOfCards[i];
                }
            }
        }
    }

    for (int i = 0; i < cardNumber; i++)
    {
        result += numberOfCards[i];
    }

    std::cout << result;

    return 0;
}