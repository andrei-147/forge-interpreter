#pragma once

#include <iostream>
#include <functional>

namespace fg {

    struct Choice {
        std::string name;
        char ch;
        std::function<void()> action;
    };

    enum class Color : int {
        Red,
        Green,
        Yellow,
        Blue,
        Magenta,
        Cyan,
        White,
        Reset
    };

    enum class Modifier : int {
        Regular,
        Bold,
        Italic,
        Underline
    };

    inline void color_code(const Color col = Color::Reset, const Modifier mod = Modifier::Regular) {
    #if defined(FORGE_PLATFORM_WINDOWS)
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        switch (col) {
            case Color::Red:     SetConsoleTextAttribute(hConsole, FOREGROUND_RED   | FOREGROUND_INTENSITY); break;
            case Color::Green:   SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY); break;
            case Color::Yellow:  SetConsoleTextAttribute(hConsole, FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_INTENSITY); break;
            case Color::Blue:    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE  | FOREGROUND_INTENSITY); break;
            case Color::Magenta: SetConsoleTextAttribute(hConsole, FOREGROUND_RED   | FOREGROUND_BLUE  | FOREGROUND_INTENSITY); break;
            case Color::Cyan:    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE  | FOREGROUND_INTENSITY); break;
            case Color::White:   SetConsoleTextAttribute(hConsole, FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY); break;
            case Color::Reset:   SetConsoleTextAttribute(hConsole, FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_BLUE); break;
        }
    #elif defined(FORGE_PLATFORM_LINUX) || defined(FORGE_PLATFORM_MACOS)
        switch (mod) {
            case Modifier::Bold:      std::cout << "\033[1m"; break;
            case Modifier::Italic:    std::cout << "\033[3m"; break;
            case Modifier::Underline: std::cout << "\033[4m"; break;
            case Modifier::Regular:   break;
        }
        switch (col) {
            case Color::Red:     std::cout << "\033[31m"; break;
            case Color::Green:   std::cout << "\033[32m"; break;
            case Color::Yellow:  std::cout << "\033[33m"; break;
            case Color::Blue:    std::cout << "\033[34m"; break;
            case Color::Magenta: std::cout << "\033[35m"; break;
            case Color::Cyan:    std::cout << "\033[36m"; break;
            case Color::White:   std::cout << "\033[37m"; break;
            case Color::Reset:   std::cout << "\033[0m";  break;
        }
    #endif
    }

    inline void perror(const std::string errstr) {
        std::cout << '[';
        fg::color_code(fg::Color::Red, fg::Modifier::Bold);
        std::cout << "ERROR";
        fg::color_code(fg::Color::Reset);
        std::cout << "] " << errstr << '\n';
    }


    inline void pinfo(const std::string infostr) {
        std::cout << '[';
        fg::color_code(fg::Color::Cyan, fg::Modifier::Bold);
        std::cout << "INFO";
        fg::color_code(fg::Color::Reset);
        std::cout << "] " << infostr << '\n';
    }


    inline void pwarn(const std::string warnstr) {
        std::cout << '[';
        fg::color_code(fg::Color::Yellow, fg::Modifier::Bold);
        std::cout << "WARNING";
        fg::color_code(fg::Color::Reset);
        std::cout << "] " << warnstr << '\n';
    }


    inline void psuccess(const std::string str) {
        std::cout << '[';
        fg::color_code(fg::Color::Green, fg::Modifier::Bold);
        std::cout << "SUCCESS";
        fg::color_code(fg::Color::Reset);
        std::cout << "] " << str << '\n';
    }
}
