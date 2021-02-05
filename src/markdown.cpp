#include <sstream>
#include <stdio.h>      // Standard I/O
#include <string>       // Use strings
#include <fstream>      // Create, write and read files
#include <iostream>     // For the std::cin and std::cout. I don't like, but... oh well
#include <regex>        // Obviously, required to do regex on the lines
#include <utility>

#include "HTML.hpp"

void markdown(std::string markdown, HTML *out){
    std::string line;
    std::stringstream input(markdown);

    while(std::getline(input, line, '\n')){        
        char const tmp = line[0];
        
        if(line[0] == '#'){                     // If the line starts with a '#', then it is a title (or subtitle, subsubtitle, etc)
            int i;
            for(i = 1; line[i]=='#'; i++){}     // So count the number of '#' in a row,

            line.erase(0, i);                   // Then delete them
            out->addChild(new Component("h" + std::to_string(i), line)); // and set the "title" level to the number of '#' there was
            out->addChild(new Component("hr")); // Plus, add a separator below the title
        }else{
            std::regex words_regex("`[^`]+`");
            auto words_begin = std::sregex_iterator(line.begin(), line.end(), words_regex);
            auto words_end   = std::sregex_iterator();
        
            Component *paragraph = new Component("p");
            int match_end = -1, match_begin;
            for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
                std::smatch match = *i;

                match_begin = match.position();

                if(match_end +1 < match_begin -1)
                    paragraph->addChild(new Component("", line.substr(match_end +1, match_begin -1)));

                match_end   = match_begin + match.length()-1;

                // std::cout << line.substr(match_begin+1, match_end-1) << std::endl; // Debug, print all the code matches
                if(match_begin +1 < match_end -1)
                    paragraph->addChild(new Component("code", line.substr(match_begin+1, match_end-1)));
            }
            if(match_end +1 < line.length() -1)
                paragraph->setText(line.substr(match_end +1, line.length() -1));

            std::cout << paragraph->render() << std::endl;

            out->addChild(paragraph);
        }

    }
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
