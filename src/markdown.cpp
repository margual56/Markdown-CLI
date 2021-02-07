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
    int length1;        // Length of the first token ("**" = 2, "*" = 1)
    int length2;        // Length of the last token (quotes only have at the beginning, newlines at the end, etc)
    std::string tag;    // Equivalent tag
};

std::string markdown(std::string markdown){
    std::smatch match;  // Match object (stores match information)

    ////////////////////////////// HEADERS //////////////////////////////////////
    std::regex headers("#+[^\\r\\n]+(\\r|\\n|\\r\\n)"); // Regex for the headers

    while (std::regex_search (markdown, match, headers)) {

        int match_begin = match.position();
        int match_end   = match_begin + match.length();

        printf("Processing match: %s", markdown.substr(match_begin, match.length()).c_str());

        int j;
        for(j = 0; markdown[j+match_begin]=='#'; j++){}     // So count the number of '#' in a row,


        markdown.insert(match_end, "</h" + std::to_string(j) + "><hr/>");
        markdown.replace(match_begin, j, "<h" + std::to_string(j) + ">");
    }

    ////////////////////////// OTHER TOKENS ////////////////////////////////////
    //token{"[^\\r\\n]+((\\r|\\n|\\r\\n)[^\\r\\n]+)*",0,2,  "p"}       // Paragraphs regex

    std::list<token> tokens = {
        token{"`[^`\\n]+`",                             1,1,  "code"},   // Code tag regex
        token{"(\\*){2}[^(\\*){2}\\r\\n]+(\\*){2}",     2,2,  "b"},      // Bold tag regex    (**)
        token{"(_){2}[^(_){2}\\r\\n]+(_){2}",           2,2,  "b"},      // Bold tag regex    (__)
        token{"\\*[^\\*\\r\\n]+\\*",                    1,1,  "i"},      // Italic tag regex  (*)
        token{"_[^\\*\\r\\n]+_",                        1,1,  "i"},      // Italic tag regex  (_)
        token{"> [^\\r\\n]+(\\r|\\n|\\r\\n){2}",        2,0,  "quote"}   // Block quote
    };

    for(token tok: tokens){
        printf("Checking for %s\n", tok.tag.c_str());
        std::regex tmp(tok.rex);
        
        int match_end, match_begin;
        while (std::regex_search (markdown, match, tmp)) {
            match_begin = match.position();
            match_end   = match_begin + match.length();

            printf("Processing match: %s\n", markdown.substr(match_begin, match.length()).c_str());

            //printf("Replacing '%s' by '%s'\n", markdown->substr(match_end, tok.length).c_str(), ("</" + tok.tag + ">").c_str());
            markdown.replace(match_end-tok.length2, tok.length2, "</" + tok.tag + ">");

            //printf("Replacing '%s' by '%s'\n", markdown->substr(match_begin, tok.length).c_str(), ("<" + tok.tag + ">").c_str());
            markdown.replace(match_begin, tok.length1, "<" + tok.tag + ">");


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

    return markdown;
}