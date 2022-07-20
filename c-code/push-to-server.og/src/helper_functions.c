#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <libgen.h>

#include "../headers/server_info_t.h"

char * create_base_server_path(server_info_t server_info)
{

    static char server_path[50];
    strcpy(server_path, " ");
    strcat(server_path, server_info.SERVER_ADDRESS);
    strcat(server_path, ":/home/");
    strcat(server_path, server_info.SERVER_HOST);

    return server_path;

}

char * create_base_scp_options(server_info_t server_info)
{
    static char command[25];
    strcpy(command,"/usr/bin/scp ");
    strcat(command, "-r -P ");
    strcat(command, server_info.SERVER_PORT);
    strcat(command, " ");

    return command;
}

void print_help_message(char * arg0)
{
        
    printf("USAGE\n\
%s [file-to-copy] [server-location]\n\n\
DESCRIPTION\n\
    Copies a file/directory from your local directory to the server\n\
    specified in your environemnt variables.\n\
Examples\n\
    (Don't enter in anything)\n\
    Copy your documents directory to your server. \n\
    `%s`\n\n\
    Copy a file/dir to your server's home dir, only enter the file \n\
    you want to copy.\n\
    `%s file.txt`\n\n\
    Copy a file/dir to a specific location in your server, enter \n\
    the filename and the server directory \n\
    (Don't use /home/name or ~/)\n\
    `%s file.txt documents/notes/computers`\n",
    basename(arg0),
    basename(arg0),
    basename(arg0),
    basename(arg0));
}
