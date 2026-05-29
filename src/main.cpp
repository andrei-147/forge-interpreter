#include <fstream>
#include <ios>
#include <iostream>
#include <filesystem>
#include <string>

#include "console_utils.hpp"
#include "tokenizer.hpp"

namespace fs = std::filesystem;

void usage() {
    fg::perror("Usage: forge-exec </path/file-name.mold> <task> [...task arguments...]");
}

#define CHUNK_SIZE 4096

int main(int argc, char *argv[]) {

    // if the required args are not specified do not run and error out with the usage message
    if (argc < 3) {
        usage();
        return 1;
    }

    // check for and load the .mold file
    fs::path moldpath = fs::absolute(argv[1]);
    if (!fs::exists(moldpath)) {
        usage();
        fg::perror(".mold file not found.");
        return 1;
    }
    std::ifstream file(moldpath, std::ios::binary);

    // save the task into a string
    std::string task = argv[2];

    // read the mold file into the content string
    std::string content;
    file.seekg(0, std::ios::end);
    content.resize(file.tellg());
    file.seekg(0, std::ios::beg);

    file.read(content.data(), content.size());

    // split the content string into tokens using the lexer
    fg::Lexer l{content};
    auto tokens = l.getTokens();

    for (auto& tk : tokens) {
        std::cout << [tk](){
            switch (tk.getType()) {
                case fg::Tokens::COMMENT:    return "COMMENT   ";
                case fg::Tokens::STRING:     return "STRING    ";
                case fg::Tokens::SYMBOL:     return "SYMBOL    ";
                case fg::Tokens::NUMBER:     return "NUMBER    ";
                case fg::Tokens::KEYWORD:    return "KEYWORD   ";
                case fg::Tokens::IDENTIFIER: return "IDENTIFIER";
            }
        }() << " : " << tk.getValue() << '\n';
    }

    return 0;
}
