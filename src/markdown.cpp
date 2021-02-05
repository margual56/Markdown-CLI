#include <sstream>
#include <stdio.h>      // Standard I/O
#include <string>       // Use strings
#include <fstream>      // Create, write and read files
#include <iostream>     // For the std::cin and std::cout. I don't like, but... oh well
#include <utility>

#include "HTML.hpp"

void markdown(std::string markdown, HTML *out){
    std::string line;
    std::stringstream input(markdown);

    while(std::getline(input, line, '\n')){        
        char const tmp = line[0];
        
        if(line[0] == '#'){
            int i;
            for(i = 1; line[i]=='#'; i++){}

            line.erase(0, i);
            out->addChild(new Component("h" + std::to_string(i), line));
            out->addChild(new Component("hr"));                
        }else{
            out->addChild(new Component("p", line));
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
