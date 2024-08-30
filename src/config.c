#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct config read_config() {
    char *location = "/.config/planewm/planewm.conf";
    char *home = getenv("HOME");

    char *absolute_location = malloc(strlen(location) + strlen(home) + 1);
    strcpy(absolute_location, home);
    strcat(absolute_location, location);

    FILE *file = fopen(absolute_location, "r");
    if (file == NULL) {
        printf("Info: No config file found at %s\n", location);
        struct config empty_config = {NULL, 0};
        return empty_config;
    }

    struct config config;
    config.commands = NULL;
    config.num_commands = 0;

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "EXEC", 4) == 0) {

            char *command = malloc(strlen(line) - 4);
            strcpy(command, line + 5);
            config.commands = realloc(config.commands, (config.num_commands + 1) * sizeof(char *));
            config.commands[config.num_commands] = command;

            printf("Info: Found command %s\n", command);
            config.num_commands++;
        }
    }

    fclose(file);
    return config;
}
