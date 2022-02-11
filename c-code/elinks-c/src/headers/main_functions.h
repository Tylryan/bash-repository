#ifndef MAIN_FUNCTIONS
#define MAIN_FUNCTIONS

#include "./structures.h"
#include "./helper_functions.h"

/* extern int options_parser(UserEntry * user_entry); */
extern void run_with_no_args(UserEntry user_entry);
extern void run_as_complete_url(UserEntry user_entry, int start_of_args);
extern void run_as_search_query(UserEntry user_entry);

#endif
