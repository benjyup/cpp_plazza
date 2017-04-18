//
// Created by peixot_b on 18/04/17.
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>

unsigned     NbOfLine(const char *file)
{
    std::ifstream   myfile(file);

    myfile.unsetf(std::ios_base::skipws);
    unsigned line_count = std::count(
            std::istream_iterator<char>(myfile),
            std::istream_iterator<char>(), '\n');
    return (line_count);
}

void    ParseFile(const char *file, int nbThread)
{
    std::ifstream   myfile(file);

    std::string line;
    int count = 0 ;
    if(!myfile.is_open())
        std::cout << "Cannot open the text.txt file" << std::endl;
    else
    {
        while(myfile.good())
        {
            count++;
            getline(myfile, line);
            if (count < 5 || count > 8)
                continue;
            else
                std::cout << line << std::endl;
        }
    }
}

int main() {
    NbOfLine("test.txt");
    ParseFile("test.txt");
}