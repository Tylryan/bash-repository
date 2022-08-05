#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* A simple program to figure out a laptop's battery level.
 * Designed to help me learn C.
 * Requires fontawesome
*/
void set_battery_icon(char * icon, int battery_level);

int main()
{
    int capacity;
    char battery_icon[10];

    FILE * fp;
    const char * capacity_path = "/sys/class/power_supply/BAT0/capacity";

    if ((fp = fopen(capacity_path, "r")) == NULL)
    {
        perror(capacity_path);
        exit(EXIT_FAILURE);
    }

    fscanf(fp, "%d", &capacity);
    fclose(fp);

    set_battery_icon(battery_icon, capacity);
    printf("%s %d%%\n", battery_icon, capacity);

    exit(EXIT_SUCCESS);
}

void set_battery_icon(char * icon, int battery_level)
{
    // No decent switches allowed
    char * full     = "  ";
    char * quarters = "  ";
    char * half     = "  ";
    char * quarter  = "  ";
    char * empty    = "  ";

    int is_full     = battery_level == 100;
    int is_quarters = battery_level >= 75;
    int is_half     = battery_level >= 50;
    int is_quarter  = battery_level >= 10;
    int is_empty    = battery_level < 10;

    if      (is_full)     strcpy(icon, full);
    else if (is_quarters) strcpy(icon, quarters);
    else if (is_half)     strcpy(icon, half);
    else if (is_quarter)  strcpy(icon, quarter);
    else if (is_empty)    strcpy(icon, empty);
}
