#ifndef _VULD_DEBUG_H
#define _VULD_DEBUG_H

#include <stdbool.h>

#define DEBUG_FILENAME ("debug.log")

void debug_print(char* str);
void set_debug(bool debug_mode);

#endif
