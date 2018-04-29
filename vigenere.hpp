/*
 * vigenere - Library for the vigenere cypher
 * Copyright (C) 2018 42tm Team
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once
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
