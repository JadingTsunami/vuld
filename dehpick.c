/*
 * DOS-Compatible DeHackEd File Loader
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
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "fileutil.h"
#include "genutil.h"

int main(int argc, char** argv)
{

    char* prompt = NULL;
    struct file_list* deh_head;
    deh_head = malloc(sizeof(struct file_list));
    deh_head->name = NULL;
    deh_head->next = NULL;
    struct file_list* chosen_deh = NULL;

    find_files( ".", ".DEH", deh_head );

    if( argc >= 2 ) {
        prompt = argv[1];
    }

    /* if only 1 deh, use it */
    if( deh_head->next == NULL ) {
        chosen_deh = deh_head;
    } else {
        /* have the user pick one */
        chosen_deh = choose_file( deh_head, prompt, 5 );
    }

    if(!deh_head->name) {
        printf("Error: No DeHackEd files found.\n");
    } else {
        char cmd[MAX_LINESIZE];
        char fullpath[MAX_PATH+1];
        char* tmp = NULL;
        int i = 0;

        fullpath[0] = '\0';

        printf("Merging DeHacked patch: %s\n", chosen_deh->name);

        realpath( chosen_deh->name, fullpath );

        /* for some reason, fullpath returns the wrong
         * slashes for DOS usage
         */
        for( i = 0; i < strlen(fullpath); i++ )
            if(fullpath[i]=='/') fullpath[i] = '\\';

        snprintf( cmd, MAX_LINESIZE, "dehacked . -load %s\n", fullpath[0]?fullpath:chosen_deh->name );

        run_command(cmd);

        tmp = strdup( chosen_deh->name );

        for( i = strlen(tmp)-1; i >= 0; i-- )
            if( tmp[i] == '.' )
                tmp[i] = '\0';

        snprintf( cmd, MAX_LINESIZE, "copy DOOMHACK.EXE %s.EXE\n", tmp);

        run_command(cmd);

        printf("\n\n%s has been merged into %s.EXE\n", chosen_deh->name,tmp);

        if (tmp)
            free(tmp);
        
    }

    destroy(deh_head);
    return 0;
}
