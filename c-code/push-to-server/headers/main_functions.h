#ifndef _MAIN_FUNCTIONS_H
#define _MAIN_FUNCTIONS_H

#include "server_info_t.h"
/* #include "../src/main_functions.c" */

extern int copy_content_to_server_home(server_info_t server_info, char ** argv);
extern int copy_content_to_server_path(server_info_t server_info, char * from_path, char * to_path);

#endif
