#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

#include "./functions.c"

#define TRUE 1
#define FALSE 0

/* What I've learned from this project is that you don't really need malloc.
 * In fact, most of the time malloc won't allocate n * sizeof() the correct
 * type at all. It allocates 8 bytes regardless of what you type.
 *
 * In addition, when you think you need to realloc, you don't. It will end 
 * up messing things up if you do for some reason.
 */

// Pretty much never allowed to use constants.
char ALTERNATIVE_GUI_BROWSER[] = "otter-browser ";
char ELINKS_CONFIG_PATH[]      = "-config-dir ~/.config/elinks ";

// #######################  MAIN #############################################
int main(int argc, char *argv[]){

    UserEntry user_entry = {
        // application_binary 25
        malloc(1 * sizeof(char)), 
        // elinks_config_path
        ELINKS_CONFIG_PATH, 
        // SearchEngine
        duck, 
        // base_search
        malloc(1 * sizeof(char)), 
        // search_terms 100
        malloc(1 * sizeof(char)), 
        // arg_num
        argc, 
        // args
        argv, 
        //  flag
        argv[1], 
        // has_flag
        0, 
        // use_gui
        0, 
        // final_url 100
        malloc(1 * sizeof(char)),
        ALTERNATIVE_GUI_BROWSER
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
    int is_complete_url   = contains_a_dot(first_argument, strlen(first_argument));
    
    if (is_complete_url){
        run_as_complete_url(user_entry, start_of_args);
        exit(EXIT_SUCCESS);
    }

    else {
        run_as_search_query(user_entry);
        exit(EXIT_SUCCESS);
        }

    }
