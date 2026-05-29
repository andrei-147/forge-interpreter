#pragma once

#include <cstring>

namespace fg {

    inline bool isLower(char c) {
        return 'a' <= c && c <= 'z';
    }

    inline bool isUpper(char c) {
        return 'A' <= c && c <= 'Z';
    }

    inline bool isNumeric(char c) {
        return '0' <= c && c <= '9';
    }

    inline char lower(char c) {
        if (isUpper(c)) return c + 32;
        return c;
    }

    inline char upper(char c) {
        if (isLower(c)) return c - 32;
        return c;
    }

    inline bool isAlpha(char c) {
        return isLower(c) || isUpper(c);
    }

    inline bool isAlphaNum(char c) {
        return isAlpha(c) || isNumeric(c);
    }

    inline bool isIdentifier(char c) {
        return isAlphaNum(c) || c == '_';
    }
}
