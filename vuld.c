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
#include <sys/stat.h>

#include "fileutil.h"
#include "genutil.h"

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
    /* we need at least dehacked and deusf or deutex */
    if ( !does_file_exist("dehacked.exe") ) {
        fprintf(stderr, "Error: No DEHACKED.EXE found.\n");
        return RET_ERROR;
    } else if (!(does_file_exist("deusf.exe")||does_file_exist("deutex.exe")) ) {
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

    /* if an INI is specified, use it, else go into launcher mode */
    if ( argc > 1 ) {
        /* INI mode */
        /* TODO: Implement */
    } else {
        /* Launcher mode */
        /* For each directory */
        /* Grab all DEH patches */
        /* Grab all WAD files */
        /* Merge all DEH patches */
        /* Merge all WAD files */

    }
    return 0;
}
