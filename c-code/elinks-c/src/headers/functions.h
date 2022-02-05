#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "./structures.h"

extern int options_parser(UserEntry * user_entry);
extern void run_with_no_args(UserEntry user_entry);
extern void run_as_complete_url(UserEntry user_entry, int start_of_args);
extern void run_as_search_query(UserEntry user_entry);
extern void print_help_message(char * PROGRAM_NAME);
extern int contains_a_dot(char * string);
extern void create_base_url(UserEntry * user_search);
extern void send_error_to_dev_null(UserEntry * user_entry);
extern void print_help_message(char * argv0);
extern void create_url_from_args(UserEntry * user_entry, int arg_index);
extern int execute_or_print_error(char * command);
extern void add_elinks_config_to_final_url(UserEntry * user_entry);
extern void free_all_memory(UserEntry user_entry);




#endif
