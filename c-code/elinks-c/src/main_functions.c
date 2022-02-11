#include <stdio.h>
#include <string.h>
#include <stdlib.h> // EXIT_SUCCESS/EXIT_FAILURE
#include <libgen.h>
#include <assert.h>
#include <unistd.h>

#include "headers/structures.h"
#include "headers/helper_functions.h"


#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif


char * RUN_IN_BACKGROUND = " &";

void run_with_no_args(UserEntry user_entry);
void run_as_complete_url(UserEntry user_entry, int start_of_args);
void run_as_search_query(UserEntry user_entry);

// ###################### FUNCTION INITIALIZATION ############################

void run_with_no_args(UserEntry user_entry){

        create_base_url(&user_entry);
         if (user_entry.use_gui)
             strcat(user_entry.final_url, RUN_IN_BACKGROUND);

        // elinks config path never works with execl
        execute_or_print_error(user_entry.final_url);
        return;

}
void run_as_complete_url(UserEntry user_entry, int start_of_args){

         char * first_argument    = user_entry.args[start_of_args];
         const int MAX_URL_LENGTH = 150;

         int url_is_too_long = (int) strlen(first_argument) > MAX_URL_LENGTH;
         if (url_is_too_long) {
            fprintf(stderr, 
                    "Error create_url_from_args() : Query too large\n");
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
