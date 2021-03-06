#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <fstream>
#include <string>
#include <utility>

class Utils
{
private:
    Utils();
public:
    static std::istream& SafeGetLine(std::istream& is, std::string& t, char ch);
    static void PrintCurDir();
};
#endif
