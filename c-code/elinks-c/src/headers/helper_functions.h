#ifndef HELPER_FUNCTIONS
#define HELPER_FUNCTIONS
#include "./structures.h"

/* Determines whether or not a string contains a dot */
extern int contains_a_dot(char * string);
/* Copies app binary to final url as well 
 * as runs add_elinks_config_to_final_url*/
extern void create_base_url(UserEntry * user_search);
/* Conditionally adds elinks config path to final url */
extern void add_elinks_config_to_final_url(UserEntry * user_entry);
extern void send_error_to_dev_null(UserEntry * user_entry);
extern void print_help_message(char * argv0);
extern void create_url_from_args(UserEntry * user_entry, int arg_index);
extern int execute_or_print_error(char * command);
/* extern void print_help_message(char * PROGRAM_NAME); */

#endif
