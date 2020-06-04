#ifndef _FILEUTIL_H
#define _FILEUTIL_H

#define MAX(a,b) ((a) > (b) ? a : b)
#define MIN(a,b) ((a) < (b) ? a : b)
#define MAX_LINESIZE (81)
#define MAX_PATH (260)

struct file_list
{
    char* name;
    struct file_list* next;
};

void add_file( struct file_list* head, char* name );
void destroy( struct file_list* head );
int choose_number(char* prompt, int max_tries, int least, int most, bool print_range);
struct file_list* choose_file( struct file_list* head, char* prompt, int max_files_per_screen );
int run_command(char* cmd);
int find_files( char* fdir, char* fextension, struct file_list* fhead );
void clear_screen();

#endif
