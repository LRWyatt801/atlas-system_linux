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
 * @path_info: stores information given by lstat
 * @program_name: name of program being run
 * @path: Path to directory in file system
 * @current_entry: Pointer to current 'struct dirent'
 * @stop: int flag to indicate directory entries have been exhausted
 */

typedef struct dir_lister_s
{
	DIR *directory;
	struct stat *path_info;
	const char *program_name;
	const char *path;
	char **dirs;
	unsigned int flags;
	int num_dirs;
	struct dirent *current_entry;
	int stop;
	int args_stop;
} dir_lister_t;

/**
 * enum errors - list of different error codes
 * @ERR_FILE_NOT_FOUND: error for 'file not found'
 * @ERR_PERM_DENIED: error for 'permission denied'
 * @ERR_FAILURE_TO_OPEN_DIR: error for 'failure to open directory'
 */

typedef enum errors
{
	ERR_FILE_NOT_FOUND,
	ERR_CANNOT_ACCESS_DIR,
	ERR_FAILURE_TO_OPEN_DIR
} errorCode_t;

/****** PROTOTYPES ******/

/* MAIN */

/* LISTER */

int directory_lister_init(dir_lister_t *parser,
						  const char *path);
int print_dir(dir_lister_t *parser);
struct dirent *next_entry(dir_lister_t *parser);
void close_dir(dir_lister_t *parser);

/* file_manager */

int check_file_type(dir_lister_t *parser, const char *path);

/* ERROR_HANDLER */

int error_handler(errorCode_t error, ...);

#endif
