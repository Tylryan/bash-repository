#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
/* This is program finds out what percent your battery is 
 * on and how many hours it is expected to remain powered.
*/

int rounded(double number);
void battery_icon(char * icon, double battery_level);
int main(int argc, char * argv[]){
    (void) argc;
    (void) argv;
    FILE *fp;
    double charge_now;
    double charge_full;
    double current_now;
    /* char state[50]; */
    //TODO Check if currently charging
    // printf hours remaining option

    fp = fopen("/sys/class/power_supply/BAT0/charge_now", "r");
    fscanf(fp, "%lf", &charge_now);
    fclose(fp);

    fp = fopen("/sys/class/power_supply/BAT0/charge_full","r");
    fscanf(fp, "%lf", &charge_full);
    fclose(fp);

    fp = fopen("/sys/class/power_supply/BAT0/current_now", "r");
    fscanf(fp, "%lf", &current_now);
    fclose(fp);

    /* fp = fopen("/sys/class/power_supply/BAT0/state", "r"); */
    /* fscanf(fp, "%s", state); */
    /* fclose(fp); */

    /* int args_entered = argc > 1; */
    /* if (args_entered) { */
    /*     int clicked = strcmp(argv[1], "--click") == 0; */
    /*     int discharging = strcmp(state, "Discharging") == 0; */
    /*     if (clicked && discharging) { */
    /*         double hours_remaining = charge_now / current_now; */
    /*         printf("%.2lf", hours_remaining); */
    /*         exit(EXIT_SUCCESS); */
    /*     } */
    /* } */
    double battery_remaining_percent = charge_now / charge_full * 100;
    int rounded_battery_percent = rounded(battery_remaining_percent);

    char battery_icon_image[8] = "";
    battery_icon(battery_icon_image, battery_remaining_percent);
    printf("%s %d%%", battery_icon_image, rounded_battery_percent);
}


int rounded(double number){
    int rounded = (int) (number + 0.5);
    return rounded;
}

void battery_icon(char * icon, double battery_level){

    // No decent switches allowed
    char * full = "  ";
    char * quarters = " ";
    char * half = " ";
    char * quarter= " ";
    char * empty = " ";

    int is_full = battery_level == 100;
    int is_quarters = battery_level >= 75;
    int is_half = battery_level >= 50;
    int is_quarter = battery_level >= 25;
    int is_empty = battery_level < 5;

    if (is_full) strcpy(icon, full);
    else if (is_quarters) strcpy(icon,quarters);
    else if (is_half) strcpy(icon, half);
    else if (is_quarter) strcpy(icon, quarter);
    else if (is_empty) strcpy(icon, empty);
}
