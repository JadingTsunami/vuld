#ifndef _GAMEUTIL_H
#define _GAMEUTIL_H

enum gametype {
    GAME_NONE,
    GAME_DOOM,
    GAME_DOOM2,
    GAME_LAST
};


enum gametype check_for_game(char* directory);


#endif
