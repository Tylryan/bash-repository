#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../src/headers/structures.h"
#include "../src/headers/functions.h"

int test_contains_a_dot();
int test_add_elinks_to_final_url();

int main(){

    printf("============ TESTING ===============\n");
    test_contains_a_dot();
    test_add_elinks_to_final_url();

    exit(EXIT_SUCCESS);
}


int test_contains_a_dot(){
    // Yes
    char * string_one   = "helllo.";
    char * string_two   = ".hello";
    char * string_three = "hell.o";

    // No
    char * string_four  = "hello";

    assert(contains_a_dot(string_one)   == 1);
    assert(contains_a_dot(string_two)   == 1);
    assert(contains_a_dot(string_three) == 1);
    assert(contains_a_dot(string_four)  == 0);
    printf("test_contains_a_dot:\tPASS\n");

    return 0;

}

int test_add_elinks_to_final_url(){

    char * elinks_config = "-config-dir ~/.config/elinks ";

    char * browser_one = "elinks ";
    char * browser_two = "otter-browser ";

    UserEntry user_entry1;
    user_entry1.application_binary = browser_one;
    user_entry1.final_url = malloc(100);

    UserEntry user_entry2;
    user_entry2.application_binary = browser_two;
    user_entry2.final_url = malloc(100);

    create_base_url(&user_entry1);
    create_base_url(&user_entry2);

    char * expected_test_one_string = strcat(user_entry1.application_binary, elinks_config);
    char * expected_test_two_string = browser_two;

    assert(strcmp(user_entry1.final_url, expected_test_one_string) == 0);
    assert(strcmp(user_entry2.final_url, expected_test_two_string) == 0);

    free(user_entry1.final_url);
    free(user_entry2.final_url);
    printf("test_add_elinks_to_final_url:\t PASS\n");

    return 0;

}
