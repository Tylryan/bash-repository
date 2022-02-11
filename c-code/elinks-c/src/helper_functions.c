#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libgen.h>
#include <unistd.h>

//
#include "headers/structures.h"
/* #include "headers/main_functions.h" */

#ifndef TRUE
#define TRUE  1
#endif


#ifndef FALSE
#define FALSE 0
#endif

/* Eventually, I want to replace this with a less general "contains"*/
void add_elinks_config_to_final_url(UserEntry * user_entry){
    int is_elinks = strcmp(
            user_entry -> application_binary, "elinks ") == 0;
    if (is_elinks == TRUE) 
        strcat(user_entry -> final_url, user_entry -> elinks_config_path);
    return;
}

int contains_a_dot(char * string){
    for (int i = 0; i < (int) strlen(string); i++) 

        if (string[i] == '.') 
            return TRUE;

    return FALSE;
}

// Boy this was a pain to figure out.
// Must pass reference to change outside values, duh
void create_base_url(UserEntry * user_entry){
    strcpy(user_entry -> final_url, user_entry -> application_binary); 
    add_elinks_config_to_final_url(user_entry); 
    return;
}

void send_error_to_dev_null(UserEntry * user_entry){
    if (user_entry -> use_gui == FALSE)
        strcat(user_entry -> final_url, " 2>/dev/null");
    else 
        strcat(user_entry -> final_url, " 2>/dev/null &");

    return;
}


void create_url_from_args(UserEntry * user_entry, int arg_index){
    strcat(user_entry -> search_terms, user_entry -> args[arg_index]);
    // Don't add "+" to the last argument
    int last_argument = user_entry -> arg_num -1;
    if (arg_index != last_argument) 
        strcat(user_entry -> search_terms, "+");

    return;
}

int execute_or_print_error(char * command){
        int error;
        if ((error = system(command) != 0)) {
            perror("");
            exit(EXIT_FAILURE);
        }
        return 0;

}


void print_help_message(char * argv0){
    char * program_name = basename(argv0);
    printf("USAGE\n\
    %s [options] [website-url]\n\
    %s [options] [your-question]\n\
DESCRIPTION\n\
    Searches the web from your terminal using Elinks.\n\
OPTIONS\n\
    No args is equivalent to running \"elinks\".\n\
    -h\t--help  \tShows this message and exits.\n\
    -g\t--google\tRuns Google's (Default Duckduckgo) with Elinks.\n\
    -o\t--otter \tRuns otter-browser instead of elinks.\n\
EXAMPLES\n\
    %s google.com\n\
    %s how big is the moon?\n", 
    program_name, program_name, program_name, program_name
);

    return;
}

