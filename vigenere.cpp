// Require C++ >= 11 to compile

#include <iostream>
#include <algorithm>
#include <string>
#include <cctype>

bool isAlphaOnly(const std::string input)
{
    for (auto itr : input)
        if (!isalpha(itr))
            return false;
    return true;
}

int CharToInt(const char ch)
{
    if (ch >= 'A' && ch <= 'Z')
        return (ch - 'A');
    else if (ch >= 'a' && ch <= 'z')
        return (ch - 'a');
    else
        return -1;
}

char IntToChar(const int i, bool isUpper = true)
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

char divide(char ch1, char ch2)
{
    int ans = CharToInt(ch1) - CharToInt(ch2);
    if (ans < 0)
        ans += 26;
    return IntToChar(ans, isupper(ch1));
}

std::string encrypt(std::string input, const std::string key)
{
    long k = 0;
    for (auto &itr : input)
        if (isalpha(itr))
            itr = combine(itr, key[(k++) % key.size()]);
    return input;
}

std::string decrypt(std::string input, const std::string key)
{
    long k = 0;
    for (auto &itr : input)
        if (isalpha(itr))
            itr = divide(itr, key[(k++) % key.size()]);
    return input;
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        std::cout << "vigenere <command> [input] [key]" << std::endl
                  << std::endl
                  << "<command>" << std::endl
                  << "e\tEncrypt string [input] with string [key]" << std::endl
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
    // Standardized [key] string
    std::transform(key.begin(), key.end(), key.begin(), ::toupper);

    if (!isAlphaOnly(key))
    {
        std::cout << "[key] contain irregular character(s)" << std::endl;
        return 1;
    }

    if (cmd == "e")
        std::cout << encrypt(input, key);
    if (cmd == "d")
        std::cout << decrypt(input, key);
    return 0;
}
