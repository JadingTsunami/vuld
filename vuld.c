/*
 * VULD Main Program
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
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

#include "fileutil.h"
#include "genutil.h"
#include "gameutil.h"

#define VULD_SUBDIR "vuld_dir"

#define RET_ERROR (-1)

/* 2 modes:
 * 1. Launcher mode: Find all dirs with .deh and .wad, give user a choice, merge dehs, deusf/detex the wads and run
 *      - 1st WAD gets appended, rest are merged
 * 2. INI mode: Select all deh/wad from "packs" specified in an INI file
 *      [pack name]
 *      game = doom|doom2
 *      launch = yes|no
 *      launch_args = whatever
 *      xxx.deh
 *      yyy.deh
 *      zzz.deh
 *      ...
 *      aaa.wad
 *      bbb.wad
 *      ccc.wad
 *      ...
 */
int main(int argc, char** argv)
{
    /* DOS files are 8.3 plus null terminator */
    char deh_prog[8 + 1 + 3 + 1];
    char deusf_prog[8 + 1 + 3 + 1];

    /* we need at least dehacked and deusf or deutex */
    if ( does_file_exist("dehacked.exe") ) {
        strcpy(deh_prog,"dehacked.exe");
    } else {
        fprintf(stderr, "Error: No DEHACKED.EXE found.\n");
        return RET_ERROR;
    }

    if (does_file_exist("deusf.exe")) {
        strcpy(deusf_prog,"deusf.exe");
    } else if (does_file_exist("deutex.exe")) {
        strcpy(deusf_prog,"deutex.exe");
    } else {
        fprintf(stderr, "Error: No DEUSF.EXE or DEUTEX.EXE found.\n");
        return RET_ERROR;
    }

    /* check if we have a vuld subdirectory,
     * create one if we do not 
     */
    DIR* d = opendir( VULD_SUBDIR );

    if( !d ) {
        if ( mkdir( VULD_SUBDIR, S_IRWXU ) != 0 ) {
            fprintf(stderr, "Error: Could not create %s subdirectory.\n", VULD_SUBDIR);
            return RET_ERROR;
        } else {
            d = opendir( VULD_SUBDIR );
            if ( !d ) {
                fprintf(stderr, "Error: Could not open %s subdirectory.\n", VULD_SUBDIR);
                return RET_ERROR;
            }
        }
    }

    closedir(d);

    /* check for doom or doom2 game files */
    enum gametype game = check_for_game(".");

    if( game == GAME_NONE ) {
        fprintf(stderr, "Error: Did not find a game in the current directory.\n");
        fprintf(stderr, "Make sure you run %s from your game directory.\n", argv[0]);
        return RET_ERROR;
    }

    /* if an INI is specified, use it, else go into launcher mode */
    if ( argc > 1 ) {
        /* INI mode */
        /* TODO: Implement */
    } else {
        /* Launcher mode */
        /* For each directory */
        d = opendir( "." );

        if ( !d ) {
            fprintf(stderr, "Error: Could not open current directory.\n");
            return RET_ERROR;
        }

        struct dirent* dirfile;
        struct stat statbuf;
        char* strfile;
        while ( (dirfile = readdir(d)) != NULL ) {
            strfile = dirfile->d_name;
            if (stat(strfile, &statbuf) != 0)
                continue;
            else if S_ISDIR(statbuf.st_mode) {
                /* Grab all DEH patches */
                /* Grab all WAD files */
            }

        }

        closedir(d);


        /* Have the user pick one */
        /* Merge all DEH patches */
        /* Merge all WAD files */

    }
    /* Launch it */
    return 0;
}
