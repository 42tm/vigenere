// Require C++ >= 11 to compile

#include <iostream>
#include "vigenere.hpp"

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
    else if (argc != 4)
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

    if (key.length() < 2)
    {
        std::cout << "[key] is too short" << std::endl;
        return 1;
    }

    if (cmd == "e")
        std::cout << encrypt(input, key);
    else if (cmd == "d")
        std::cout << decrypt(input, key);
    return 0;
}
