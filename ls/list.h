#ifndef _LIST_H
#define _LIST_H

#include <dirent.h>
#include <sys/stat.h>

/****** MACROS ******/

#define ISFILE 128
#define ISDIR 129
#define FILEERR 130

/****** STRUCTS ******/

/**
 * struct dir_lister_s - Iterator for parsing 'DIR' stream
 * @directory: Pointer to 'DIR' instance
 * @path: Path to directory in file system
 * @current_entry: Pointer to current 'struct dirent'
 * @stop: int flag to indicate directory entries have been exhausted
 */

typedef struct dir_lister_s
{
	DIR *directory;
	struct stat *path_info;
	const char *path;
	struct dirent *current_entry;
	int stop;
} dir_lister_t;

/****** PROTOTYPES ******/

/* LIST_MAIN */


/* LISTER */

int directory_lister_init(dir_lister_t *parser,
						 const char *path);
int print_dir(dir_lister_t *parser);
struct dirent *next_entry(dir_lister_t *parser);
void close_dir(dir_lister_t *parser);

/* file_manager */

int check_file_type(const char *path);

#endif