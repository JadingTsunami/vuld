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

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>

#include "fileutil.h"
#include "genutil.h"

struct file_list* create_file_list()
{
    struct file_list* f = malloc(sizeof(struct file_list));

    if(!f) return NULL;

    f->name = NULL;
    f->next = NULL;

    return f;
}

void add_file( struct file_list* head, char* name )
{
    if( head && head->name ) {
        struct file_list* new_file = malloc(sizeof(struct file_list));
        if(!new_file) {
            fprintf(stderr,"Error: Out of memory when building internal file structures.\n");
            return;
        }
        new_file->name = strdup(name);
        new_file->next = NULL;
        struct file_list* file_ptr = head;
        while( file_ptr->next )
            file_ptr = file_ptr->next;
        file_ptr->next = new_file;
    } else if ( head ) {
        head->name = strdup(name);
    }
}

void destroy( struct file_list* head )
{
    struct file_list* prev = head;
    while( head ) {
        if( head->name )
            free( head->name );
        prev = head;
        head = head->next;
        free( prev );
    }
}

int choose_number(char* prompt, int max_tries, int least, int most, bool print_range)
{
    char in[33];
    int chosen = -1;
    bool choice_made = false;
    int tries = 0;
    bool try = (max_tries>0);

    while ( !choice_made || (try && tries > max_tries) ) {
        if( prompt ) {
            printf("%s ", prompt);
            fflush(stdout);
        }
        
        if( print_range ) {
            printf("[%d-%d] ", least, most);
        }

        scanf( "%32s[^\n]", in );
        chosen = atoi(in);
        if( chosen < least || chosen > most ) {
            printf("Error: Selection must be between %d and %d.\n", least, most);
        } else {
            choice_made = true;
        }
        tries++;
    }
    if( choice_made )
        return chosen;
    else
        return -1;
}

struct file_list* choose_file( struct file_list* head, char* prompt, int max_files_per_screen )
{
    int pos = 0;
    int page = 0;
    int chosen = -1;
    struct file_list* file_onscreen[max_files_per_screen];
    struct file_list* node = head;
    int max_choice = 0;
    while( head ) {
        pos = 0;
        clear_screen();
        if( prompt )
            printf("%s\n", prompt);
        else
            printf("Select a DeHackEd file:\n\n");

        if( page > 0 ) {
            printf("Page %d\n\n", page+1);
            printf("\t0. Start over\n");
        }

        while( node && pos < max_files_per_screen ) {
            printf("\t%d. %s\n", pos+1, node->name);
            file_onscreen[pos] = node;
            node = node->next;
            pos++;
        }

        if( node ) {
            printf("\t%d. Next Page\n", max_files_per_screen+1);
            max_choice = max_files_per_screen+1;
        } else {
            max_choice = MIN(pos,max_files_per_screen);
        }


        printf("\n");

        chosen = choose_number( "Select a file: ", -1, (page>0?0:1), max_choice, true);

        if( chosen == 0 ) {
            node = head;
            page = 0;
        } else if( chosen == max_files_per_screen+1 ) {
            page++;
        } else {
            return file_onscreen[chosen-1];
        }

    }
    return NULL;
}

int run_command(char* cmd)
{
    int code = 0;
    code = system(cmd);
    if ( code != 0 ) {
        printf("Error: Command %s failed with error code %d.\n", cmd, code);
    }
    return code;
}

int find_files( char* fdir, char* fextension, struct file_list* fhead )
{
    DIR *d;
    struct dirent *dir;
    char* ent = NULL;
    int found = 0;
    int i = 0;
    int len = 0;
    char fpath[strlen(fdir)+8+1+3+1];

    fpath[0] = '\0';

    if( strcmp(fdir,".") != 0 )
        strcpy(fpath,fdir);

    d = opendir(fdir);

    /* find all the files with the given extension */
    if( d ) {
        while ( (dir = readdir(d)) != NULL ) {
            ent = dir->d_name;
            if( ent && (strcmp(ent, ".") == 0 || strcmp(ent, "..") == 0) )
                continue;
            len = strlen(ent);
            for( i = 0; i < len; i++ )
                ent[i] = toupper(ent[i]);
            if( len-4 >= 0 && strncmp( fextension, &ent[len-4], 4 ) == 0 ) {
                if ( fhead ) {
                    if( fpath[0] ) {
                        strcat(fpath,"\\");
                        strcat(fpath,ent);
                        add_file( fhead, fpath );
                        strcpy(fpath,fdir);
                    } else {
                        add_file( fhead, ent );
                    }
                }
                found++;
            }
        }
        closedir(d);
    }

    return found;
}

void clear_screen()
{
    system("cls");
}


bool does_file_exist(char* path_to_file)
{
    return (access( path_to_file, F_OK ) == 0);
}
