/*
 * Game-related Utilities
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


#include "gameutil.h"

#include "fileutil.h"
#include "genutil.h"


#include <string.h>

enum gametype check_for_game(char* directory)
{
    char tmpdir[MAX_PATH];
    int pathloc = 0;

    if ( strlen(directory) >= MAX_PATH-1 )
        return GAME_NONE;

    strcpy( tmpdir, directory );

    pathloc = strlen(tmpdir)-1;
    
    if ( pathloc > 0 && pathloc+2 < MAX_PATH && directory[pathloc] != PATHSEP_CHAR &&
         (strcmp(tmpdir,".") != 0)) {
        strcat( tmpdir, PATHSEP_STR );
        pathloc++;
    }

    if ( pathloc < 0 )
        return GAME_NONE;
    else if( pathloc != 0 )
        pathloc++;

    /* need enough space left for an 8.3 filename + null terminator */
    if ( (pathloc + 8 + 1 + 3 + 1) >= MAX_PATH )
        return GAME_NONE;

    /* check for doom files */
    tmpdir[pathloc] = '\0';
    strcat( tmpdir, "DOOM.EXE" );

    if ( does_file_exist( tmpdir ) ) {
        tmpdir[pathloc] = '\0';
        strcat( tmpdir, "DOOM.WAD" );

        if( does_file_exist( tmpdir ) ) {
            return GAME_DOOM;
        }
    }

    /* check for doom2 files */
    tmpdir[pathloc] = '\0';
    strcat( tmpdir, "DOOM2.EXE" );

    if ( does_file_exist( tmpdir ) ) {
        tmpdir[pathloc] = '\0';
        strcat( tmpdir, "DOOM2.WAD" );

        if( does_file_exist( tmpdir ) ) {
            return GAME_DOOM2;
        }
    }

    /* didn't find any valid game */
    return GAME_NONE;
}
