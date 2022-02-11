#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

#include "./headers/functions.h"

#define TRUE 1
#define FALSE 0

// Make sure you add a space at the end
char ALTERNATIVE_GUI_BROWSER[] = "otter-browser ";
char ELINKS_CONFIG_PATH[]      = "-config-dir ~/.config/elinks ";

// #######################  MAIN #############################################
int main(int argc, char *argv[]){

    UserEntry user_entry = {
        .application_binary      = malloc(1 * sizeof(char)), 
        .elinks_config_path      = ELINKS_CONFIG_PATH, 
        .search_engine           = duck, 
        .base_search             = malloc(1 * sizeof(char)), 
        .search_terms            = malloc(1 * sizeof(char)), 
        .arg_num                 = argc, 
        .args                    = argv, 
        .flag                    = argv[1], 
        .has_flag                = FALSE, 
        .use_gui                 = FALSE, 
        .final_url               = malloc(1 * sizeof(char)),
        .alternative_gui_browser = ALTERNATIVE_GUI_BROWSER
    };

    options_parser(&user_entry);

    int entered_no_args = (argc == 1)                   || 
        (argc == 2 && user_entry.search_engine != duck) ||
        (argc == 2 && user_entry.use_gui == TRUE);

    if (entered_no_args) {
        run_with_no_args(user_entry);
        exit(EXIT_SUCCESS);
    }


    int start_of_args = 1;
    if ( user_entry.has_flag ) 
        start_of_args = 2;
    char * first_argument = argv[start_of_args];
    int is_complete_url   = contains_a_dot(first_argument);
    
    if (is_complete_url){
        run_as_complete_url(user_entry, start_of_args);
        exit(EXIT_SUCCESS);
    }

    else {
        run_as_search_query(user_entry);
        exit(EXIT_SUCCESS);
        }

    }
