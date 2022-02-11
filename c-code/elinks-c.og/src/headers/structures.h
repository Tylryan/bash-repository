#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef enum SearchEngine { duck, google } SearchEngine;

typedef struct UserEntry {
    char *  application_binary;
    char *  elinks_config_path;
    SearchEngine search_engine;
    char *  base_search;
    char *  search_terms;
    int arg_num;
    char ** args;
    char *  flag;
    int has_flag;
    int use_gui;
    char *  final_url;
    char *  alternative_gui_browser;
} UserEntry;

#endif
