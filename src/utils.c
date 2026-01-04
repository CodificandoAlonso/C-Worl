//
// Created by hectoralv22 on 1/4/26.
//

#include "../include/utils.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *check_mem_alloc(void *mem_to_check, const char *error_type)
{

    if (mem_to_check == NULL)
    {
        fprintf(stderr, "ERROR ALLOCATING MEMORY %s\n", error_type);
        _exit(EXIT_FAILURE);
    }
    return NULL;
}

void *throw_error(const char *error_type)
{
    fprintf(stderr, "ERROR%s\n", error_type);
    _exit(EXIT_FAILURE);
}
