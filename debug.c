/*
 * Debug Helper Functions
 *
 * Copyright (C) 2020  Jading Tsunami
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

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
