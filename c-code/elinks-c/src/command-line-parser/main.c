#include <stdio.h>
#include <string.h>
#include <stdlib.h>

 /* 
 * run `./a.out hello there -hmad` in the command line as an example
 * run `./a.out --hello there partner` to see a limitation
 * run `./a.out hello -asf there partner -dqw` to see another limitation
 */

int contains(char * string, char character);
int find_option_index(int argc, char ** args);
void options_parser(char ** argv, int option_index);
void args_without_options(int argc, char ** args, int option_index);
void long_options_parser(int argc, char ** argv, int len_lo, char ** long_options);

char *long_options[] = {
    "--help", "--enter"
};
int main(int argc, char ** argv)
{
    printf("All the options\n");

    int option_index;
    if ((option_index = find_option_index(argc, argv)) != 0){
        options_parser(argv, option_index);
    };

    printf("All the arguments\n");

    args_without_options(argc, argv, option_index);
    // Example of long option parser
    /* long_options_parser(argc, argv, 2, long_options); */


    exit(EXIT_SUCCESS);
}

/* Only deals with arguments from a command line entry*/
void args_without_options(int argc, char ** args, int option_index)
{
    int has_options = option_index != 0;
    int no_args = has_options && argc == 2;
    if (no_args)
        return;

    int i;
    for (i = 1; i < argc; i++)
    {
        if (i == option_index)
            continue;
        printf("%s\n", args[i]);
    }
    return;
}

/* Only deals with options from a command line entry*/
void options_parser(char ** argv, int option_index)
{
    char * options = argv[option_index];
    int i;
    for (i = 1; i < (int) strlen(options); i++)
        printf("%c\n", options[i]);

    return;
}
/* Ideally you would pass in a struct that contains all of this information*/
void long_options_parser(int argc, char ** argv, int len_lo, char ** long_options)
{
    int i,j;

    for (i = 0; i < len_lo; i++)
        for (j = 1; j < argc; j++)
        {
            int matches = strcmp(argv[j], long_options[i]) == 0;
            if (matches)
                printf("LO Index: %d\n%s",j, argv[j]);
        }
    return;


}
/* Returns the index of the option flag or 0 if no options passed*/
int find_option_index(int argc, char ** args)
{
    int i;
    for (i = 1; i < argc; i++)
    {
        int not_url = contains(args[i], '.') == 0;
        int has_option = contains(args[i], '-');

        if (not_url && has_option)
            return i;
    }
    return 0;
}

/* Returns 1 if string contains char, 0 if not*/
int contains(char * string, char character)
{
    char ch;
    int i = 0;
    do {
        ch = string[i];
        if (ch == character)
            return 1;
        i++;
    } while (ch != '\0');
    return 0;
}
