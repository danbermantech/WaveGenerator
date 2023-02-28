#pragma once
#include <string>
using namespace std;

template <typename T>

T requestUserInput(string message, T defaultValue) {
    cout << message << " : ";
    string buffer;
    getline(std::cin, buffer);
    if constexpr (is_same_v < T, string>) {
        if (buffer.length() == 0) return defaultValue;
            return buffer;
    }
    if constexpr (is_same_v < T, char>) {
        if (buffer.length() == 0) return defaultValue;
        return buffer[0];
    }
    if constexpr (is_same_v < T, double>) {
        if (buffer.length() == 0) return defaultValue;
        return stod(buffer);
    }
    if constexpr (is_same_v < T, float > ) {
        if (buffer.length() == 0) return defaultValue;
        return stof(buffer);
    }

}