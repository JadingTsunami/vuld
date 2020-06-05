/*
 * File and File Selection Utilities
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

#ifndef _FILEUTIL_H
#define _FILEUTIL_H

#include <stdbool.h>

#if (__APPLE__ || __linux__ )
#define PATHSEP '/'
#else
#define PATHSEP '\\'
#endif

struct file_list
{
    char* name;
    struct file_list* next;
};

void add_file( struct file_list* head, char* name );
void destroy( struct file_list* head );
int choose_number(char* prompt, int max_tries, int least, int most, bool print_range);
struct file_list* choose_file( struct file_list* head, char* prompt, int max_files_per_screen );
int run_command(char* cmd);
int find_files( char* fdir, char* fextension, struct file_list* fhead );
void clear_screen();
bool does_file_exist(char* path_to_file);

#endif
