#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>

int FindMirrors(const std::vector<std::string>& m)
{
	int result = 0;
    int rows = m.size();
    int cols = m[0].size() - 1; // invisible unicode character at the end of each line or whatever

    for (int i = 1; i < rows && !result; i++)
	{
        int diff = 0;
		for (int x = i - 1, y = i; x >= 0 && y < rows && diff < 1; x--, y++)
        {
            diff += (m[x] != m[y]);
        }
			
		if (diff == 0)
        {
            result = i * 100;
            std::cout << "Lines above: " << i << std::endl;
        }
	}

    for (int i = 1; i < cols && !result; i++)
	{
        int diff = 0;
		for (auto& row : m)
        {
            for (int x = i - 1, y = i; x >= 0 && y < cols && diff < 1; x--, y++)
            {
                diff += (row[x] != row[y]);
                // std::cout << x << " " << y << " " << " " << (row[x] != row[y]) << std::endl;
            }
        }
		if (diff == 0)
        {
            result = i;
            std::cout << "Columns left: " << i << std::endl;
        }
	}
    
	return result;
}

int main()
{
    std::ifstream file("day_13.in");
    std::string line;
    std::vector<std::string> matrix;
    int left = 0, above = 0;
    int result = 0;

    while (getline(file, line))
    {
        if (line.empty() || line == "\r" || line == "\n")
        {
			result += FindMirrors(matrix);

            matrix.clear();
        }
        else
        {
            matrix.push_back(line);
        }
    }

    result += FindMirrors(matrix);
    std::cout << result;

    return 0;
}