/*
 * INI File Utilities
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

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "iniutil.h"
#include "genutil.h"

bool find_in_file(FILE* f, char* target, bool exact, int max_lines)
{
    char l[MAX_LINESIZE];
    int i = 0;
    int target_len = strlen(target);
    int lines_read = 0;
    if( target == NULL || f == NULL ) return false;

    while( (!feof(f) && !ferror(f)) || (lines_read >= max_lines) ) {
        lines_read++;
        if( fgets(l,MAX_LINESIZE,f) != NULL ) {

            if( exact ) {
                for( i = strlen(l)-1; i >= 0; i-- ) {
                    if( !isspace(l[i]) )
                        break;
                }
                if( i > 0 )
                    l[i+1] = '\0';
                if( strcmp(l, target) == 0 )
                    return true;
            } else {

                /* skip over whitespace */
                for( i = 0; i < strlen(l); i++ )
                    if( l[i] != ' ' )
                        break;

                if( i < strlen(l) &&
                        strlen(&l[i]) >= target_len &&
                        strncmp(&l[i], target, target_len) == 0) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool is_header( char* s )
{
    if( s && s[0] == '[' ) {
        int pos = strlen(s);
        while( pos >= 0 && isspace(s[pos]) )
            pos--;
        return s[pos] == ']';
    }
    return false;
}

bool get_attribute(FILE* f, char* attribute_name, char** attribute_value)
{
    long int fpos = ftell(f);
    char s[MAX_LINESIZE];
    char* token;
    while( (!feof(f) && !ferror(f)) ) {
        fgets(s,MAX_LINESIZE,f);
        if( is_header(s) )
            break;
        token = strtok(s, "=");
        if( strncmp( attribute_name, token, strlen(attribute_name) ) == 0 ) {
            token = strtok( NULL, "=");
            while( *token && isspace(*token) )
                token++;
            *attribute_value = strdup(token);
            return true;
        }
    }
    /* if we didn't find it, rewind */
    fseek(f, fpos, SEEK_SET);
    return false;
}


