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
    enum gametype game_found = GAME_NONE;

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

    /* check for game files */

    /* check for an executable */
    /* at each point, we expect to see only ONE
     * set of game files. If anything is incomplete
     * or we find multiple sets, return GAME_MULTIPLE
     * immediately, as no support for multiple
     * games is expected
     */
    tmpdir[pathloc] = '\0';
    strcat( tmpdir, "DOOM.EXE" );

    if ( does_file_exist( tmpdir ) ) {
        game_found = GAME_DOOM;
    }

    tmpdir[pathloc] = '\0';
    strcat( tmpdir, "DOOM2.EXE" );

    if ( does_file_exist( tmpdir ) ) {
        if( game_found == GAME_NONE ) {
            game_found = GAME_DOOM2;
        } else {
            return GAME_MULTIPLE;
        }
    }

    /* check for an IWAD */

    tmpdir[pathloc] = '\0';
    strcat( tmpdir, "DOOM.WAD" );

    if( !does_file_exist( tmpdir ) && game_found == GAME_DOOM ) {
        /* found a DOOM.EXE but no commercial IWAD. */
        return GAME_MULTIPLE;
    }

    tmpdir[pathloc] = '\0';
    strcat( tmpdir, "DOOM1.WAD" );
    if( does_file_exist( tmpdir ) ) {
        /* we have a Shareware IWAD, but no executable. */
        return GAME_MULTIPLE;
    }

    tmpdir[pathloc] = '\0';
    strcat( tmpdir, "DOOM2.WAD" );

    if( !does_file_exist( tmpdir ) && game_found == GAME_DOOM2 ) {
        /* found a DOOM2.EXE but no IWAD */
        return GAME_MULTIPLE;
    }

    return game_found;
}
