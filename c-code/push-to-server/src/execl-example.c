#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

/* This allows sensitive data to be used indirectly via environment variables */
typedef struct user_info_t
{
    char * host_name;
    char * server_address;
    char *  port_number;

} user_info_t;

char * create_base_file_destination(user_info_t user_info);
int main(int argc, char ** argv)
{
    (void) argc;

    user_info_t user_info = {
        .host_name      = getenv("SERVER_HOST"),
        .server_address = getenv("SERVER_ADDRESS"),
        .port_number    = getenv("SERVER_PORT")
    };

    char * file_destination = create_base_file_destination(user_info);
    printf("Before Process\n"); // this runs twice

    int pid;
    // pid < 0 means failed
    if ((pid = fork()) < 0)
    {
        perror("");
        exit(EXIT_FAILURE);
    }

    // If pid != 1 then it is a child
    else if (!pid)
    {
        execl("/usr/bin/scp", "scp", "-r", "-P", user_info.port_number,
                argv[1], file_destination, (char *) NULL);
    }

    printf("After process\n");
    exit(EXIT_SUCCESS);

}
char * create_base_file_destination(user_info_t user_info)
{
    int max_path_length = pathconf(".", _PC_PATH_MAX);
    char * file_destination;
    file_destination = calloc(max_path_length, sizeof(char));

    strcpy(file_destination, user_info.server_address);
    strcat(file_destination, ":");
    strcat(file_destination, "/home/");
    strcat(file_destination, user_info.host_name);

    return file_destination;
}
