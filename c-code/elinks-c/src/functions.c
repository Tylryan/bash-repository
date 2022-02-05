#include <stdio.h>
#include <string.h>
#include <stdlib.h> // EXIT_SUCCESS/EXIT_FAILURE
#include <libgen.h>
#include "./headers/structures.h"
#include <assert.h>


#define TRUE 1
#define FALSE 0


char * RUN_IN_BACKGROUND = " &";

void print_help_message(char * PROGRAM_NAME);
int contains_a_dot(char * string);
void create_base_url(UserEntry * user_search);
void send_error_to_dev_null(UserEntry * user_entry);
void print_help_message(char * argv0);
void create_url_from_args(UserEntry * user_entry, int arg_index);
int execute_or_print_error(char * command);
void add_elinks_config_to_final_url(UserEntry * user_entry);
void free_all_memory(UserEntry user_entry);
int options_parser(UserEntry * user_entry);
void run_with_no_args(UserEntry user_entry);
void run_as_complete_url(UserEntry user_entry, int start_of_args);
void run_as_search_query(UserEntry user_entry);

// ###################### FUNCTION INITIALIZATION ############################

void run_with_no_args(UserEntry user_entry){

        create_base_url(&user_entry);
         if (user_entry.use_gui)
             strcat(user_entry.final_url, RUN_IN_BACKGROUND);

        execute_or_print_error(user_entry.final_url);
        return;

}
void run_as_complete_url(UserEntry user_entry, int start_of_args){

         char * first_argument    = user_entry.args[start_of_args];
         const int MAX_URL_LENGTH = 150;

         int url_is_too_long      = (int) strlen(first_argument) > MAX_URL_LENGTH;
         if (url_is_too_long) {
            fprintf(stderr, "Error create_url_from_args() : Query too large\n");
            exit(EXIT_FAILURE);
         }

         user_entry.final_url = realloc(user_entry.final_url, MAX_URL_LENGTH);
         strcat(user_entry.final_url,user_entry.application_binary);
         // Will only add config if application chosen is elinks */
         add_elinks_config_to_final_url(&user_entry); 

         char * url = first_argument;
         strcat(user_entry.final_url, url);

         if (user_entry.use_gui)
             strcat(user_entry.final_url, RUN_IN_BACKGROUND);

         execute_or_print_error(user_entry.final_url);

         return;

}
void run_as_search_query(UserEntry user_entry){

        int BASE_URL_LENGTH   = 75;
        int MAX_SEARCH_LENGTH = 200;
        int MAX_URL_LENGTH    = BASE_URL_LENGTH + MAX_SEARCH_LENGTH;

        int arg_index = 1;
        if (user_entry.has_flag) 
            arg_index = 2;

        user_entry.search_terms = realloc(user_entry.search_terms, MAX_SEARCH_LENGTH);
        // Turning args into "arg1+arg2+arg3"
        for (;arg_index < user_entry.arg_num; arg_index++){

            int search_length_too_large = (int) strlen(user_entry.search_terms) > MAX_SEARCH_LENGTH;

            if (search_length_too_large) {
                fprintf(stderr, "Error create_url_from_args() : Query too large\n");
                exit(EXIT_FAILURE);
            }

            create_url_from_args(&user_entry, arg_index);
        }


        user_entry.final_url = realloc(user_entry.final_url, MAX_URL_LENGTH);
        strcat(user_entry.final_url, user_entry.application_binary);
        add_elinks_config_to_final_url(&user_entry);
        strcat(user_entry.final_url, user_entry.base_search);

        {
            int url_len_before_search = (int) strlen(user_entry.final_url);
            assert(url_len_before_search < BASE_URL_LENGTH);
        }

        strcat(user_entry.final_url, user_entry.search_terms);

        if (user_entry.use_gui)
             strcat(user_entry.final_url, RUN_IN_BACKGROUND);

        execute_or_print_error(user_entry.final_url);

        return;
}


/* Eventually, I want to replace this with a less general "contains"*/
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
    if (user_entry -> use_gui == FALSE){
        strcat(user_entry -> final_url, " 2>/dev/null");
    }
    else {
        strcat(user_entry -> final_url, " 2>/dev/null &");
    }

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

void add_elinks_config_to_final_url(UserEntry * user_entry){
    int is_elinks = strcmp(
            user_entry -> application_binary, "elinks ") == 0;
    if (is_elinks == TRUE) 
        strcat(user_entry -> final_url, user_entry -> elinks_config_path);
}

void free_all_memory(UserEntry user_entry){
    // Free the memory of the entire struct
    free(user_entry.application_binary);
    free(user_entry.final_url);
    return;
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

int options_parser(UserEntry * user_entry){
    char * program_name = user_entry -> args[0];
    if (user_entry -> arg_num > 1){

        int needs_help = (
                (strcmp(user_entry -> flag, "-h")      == 0)  || 
                (strcmp(user_entry -> flag, "--help")  == 0));

        int wants_gui_browser = (
                (strcmp(user_entry -> flag, "-o")       == 0) || 
                (strcmp(user_entry -> flag, "--otter")  == 0));

        int wants_google_search_engine = (
                (strcmp(user_entry -> flag, "-g")       == 0) ||
                (strcmp(user_entry -> flag, "--google") == 0));
        if (needs_help){
            // todo stack smashing here
            print_help_message(program_name);
            exit(EXIT_SUCCESS);
        } 
        if (wants_gui_browser){
            // todo free this
            strcpy(
                    user_entry -> application_binary, 
                    user_entry -> alternative_gui_browser);

            user_entry -> has_flag = 1;
            user_entry -> use_gui = 1;
        } else 
            user_entry -> application_binary = "elinks ";

        if (wants_google_search_engine){
            user_entry -> search_engine  = google;
            user_entry -> base_search    = "google.com/search?q=";
            user_entry -> has_flag       = 1;
        } else
            user_entry -> base_search    = "duckduckgo.com/?q=";

    } else {
        user_entry -> application_binary = "elinks ";
        user_entry -> base_search        = "duckduckgo.com/?q=";
    }

    return 0;
}
