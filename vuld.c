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
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>

#include "fileutil.h"
#include "genutil.h"
#include "gameutil.h"

#define VULD_SUBDIR "vuld_dir"
#define VULD_WAD "VULD.WAD"
#define VULD_EXE "VULD.EXE"

#define RET_ERROR (-1)

struct gamepack {
    enum gametype game;
    char* command_args;
    char* processed_wad;
    struct file_list* deh_files;
    struct file_list* wad_files;
};

bool merge_all_deh( struct file_list* deh_files, char* deh_cmd )
{

    char cmd[MAX_LINESIZE];
    char fullpath[MAX_PATH+1];
    char* tmp = NULL;
    int i = 0;
    int cmd_len = 0;

    fullpath[0] = '\0';

    if(!deh_files || !deh_files->name || !deh_cmd)
        return false;

    //snprintf( cmd, MAX_LINESIZE, "dehacked . -load %s\n", fullpath[0]?fullpath:chosen_deh->name );
    snprintf( cmd, MAX_LINESIZE, "%s . -load ", deh_cmd );
    cmd_len = strlen(cmd);
    while( deh_files && deh_files->name ) {
        realpath( deh_files->name, fullpath );
        /* for some reason, fullpath returns the wrong
         * slashes for DOS usage
         */
        for( i = 0; i < strlen(fullpath); i++ )
            if(fullpath[i]=='/') fullpath[i] = '\\';

        cmd_len += strlen(fullpath) + 1;
        if( cmd_len >= MAX_LINESIZE ) {
            fprintf(stderr, "Error: Could not fit the DeHackEd command on the command line.\n");
            fprintf(stderr, "Try loading fewer patches.\n");
            return false;
        }

        strcat( cmd, fullpath[0]?fullpath:deh_files->name );
        strcat( cmd, " " );

        deh_files = deh_files->next;
    }

    /* run the Dehacked command */
    if( !run_command(cmd) ) {
        fprintf(stderr, "Error: Could not apply the DeHackEd patches.\n");
        fprintf(stderr, "Check for DeHackEd errors.\n");
        return false;
    }

    snprintf( cmd, MAX_LINESIZE, "copy DOOMHACK.EXE %s\\%s.EXE\n", VULD_SUBDIR, VULD_EXE);

    if( !run_command(cmd) ) {
        fprintf(stderr, "Error: Could not copy the modified Game EXE.\n");
        return false;
    }

    return true;
}

bool merge_all_wad( struct file_list* wad_files, char* wad_cmd )
{
    char cmd[MAX_LINESIZE];
    char fullpath[MAX_PATH+1];
    char* tmp = NULL;
    int i = 0;
    int cmd_len = strlen("COPY ") + strlen(VULD_SUBDIR) + strlen(VULD_WAD) + 1;
    bool first = true;

    fullpath[0] = '\0';

    if(!wad_files || !wad_files->name || !wad_cmd)
        return false;

    do {

        realpath( wad_files->name, fullpath );

        /* for some reason, fullpath returns the wrong
         * slashes for DOS usage
         */
        for( i = 0; i < strlen(fullpath); i++ )
            if(fullpath[i]=='/') fullpath[i] = '\\';

        if( cmd_len+MAX(strlen(wad_files->name),strlen(fullpath))+1 >= MAX_LINESIZE ) {
            fprintf(stderr, "Error: Could not fit the DeuSF command on the command line.\n");
            fprintf(stderr, "Try loading fewer WAD files.\n");
            return false;
        }

        if( first ) {
            first = false;

            /* create the vuld wad */
            snprintf( cmd, MAX_LINESIZE, "copy %s %s\\%s \n", (fullpath[0]?fullpath:wad_files->name), VULD_SUBDIR, VULD_WAD);

            if( !run_command(cmd) ) {
                fprintf(stderr, "Error: Could create the merged WAD files.\n");
                return false;
            }

        } else {
            /* deusf join with the vuld wad */
            snprintf( cmd, MAX_LINESIZE, "%s -join %s\\%s %s\n", wad_cmd, VULD_SUBDIR, VULD_WAD, (fullpath[0]?fullpath:wad_files->name));

            if( !run_command(cmd) ) {
                fprintf(stderr, "Error: DeuSF failed to merge the WAD files.\n");
                return false;
            }
        }

        wad_files = wad_files->next;
    } while( wad_files && wad_files->name );

    /* do APPEND on VULD */
    snprintf( cmd, MAX_LINESIZE, "%s -append %s\\%s\n", wad_cmd, VULD_SUBDIR, VULD_WAD );

    if( !run_command(cmd) ) {
        fprintf(stderr, "Error: Could not create the final merged WAD.\n");
        fprintf(stderr, "Check for DeuSF errors.\n");
        return false;
    }

    return true;
}

void destroy_gamepack( struct gamepack* g, bool delete_strings )
{
    if(g) {
        if(g->deh_files)
            free(g->deh_files);
        if(g->wad_files)
            free(g->wad_files);

        if(delete_strings) {
            if(g->command_args)
                free(g->command_args);
            if(g->processed_wad)
                free(g->processed_wad);
        }

        free(g);
    }
}

struct gamepack* create_gamepack( enum gametype g, char* args, char* procwad,
        struct file_list* d, struct file_list* w )
{
    struct gamepack* gp = malloc(sizeof(struct gamepack));
    if(!gp)
        return NULL;

    gp->game = g;
    gp->command_args = args;
    gp->processed_wad = procwad;
    gp->deh_files = d;
    gp->wad_files = w;

    return gp;
}

struct gamepack* convert_dir_to_gamepack( char* dir_to_convert )
{
    if(!dir_to_convert)
        return NULL;

    struct gamepack* gp = create_gamepack(GAME_NONE,NULL,NULL,malloc(sizeof(struct file_list)),malloc(sizeof(struct file_list)));
    if(!gp || !gp->deh_files || !gp->wad_files)
        destroy_gamepack(gp,false);
        return NULL;

    find_files(dir_to_convert,".DEH",gp->deh_files);
    find_files(dir_to_convert,".WAD",gp->wad_files);

    return gp;
}


/* 2 modes:
 * 1. Launcher mode: Find all dirs with .deh and .wad, give user a choice, merge dehs, deusf/detex the wads and run
 *      - 1st WAD gets appended, rest are joined
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
    struct file_list* mod_dirs = NULL;
    struct file_list* chosen_file;
    struct gamepack* chosen_gamepack;
    /* DOS files are 8.3 plus null terminator */
    char deh_prog[8 + 1 + 3 + 1];
    char wad_prog[8 + 1 + 3 + 1];

    /* we need at least dehacked and deusf or deutex */
    if ( does_file_exist("dehacked.exe") ) {
        strcpy(deh_prog,"dehacked.exe");
    } else {
        fprintf(stderr, "Error: No DEHACKED.EXE found.\n");
        return RET_ERROR;
    }

    if (does_file_exist("deusf.exe")) {
        strcpy(wad_prog,"deusf.exe");
    } else if (does_file_exist("deutex.exe")) {
        strcpy(wad_prog,"deutex.exe");
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

    /* if an INI is specified, use it, else go into launcher mode */
    if ( argc > 1 ) {
        /* INI mode */
        /* TODO: Implement */
    } else {

        /* check for doom or doom2 game files */
        enum gametype game = check_for_game(".");

        if( game == GAME_NONE ) {
            fprintf(stderr, "Error: Did not find a game in the current directory.\n");
            fprintf(stderr, "Make sure you run %s from your game directory.\n", argv[0]);
            return RET_ERROR;
        }

        /* Launcher mode */
        /* For each directory */
        d = opendir( "." );

        if ( !d ) {
            fprintf(stderr, "Error: Could not open current directory.\n");
            return RET_ERROR;
        }

        /* find all the directories that contain
         * game files
         */
        struct dirent* dirfile;
        struct stat statbuf;
        char* strfile;
        while ( (dirfile = readdir(d)) != NULL ) {
            strfile = dirfile->d_name;
            if (stat(strfile, &statbuf) != 0)
                continue;
            else if S_ISDIR(statbuf.st_mode) {
                /* NOTE: optimization could be to stop after 1 file is found */
                if( find_files(dirfile->d_name, ".DEH", NULL) > 0 ||
                        find_files(dirfile->d_name, ".WAD", NULL) > 0 ) {
                    add_file( mod_dirs, dirfile->d_name );
                }
            }

        }

        closedir(d);

        /* Have the user pick one */
        chosen_file = choose_file( mod_dirs, "Select a gameplay mod:\n", 5 );

        /* turn it into a game pack */
        chosen_gamepack = convert_dir_to_gamepack(chosen_file->name);

        if( !chosen_gamepack ) {
            fprintf(stderr, "Wasn't able to create a game pack.\n");
            fprintf(stderr, "This is an internal error.\n");
            return RET_ERROR;
        }

        /* Merge all DEH patches */
        if( chosen_gamepack->deh_files )
            merge_all_deh( chosen_gamepack->deh_files, deh_prog );

        /* Merge all WAD files */
        if( chosen_gamepack->wad_files )
            merge_all_wad( chosen_gamepack->wad_files, wad_prog );

        if(chosen_gamepack)
            destroy_gamepack(chosen_gamepack,false);
    }
    /* Launch it */
    return 0;
}
