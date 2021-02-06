#include <sstream>
#include <stdio.h>      // Standard I/O
#include <string>       // Use strings
#include <fstream>      // Create, write and read files
#include <iostream>     // For the std::cin and std::cout. I don't like, but... oh well
#include <regex>        // Unlocks REGEX POWAA
#include <utility>

#include "HTML.hpp"

struct token {
    std::regex rex;     // Regex to find the markdown token
    std::string tag;    // Equivalent tag
};

void markdown(std::string markdown, HTML *out){
    /*std::string line;
    std::stringstream input(markdown);

    while(std::getline(input, line, '\n')){        
        char const tmp = line[0];
        
        if(line[0] == '#'){                     // If the line starts with a '#', then it is a title (or subtitle, subsubtitle, etc)
            int i;
            for(i = 1; line[i]=='#'; i++){}     // So count the number of '#' in a row,

            line.erase(0, i);                   // Then delete them
            out->addChild(new Component("h" + std::to_string(i), line)); // and set the "title" level to the number of '#' there was
            out->addChild(new Component("hr")); // Plus, add a separator below the title
        }
    }*/
    
    printf("Wtf is happeninggg");

    std::list<token> tokens = {
        token{std::regex("`[^`]+`"),    "code"},   // Code tag regex
        token{std::regex("*[^*]+*"),    "i"},      // Italic tag regex
        token{std::regex("**[^**]+**"), "b"},      // Bold tag regex
        token{std::regex(">[^\n]+\n\n"),"quote"}   // Block quote
    };
    for(token tok: tokens){
        printf("Checking for %s\n", tok.tag.c_str());

        auto words_begin = std::sregex_iterator(markdown.begin(), markdown.end(), tok.rex);
        auto words_end   = std::sregex_iterator();

        int match_end, match_begin;
        for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
            std::smatch match = *i;

            match_begin = match.position();
            match_end   = match_begin + match.length()-1;

            markdown.replace(match_begin, 1, "<" + tok.tag + ">");
            markdown.replace(match_end, 1, "</" + tok.tag + ">");
            // std::cout << line.substr(match_begin+1, match_end-1) << std::endl; // Debug, print all the code matches
        }
    }

    out = new HTML(markdown);
}

//Read from a file, return a HTML object
HTML* markdown(std::string markdownInput){
    HTML *out = new HTML();

    markdown(markdownInput, out);

    return out;
}

//Read from a file, return a HTML object with style applied
HTML* markdown(std::string markdownInput, std::string stylePath){
    HTML *out = new HTML(stylePath);

    markdown(markdownInput, out);

    return out;
}
