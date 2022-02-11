#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h> 

/* #include "../src/main_functions.c" */
#include "../src/helper_functions.c"
#include "../src/headers/structures.h"

int test_contains_a_dot();
int test_add_elinks_config_to_final_url();
int test_create_url_from_args();
int test_create_base_url();

int main()
{

    printf("============== HELPER FUNCTIONS ================\n");
    test_contains_a_dot();
    test_add_elinks_config_to_final_url();
    test_create_base_url();
    test_create_url_from_args();
    /* test_run_as_complete_url(); */
    printf("\n============== MAIN FUNCTIONS ================\n");

    exit(EXIT_SUCCESS);
}

int test_contains_a_dot()
{
    // Does contain a dot
    char * string_one   = "helllo.";
    char * string_two   = ".hello";
    char * string_three = "hell.o";

    // Does NOT contain a dot
    char * string_four  = "hello";

    assert(contains_a_dot(string_one)   == 1);
    assert(contains_a_dot(string_two)   == 1);
    assert(contains_a_dot(string_three) == 1);
    assert(contains_a_dot(string_four)  == 0);
    printf("test_contains_a_dot:\t\t\tPASS\n");

    return 0;

}

int test_add_elinks_config_to_final_url()
{


    char * elinks_config = "-config-dir ~/.config/elinks ";
    char * browser_one = "elinks ";
    char * browser_two = "otter-browser ";

    /////////////////// SETUP /////////////////////////
    // Final url should be  browser1 + elinks_config
    UserEntry user1 = {
        .application_binary = strdup(browser_one),
        .elinks_config_path = strdup(elinks_config),
        .final_url          = malloc(100)
    };

    /* strcpy(user1.final_url, ""); */
    /////////////////// TESTING FUNCTION /////////////////////////
    // Final url should be the same as its application binary
    add_elinks_config_to_final_url(&user1);

    // expected final_url "-config-dir ..."
    char * expected_user1_final_url = malloc(100);
    expected_user1_final_url = strcpy(expected_user1_final_url, elinks_config);
    assert(strcmp(user1.final_url, expected_user1_final_url) == 0);

    free(user1.application_binary);
    free(user1.elinks_config_path);
    free(user1.final_url);
    free(expected_user1_final_url);

    /////////////////// SETUP 2 ////////////////////////////////
    UserEntry user2 = {
        .application_binary = strdup(browser_two),
        .elinks_config_path = strdup(elinks_config),
        .final_url          = malloc(100)
    };

    strcpy(user2.final_url, "");

    add_elinks_config_to_final_url(&user2);
    // expected final url = ""
    char * expected_user2_final_url = "";

    assert(strcmp(user2.final_url, expected_user2_final_url) == 0);

    free(user2.application_binary);
    free(user2.elinks_config_path);
    free(user2.final_url);

    printf("test_add_elinks_config_to_final_url:\tPASS\n");

    return 0;
}

// this just copies the result of add_elinks_config_to_final_url
// to 
int test_create_base_url()
{

    char * elinks_config = "-config-dir ~/.config/elinks ";
    char * browser_one = "elinks ";
    char * browser_two = "otter-browser ";

    /////////////////// SETUP /////////////////////////
    UserEntry user1 = {
        .application_binary = strdup(browser_one),
        .elinks_config_path = strdup(elinks_config),
        .final_url          = malloc(100)
    };

    create_base_url(&user1);

    ////////////////// TEST 1 ////////////////////////////

    char expected_final_url1[100];
    strcpy(expected_final_url1, user1.application_binary);
    strcat(expected_final_url1, user1.elinks_config_path);
    // elinks config-dir /path/to/config
    int expected_matches_actual = strcmp(expected_final_url1, user1.final_url) == 0;
    assert(expected_matches_actual);

    free(user1.application_binary);
    free(user1.elinks_config_path);
    free(user1.final_url);

    /////////////////// SETUP 2 /////////////////////////
    UserEntry user2 = {
        .application_binary = strdup(browser_two),
        .elinks_config_path = strdup(elinks_config),
        .final_url          = malloc(100)
    };

    create_base_url(&user1);

    ////////////////// TEST 1 ////////////////////////////

    // otter-browser
    char expected_final_url2[100];
    strcpy(expected_final_url2, browser_two);

    int expected_matches_actual2 = strcmp(expected_final_url2, user2.final_url) == 0;
    assert(expected_matches_actual2);

    free(user1.application_binary);
    free(user1.elinks_config_path);
    free(user1.final_url);

    printf("test_create_base_url:\t\t\tPASS\n");

    return 0;

}

int test_create_url_from_args()
{
    char * args[] = {"hello"};

    UserEntry user1 = {
        .args = args,
        .search_terms = calloc(100, 1)
    };

    char * expected_output = "hello+";
    create_url_from_args(&user1, 0);

    int expected_matches_actual = strcmp(expected_output, user1.search_terms) == 0;
    assert(expected_matches_actual);

    printf("test_create_url_from_args:\t\tPASS\n");
    return 0;

}
