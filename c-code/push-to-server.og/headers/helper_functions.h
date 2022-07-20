#ifndef _HELPER_FUNCTIONS_H
#define _HELPER_FUNCTIONS_H

/* #include "../src/helper_functions.c" */
#include "server_info_t.h"

extern char * create_base_server_path(server_info_t server_info);
extern char * create_base_scp_options(server_info_t server_info);
extern char * print_help_message(char * argv0);

#endif
