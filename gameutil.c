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
    
    if ( pathloc > 0 && pathloc+2 < MAX_PATH && directory[pathloc] != PATHSEP &&
         (strcmp(tmpdir,".") != 0)) {
        strcat( tmpdir, PATHSEP );
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
