#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "../headers/main_functions.h"
#ifndef _HELP
#define _HELP
#include "../headers/helper_functions.h"
#endif

int main(int argc, char ** argv)
{
    server_info_t server_info = {
        .SERVER_ADDRESS = getenv("SERVER_ADDRESS"),
        .SERVER_HOST    = getenv("SERVER_HOST"),
        .SERVER_PORT    = getenv("SERVER_PORT")
    };

    int needs_help = (strcmp(argv[1], "-h") == 0) || 
        (strcmp(argv[1], "--help") == 0);

    if (needs_help)
    {
        print_help_message(argv[0]);
        exit(EXIT_SUCCESS);
    }

    if (argc > 3)
    {
        fprintf(stderr, "Error: too many arguments\n");
        exit(EXIT_FAILURE);
    }

    else if (argc < 2)
    {
        char * from_path = "~/documents";
        char * to_path   = "external-drive/documents";
        copy_content_to_server_path(server_info, from_path, to_path);
        exit(EXIT_SUCCESS);
    }

    else if (argc == 2)
    {
        copy_content_to_server_home(server_info, argv);
        exit(EXIT_SUCCESS);
    }

    else if (argc == 3)
    {
        char * from_path = argv[1];
        char * to_path   = argv[2];
        copy_content_to_server_path(server_info, from_path, to_path);
        exit(EXIT_SUCCESS);
    }

    exit(EXIT_SUCCESS);
}
