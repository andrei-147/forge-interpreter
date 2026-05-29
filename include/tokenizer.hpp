#pragma once

#include <cctype>
#include <cstring>
#include <ranges>
#include <string>
#include <vector>

#include "string_utils.hpp"

namespace fg {
    enum class Tokens : int {
        KEYWORD,
        IDENTIFIER,
        STRING,
        NUMBER,
        SYMBOL,
        COMMENT
    };

    class Token {
        private:
            Tokens type;
            std::string value;
        public:
            Token() = delete;
            Token(Tokens type, std::string val) : type(type), value(val) {}

            Tokens getType() const noexcept { return type; }
            std::string &getValue() noexcept { return value; }

    };

    inline const std::vector<std::string> keywords = {
        "import",
        "for",
        "do",
        "while",
        "if",
        "else",
        "elif",
        "var",
        "const",
        "task",
        "property",
        "properties",
        "null",
        "template",
        "task"
    };

    class Lexer {
        private:
            std::string &str;
            std::string::iterator it;

            bool isSymbol(char c) {
                return strchr("(){}:,=+-*/%&|^!", c);
            }

            bool isKeyword(std::string str) {
                for (const auto& s : keywords) if (str == s) return true;
                return false;
            }

        public:
            Lexer() = delete;
            Lexer(std::string &str) : str(str) {
                it = str.begin();
            }

            std::vector<Token> getTokens() {
                std::vector<Token> tokens;
                std::string builder;
                while (it != str.end()) {
                    char c = *it;
                    if (isSymbol(c)) {
                        tokens.emplace_back(Tokens::SYMBOL, str.substr(it - str.begin(), 1));
                        ++it;
                    }
                    else if (c == '#') {
                        do { ++it; } while (it != str.end() && !strchr("#\n", *it));
                        ++it;
                    }
                    else if (c == '"') {
                        builder.clear();
                        ++it;
                        while (it != str.end() && *it != '"') builder += *(it++);
                        tokens.emplace_back(Tokens::STRING, builder);
                        ++it;
                    } else if (isNumeric(c)) {
                        builder = c;
                        ++it;
                        while (it != str.end() && isNumeric(c)) builder += *(it++);
                        tokens.emplace_back(Tokens::NUMBER, builder);
                    } else if (isIdentifier(c)) {
                        builder = c;
                        ++it;
                        while (it != str.end() && isIdentifier(*it)) builder += *(it++);
                        if (isKeyword(builder)) {
                            tokens.emplace_back(Tokens::KEYWORD, builder);
                        } else tokens.emplace_back(Tokens::IDENTIFIER, builder);
                    } else ++it;
                }
                return tokens;
            }
    };
}
