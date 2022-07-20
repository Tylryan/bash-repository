#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/* #include "../headers/server_info_t.h" */
#include "../headers/helper_functions.h"

int copy_content_to_server_home(server_info_t server_info, char ** argv)
{
    char command[75];
    char * content_to_copy = argv[1];
    char * server_path     = create_base_server_path(server_info);

    strcpy(command, create_base_scp_options(server_info));
    strcat(command, content_to_copy);
    strcat(command, server_path);

    printf("%s\n", command);

    system(command);
    return 0;
}

int copy_content_to_server_path(server_info_t server_info, char * from_path, char * to_path)
{
    char command[75];
    char * content_to_copy = from_path;
    char * server_path     = create_base_server_path(server_info);
    char * backup_dir_path = to_path;


    strcpy(command, create_base_scp_options(server_info));
    strcat(command, content_to_copy);
    strcat(command, server_path);
    strcat(command, "/");
    strcat(command, backup_dir_path);

    printf("%s\n", command);
    system(command);
    return 0;
}
