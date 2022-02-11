#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers/structures.h"
#include "headers/helper_functions.h"

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
