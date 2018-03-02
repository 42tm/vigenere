// Require C++ >= 11 to compile

#include <iostream>
#include <algorithm>
#include <string>
#include <cctype>

bool isAlpha(char ch)
{
    return ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'));
}

bool isAlphaOnly(std::string input)
{
    for (auto itr : input)
        if (!isAlpha(itr))
            return false;
    return true;
}

int CharToInt(char ch)
{
    if (ch >= 'A' && ch <= 'Z')
        return (ch - 'A');
    else if (ch >= 'a' && ch <= 'z')
        return (ch - 'a');
    else
        return -1;
}

char IntToChar(int i, bool isUpper = true)
{
    if (i >= 0 && i < 26)
        return (isUpper ? (i + 'A') : (i + 'a'));
    else
        return 0;
}

char combine(char ch1, char ch2)
{
    int ans = CharToInt(ch1) + CharToInt(ch2);
    ans %= 26;
    return IntToChar(ans, isupper(ch1));
}

char divine(char ch1, char ch2)
{
    int ans = CharToInt(ch1) - CharToInt(ch2);
    if (ans < 0)
        ans += 26;
    return IntToChar(ans, isupper(ch1));
}

std::string encode(std::string input, std::string key)
{
    std::transform(key.begin(), key.end(), key.begin(), ::toupper);
    auto k = 0;
    for (auto &itr : input)
        if (isAlpha(itr))
            itr = combine(itr, key[k++ % key.size()]);
    return input;
}

std::string decode(std::string input, std::string key)
{
    std::transform(key.begin(), key.end(), key.begin(), ::toupper);
    auto k = 0;
    for (auto &itr : input)
        if (isAlpha(itr))
            itr = divine(itr, key[k++ % key.size()]);
    return input;
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        std::cout << "vigenere <command> [input] [key]" << std::endl
                  << std::endl
                  << "<command>" << std::endl
                  << "e\tEncode string [input] with string [key]" << std::endl
                  << "d\tDecrypt string [input] with string [key]" << std::endl;
        return 0;
    }

    if (argc < 4)
    {
        std::cout << "Wrong parameter(s)" << std::endl;
        return 1;
    }

    std::string cmd = argv[1];
    std::string input = argv[2];
    std::string key = argv[3];

    if (!isAlphaOnly(key))
    {
        std::cout << "[key] contain irregular character(s)" << std::endl;
        return 1;
    }
    if (cmd == "e")
        std::cout << encode(input, key);
    if (cmd == "d")
        std::cout << decode(input, key);
    return 0;
}