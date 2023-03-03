#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
/*This command specifies the following arguments:

covtype.data.txt is the name of the input file
0 is the starting line to search from
1:2:3 specifies the range to search within. This means that the program will search from line 1, column 2 to line 2, column 3 (inclusive).
0 1 2 3 are the numbers to search for in the specified range.




*/
int main(int argc, char *argv[])
{
    // Check if the correct number of command line arguments have been provided
    if (argc < 3)
    {
        cout << "Usage: " << argv[0] << " filename startLine startColumn:endLine:endColumn number [number2]" << endl;
        return 1;
    }

    // Extract the filename and starting line and column from the command line arguments
    string filename = argv[1];
    int startLine = atoi(argv[2]), startColumn = 0, endLine = -1, endColumn = -1;
    int colonIndex = -1;

    // Parse the range specification if provided
    if (argc > 3)
    {
        string rangeSpec = argv[3];
        colonIndex = rangeSpec.find(':');
        if (colonIndex != -1)
        {
            // Parse the end line and column
            stringstream ss(rangeSpec.substr(colonIndex + 1));
            char separator;
            ss >> endLine >> separator >> endColumn;
        }
    }

    // Extract the numbers to search for from the command line arguments
    int numIndex = (colonIndex != -1) ? 4 : 3;
    int numCount = argc - numIndex;
    int numbers[numCount];
    for (int i = 0; i < numCount; i++)
    {
        numbers[i] = atoi(argv[numIndex + i]);
    }

    // Open the file and start reading lines
    ifstream file("covtype.data.txt");
    string line;
    int lineNumber = 0;
    int frequency[numCount] = {0};

    // Search for the specified numbers in the specified range
    while (getline(file, line) && (endLine == -1 || lineNumber <= endLine))
    {
        if (lineNumber >= startLine)
        {
            stringstream ss(line);
            int columnNumber = 0;
            string token;
            while (getline(ss, token, ',') && (endColumn == -1 || columnNumber <= endColumn))
            {
                if (columnNumber >= startColumn)
                {
                    // Convert the token to an integer and check if it matches any of the specified numbers
                    int number = atoi(token.c_str());
                    for (int i = 0; i < numCount; i++)
                    {
                        if (number == numbers[i])
                        {
                            frequency[i]++;
                        }
                    }
                }
                columnNumber++;
            }
        }
        lineNumber++;
    }

    file.close();

    // Print the frequency of the specified numbers
    for (int i = 0; i < numCount; i++)
    {
        cout << "Number " << numbers[i] << " occurs " << frequency[i] << " times" << endl;
    }

    return 0;
}
