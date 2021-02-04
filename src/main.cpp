#include <cstring>
#include <getopt.h>     // GNU's getopt (parse CL arguments)
#include <stdio.h>      // Standard I/O
#include <string>       // Use strings
#include <fstream>      // Create, write and read files

#include "markdown.hpp" // Markdown parser

/* Flag set by ‘--verbose’. */
static int verbose_flag;

int main(int argc, char **argv) {
    int c;
    std::string styleFile, inputFile, outputFile;

    while (1) {
        static struct option long_options[] = {
            /* These options set a flag. */
            {"verbose", no_argument, &verbose_flag, 1},
            {"brief", no_argument, &verbose_flag, 0},
            {"help", no_argument, 0, 'h'},
            {"style", required_argument, 0, 's'},
            {"input", required_argument, 0, 'i'}
        };
        /* getopt_long stores the option index here. */
        int option_index = 0;

        c = getopt_long(argc, argv, "hs:i:", long_options, &option_index);

        /* Detect the end of the options. */
        if (c == -1)
            break;

        switch (c) {
            case 'h':
                printf("Gotta show the man page (or the help)");
            break;

            case 's':
                styleFile = optarg;
            break;

            case 'i':
                inputFile = optarg;
            break;

            case '?':
                /* getopt_long already printed an error message. */
            break;

            default:
                abort();
        }
    }

    /* Instead of reporting ‘--verbose’
    and ‘--brief’ as they are encountered,
    we report the final status resulting from them. */
    if (verbose_flag)
        puts("verbose flag is set");

    if (optind+1 < argc) {
        perror("Too many arguments");
        exit(2);
    }

    HTML output;
    if(!inputFile.empty()){
        printf("Input: %s\n", inputFile.c_str());
    }else{
        printf("Input: stdin\n");
    }

    if(!styleFile.empty()){
        printf("Style: %s\n", styleFile.c_str());
    }

    //output = markdownFile(outputFile, nullptr);
    if(optind < argc){
        outputFile = argv[optind++];
        printf("Output: %s\n", outputFile.c_str());

        //std::fstream outputFile(argv[optind++], std::ios::in);
    }else{
        printf("Output: stdout\n");
    }


    exit(0);
}