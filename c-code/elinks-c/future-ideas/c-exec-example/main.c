#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "structs.h"

int main(int argc, char ** argv)
{
    (void) argc;
    user_t user_info = 
    {
        .home                  = getenv("HOME"),
        .path_to_elinks_config = "/.config/elinks",
        .path_to_binaries      = "/usr/bin",
        .application_path      = malloc(sizeof(char) * 25),
        .elinks_options        = malloc (
                strlen(user_info.home) +
                strlen(user_info.path_to_elinks_config) + 15
                )
    };
    entry_t entry_info =
    {
        .chosen_application = "/elinks",
        .args               = argv[1]
    };

    strcpy(user_info.application_path, user_info.path_to_binaries);
    strcat(user_info.application_path, entry_info.chosen_application);

    strcpy(user_info.elinks_options, user_info.home);
    strcat(user_info.elinks_options,user_info.path_to_elinks_config);

    int exec_status;
    if ((exec_status = execl(
                    user_info.application_path, 
                    user_info.elinks_options, 
                    entry_info.args, (char *) NULL)) != 0)
    {
        perror(user_info.application_path);
        exit(EXIT_FAILURE);
    };

    free(user_info.application_path);
    free(user_info.elinks_options);

    exit(EXIT_SUCCESS);
}
