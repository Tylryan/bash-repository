#ifndef _USER_T
typedef struct user_t 
{
    char * home;
    char * path_to_elinks_config;
    char * path_to_binaries;
    char * elinks_options;
    char * application_path;

} user_t;
#endif

#ifndef _ENTERY_T
typedef struct entry_t
{
    char * chosen_application;
    char * args;

} entry_t;
#endif

