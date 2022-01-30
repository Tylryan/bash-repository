#include <stdio.h>
#include <string.h>
#include <stdlib.h> // EXIT_SUCCESS/EXIT_FAILURE
#include <libgen.h>
#include "./structures.c"


#define TRUE 1
#define FALSE 0

char * RUN_IN_BACKGROUND = " &";

void print_help_message(char * PROGRAM_NAME);
int contains_a_dot(char * string, int str_len);
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
        user_entry.final_url = realloc(user_entry.final_url, 25 * sizeof(char) );
        create_base_url(&user_entry);

         if (user_entry.use_gui)
             strcat(user_entry.final_url, RUN_IN_BACKGROUND);
        execute_or_print_error(user_entry.final_url);
}
void run_as_complete_url(UserEntry user_entry, int start_of_args){
        size_t url_len = 4 * strlen(user_entry.args[start_of_args]);
        char * first_argument = user_entry.args[start_of_args];

        if (strlen(first_argument) > 150) {
            printf("Error: Url is too big\n");
            exit(EXIT_FAILURE);
        }
         strcat(user_entry.final_url,user_entry.application_binary);

         user_entry.final_url = realloc(user_entry.final_url, url_len * sizeof(char));

         // Will only add config if application chosen is elinks */
         add_elinks_config_to_final_url(&user_entry); 

         char * url = first_argument;
         // Max url length is 100 */
         user_entry.final_url = realloc(user_entry.final_url, 75 * sizeof(char)); 
         strcat(user_entry.final_url, url);

         if (user_entry.use_gui)
             strcat(user_entry.final_url, RUN_IN_BACKGROUND);

         execute_or_print_error(user_entry.final_url);


}
void run_as_search_query(UserEntry user_entry){
        // Turning args into "arg1+arg2+arg3"
        int arg_index = 1;
        if (user_entry.has_flag) 
            arg_index = 2;
        for (;arg_index < user_entry.arg_num; arg_index++){
            create_url_from_args(&user_entry, arg_index);
        }

        user_entry.final_url = realloc(user_entry.final_url, 250 * sizeof(char));
        strcat(user_entry.final_url, user_entry.application_binary);
        add_elinks_config_to_final_url(&user_entry);
        strcat(user_entry.final_url, user_entry.base_search);
        strcat(user_entry.final_url, user_entry.search_terms);

         if (user_entry.use_gui)
             strcat(user_entry.final_url, RUN_IN_BACKGROUND);
        execute_or_print_error(user_entry.final_url);
}


// Does the string contain a dot?
int contains_a_dot(char * string, int str_len){
    for (int i = 0; i < str_len; i++) 
        if (string[i] == '.') return TRUE;
    return FALSE;
}

// Boy this was a pain to figure out.
// Must pass reference to change outside values, duh
void create_base_url(UserEntry * user_entry){
    strcpy(user_entry -> final_url, user_entry -> application_binary); 
    add_elinks_config_to_final_url(user_entry); 
    /* strcat(user_entry -> final_url, user_entry -> elinks_config_path); */
}

void send_error_to_dev_null(UserEntry * user_entry){
    if (user_entry -> use_gui == FALSE){
        strcat(user_entry -> final_url, " 2>/dev/null");
    }
    else {
        strcat(user_entry -> final_url, " 2>/dev/null &");
    }
}


void create_url_from_args(UserEntry * user_entry, int arg_index){
    strcat(user_entry -> search_terms, user_entry -> args[arg_index]);
    // Don't add "+" to the last argument
    int last_argument = user_entry -> arg_num -1;
    if (arg_index != last_argument) 
        strcat(user_entry -> search_terms, "+");

}

int execute_or_print_error(char * command){
        int error;
        if ((error = system(command) != 0)) 
            // Could also use strerror(errno)
            perror("");
        return 0;
}

void add_elinks_config_to_final_url(UserEntry * user_entry){
    int is_elinks = strcmp(user_entry -> application_binary, "elinks ") == 0;
    if (is_elinks == TRUE) 
        strcat( user_entry -> final_url, user_entry -> elinks_config_path );
}

void free_all_memory(UserEntry user_entry){
    // Free the memory of the entire struct
    free(user_entry.application_binary);
    free(user_entry.final_url);
}

void print_help_message(char * argv0){
    char * program_name = basename(argv0);
    printf("USAGE\n\
\t%s [options] [website-url]\n\
\t%s [options] [your-question]\n\
DESCRIPTION\n\
\tSearches the web from your terminal using Elinks.\n\
OPTIONS\n\
\tNo args is equivalent to running \"elinks\".\n\
\t-h\t--help  \tShows this message and exits.\n\
\t-g\t--google\tRuns Google's (Default Duckduckgo) with Elinks.\n\
\t-o\t--otter \tRuns otter-browser instead of elinks.\n\
EXAMPLES\n\
\t%s google.com\n\
\t%s how big is the moon?\n", 
program_name,program_name, program_name, program_name
);
}

int options_parser(UserEntry * user_entry){
    char * program_name = user_entry -> args[0];
    if (user_entry->arg_num > 1){
        int needs_help = (
                (strcmp(user_entry->flag, "-h") == 0 || 
                (strcmp(user_entry -> flag, "--help") == 0))
                    );
        int wants_gui_browser = (
                (strcmp(user_entry -> flag, "-o")      == 0) || 
                (strcmp(user_entry -> flag, "--otter") == 0)
                    );
        int wants_google_search_engine = (
                (strcmp(user_entry -> flag, "-g")       == 0) ||
                (strcmp(user_entry -> flag, "--google") == 0)
                    );
        if (needs_help){
            // todo stack smashing here
            print_help_message(program_name);
            exit(EXIT_SUCCESS);
        } 
        if (wants_gui_browser){
            // todo free this
            user_entry -> application_binary = realloc(user_entry -> application_binary, 25 * sizeof(char));
            strcpy(user_entry -> application_binary, user_entry->alternative_gui_browser);
            user_entry -> has_flag = 1;
            user_entry -> use_gui = 1;
        } else {
            user_entry -> application_binary = "elinks ";
        }

        user_entry -> base_search = realloc(
                user_entry -> base_search, 40 * sizeof(char));

        if (wants_google_search_engine){
            user_entry -> search_engine = google;
            user_entry -> base_search = "google.com/search?q=";
            user_entry -> has_flag = 1;
        } else {
            user_entry -> base_search = "duckduckgo.com/?q=";
        }

    } else {
    user_entry -> application_binary = "elinks ";
    user_entry -> base_search = "duckduckgo.com/?q=";
    }

    return 0;
}
