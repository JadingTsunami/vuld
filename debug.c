#include "debug.h"

#include <stdio.h>
#include <stdbool.h>

static bool debug_enabled = false;

void debug_print(char* str)
{
    if( debug_enabled ) {
        FILE* f = fopen(DEBUG_FILENAME,"a");
        if(f) {
            fprintf(f,"%s",str);
            fclose(f);
        }
    }
}

void set_debug(bool debug_mode)
{
    debug_enabled = debug_mode;
}
