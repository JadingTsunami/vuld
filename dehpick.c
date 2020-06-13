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
    int retval = 0;

    if( !does_file_exist("dehacked.exe") ) {
        fprintf(stderr, "Error: No DeHackEd executable found.\n");
        destroy( deh_head );
        return 1;
    }

    if( does_file_exist("doomhack.exe") ) {
        struct file_list choice_clean;
        struct file_list choice_acc;
        char str_clean[] = "Start over anew (delete DOOMHACK.EXE).";
        char str_acc[] = "Patch on top of the existing executable (keep DOOMHACK.EXE).";
        choice_clean.name = str_clean;
        choice_acc.name = str_acc;
        choice_clean.next = &choice_acc;
        if( &choice_clean == choose_option(&choice_clean,"NOTICE: Found a DeHackEd patched DOOMHACK.EXE.\n\nDo you want to patch on top of this executable or start over?\nIf you don't know what this is, choose \"start over\".\n","Select an option: ",5) ) {
            if( remove( "doomhack.exe" ) != 0 ) {
                fprintf(stderr, "Error: Couldn't remove DOOMHACK.EXE.\n");
                fprintf(stderr, "Please remove the file manually and re-run.\n");
                destroy(deh_head);
                return 1;
            } else if( (does_file_exist("doom.exe") && !run_command("copy doom.exe doomhack.exe")) ||
                    (does_file_exist("doom2.exe") && !run_command("copy doom2.exe doomhack.exe") ) ) {
                /* ordinarily, this would be an error, but
                 * since DeHackEd will handle this, we can 
                 * just print it and continue
                 */
                fprintf(stderr, "Warning: Couldn't create a new DOOMHACK.EXE.\n");
                fprintf(stderr, "Will let DeHackEd handle it.\n");
                fprintf(stderr, "Logging and moving on...\n");
            }
        } else {
            printf("Patching on top of existing DOOMHACK.EXE.\n");
        }
        
    }

    if( argc > 1 ) {
        find_files( argv[1], ".DEH", deh_head );
    } else {
        find_files( ".", ".DEH", deh_head );
    }

    /* if only 1 deh, use it */
    if( deh_head->next == NULL ) {
        chosen_deh = deh_head;
    } else {
        /* have the user pick one */
        chosen_deh = choose_file( deh_head, prompt, 5 );
    }

    if(!deh_head->name) {
        fprintf(stderr, "Error: No DeHackEd files found.\n");
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

        if( run_command(cmd) ) {
            fprintf(stderr, "Error: Could not apply the DeHackEd patches.\n");
            fprintf(stderr, "Check for DeHackEd errors.\n");
            destroy( deh_head );
            return 1;
        }

        tmp = strdup( chosen_deh->name );

        for( i = strlen(tmp)-1; i >= 0; i-- )
            if( tmp[i] == '.' )
                tmp[i] = '\0';

        snprintf( cmd, MAX_LINESIZE, "copy DOOMHACK.EXE %s.EXE\n", tmp);

        if ( run_command(cmd) ) {
            fprintf(stderr,"\n\nError: Could not merge changes into %s.EXE\n", tmp);
            fprintf(stderr, "Check for DeHackEd or disk errors.\n");
            retval = 1;
        } else { 
            printf("\n\n%s has been merged into %s.EXE\n", chosen_deh->name,tmp);
            printf("\n");
        }

        if (tmp)
            free(tmp);
        
    }

    destroy(deh_head);
    return retval;
}
