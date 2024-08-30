#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct config {
    char **commands;
    int num_commands;
};

struct config read_config();
