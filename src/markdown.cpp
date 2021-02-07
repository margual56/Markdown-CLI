#include <sstream>
#include <stdio.h>      // Standard I/O
#include <string>       // Use strings
#include <fstream>      // Create, write and read files
#include <iostream>     // For the std::cin and std::cout. I don't like, but... oh well
#include <regex>        // Unlocks REGEX POWAA
#include <algorithm>    // It does one linear scan of the string and inplace replaces all the matching characters
#include <utility>

#include "HTML.hpp"

struct token {
    std::string rex;    // Regex to find the markdown token
    int length;         // Length of the token ("**" = 2, "*" = 1)
    std::string tag;    // Equivalent tag

};

void markdown(std::string markdown, HTML *out){

    ////////////////////////////// HEADERS //////////////////////////////////////
    std::regex headers("^#+[^\\n]*\\n");
    auto header_begin = std::sregex_iterator(markdown.begin(), markdown.end(), headers);
    auto header_end   = std::sregex_iterator();
    
    int match_end, match_begin;
    for (std::sregex_iterator i = header_begin; i != header_end; ++i) {
        std::smatch match = *i;

        match_begin = match.position();
        match_end   = match_begin + match.length();

        int j;
        for(j = 1; markdown[j+match_begin-1]=='#'; j++){}     // So count the number of '#' in a row,

        markdown.replace(match_begin, j, "<h" + std::to_string(j) + ">");
        markdown.insert(match_end, "</h" + std::to_string(j) + ">");
    }

    ////////////////////////// OTHER TOKENS ////////////////////////////////////
    std::list<token> tokens = {
        token{"`[^`\\n]+`",                 1,  "code"},   // Code tag regex
        token{"(\\*){2}[^(\\*){2}\\n]+(\\*){2}",2,  "b"},      // Bold tag regex    (**)
        token{"(_){2}[^(_){2}\\n]+(_){2}",        2,  "b"},      // Bold tag regex    (__)
        token{"\\*[^\\*\\n]+\\*",           1,  "i"},      // Italic tag regex  (*)
        token{"_[^\\*\\n]+_",               1,  "i"}       // Italic tag regex  (_)
        //token{"^>[^\\n]+\\n\\n","quote"}   // Block quote
    };

    for(token tok: tokens){
        printf("Checking for %s\n", tok.tag.c_str());
        std::regex tmp(tok.rex);
        auto words_begin = std::sregex_iterator(markdown.begin(), markdown.end(), tmp);
        auto words_end   = std::sregex_iterator();
        
        int match_end, match_begin;
        for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
            std::smatch match = *i;

            match_begin = match.position();
            match_end   = match_begin + match.length();

            //printf("Processing match: %i, %i\n", match_begin, match_end);

            printf("Replacing '%s' by '%s'\n", markdown.substr(match_begin, tok.length).c_str(), ("<" + tok.tag + ">").c_str());
            markdown.replace(match_begin, tok.length, "<" + tok.tag + ">");

            printf("Replacing '%s' by '%s'\n", markdown.substr(match_end+tok.length, tok.length).c_str(), ("</" + tok.tag + ">").c_str());
            markdown.replace(match_end+tok.length, tok.length, "</" + tok.tag + ">");


            // std::cout << line.substr(match_begin+1, match_end-1) << std::endl; // Debug, print all the code matches
        }

        printf("Done checking %s\n", tok.tag.c_str());
    }

    ////////////////////////////// LINE BREAKS ///////////////////////////////////
    for(int i = 0; i<markdown.length(); i++){
        if(markdown[i] == '\n'){
            markdown.replace(i, 1, "<br/>");
        }
    }

    //out = new HTML();
    out->setText(markdown);
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
