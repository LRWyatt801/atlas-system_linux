#ifndef _LIST_H
#define _LIST_H

#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

/****** MACROS ******/

#define ISFILE 128
#define ISDIR 129
#define FILEERR 130
#define ONEPERLINE 1
#define ALLHIDDEN 2
#define ALLNOTCURPREV 4
#define LONGFORMAT 8
#define MULTIPLEDIRS 16

/****** STRUCTS ******/

/**
 * struct dir_lister_s - Iterator for parsing 'DIR' stream
 * @directory: Pointer to 'DIR' instance
 * @path_info: stores information given by lstat
 * @program_name: name of program being run
 * @path: Path to directory in file system
 * @flags: a bit map of given CL input flags
 * @num_dirs: number of given CL input directories
 * @current_entry: Pointer to current 'struct dirent'
 * @stop: int flag to indicate directory entries have been exhausted
 */

typedef struct dir_lister_s
{
	DIR *directory;
	struct stat *path_info;
	const char *program_name;
	const char *path;
	unsigned int flags;
	int num_dirs;
	struct dirent *current_entry;
	int stop;
} dir_lister_t;

/**
 * struct longlistfmt - supplies all info needed for long format
 *
 */

typedef struct longlistfmt
{
	char mode[16];
	nlink_t nlinks;
	const char *user;
	const char *group;
	off_t size;
	const char *modified;
	const char *entry_name;
} longlistfmt_t;

/**
 * struct print_flags_s - struct for managing the different CL flags
 * @flag_value: the decimal value of each flag
 * @printer: function pointer to correct printer
 */

typedef struct print_flags_s
{
	unsigned int flag_value;
	int (*printer)(dir_lister_t *parser);
} print_flags_t;

/**
 * enum errors - list of different error codes
 * @ERR_FILE_NOT_FOUND: error for 'file not found'
 * @ERR_CANNOT_ACCESS_DIR: error for 'permission denied'
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

/* PRINT_MANAGER */

int print_single_dir(dir_lister_t *parser, const char *path);
int print_multi_inputs(dir_lister_t *parser,
					   int argc, char **argv);

int (*get_flag_func(unsigned int flags))(dir_lister_t *);

/* PRINTERS */

int print_oneperline(dir_lister_t *parser);
int printall(dir_lister_t *parser);
int printAll_notcurnt(dir_lister_t *parser);
int longlistfmt_entry_init(dir_lister_t *parser);
int print_longlistfmt(dir_lister_t *parser);

/* HELPERS */

int _strcmp(char *s1, char *s2);
const char *dirent_type_name(unsigned char d_type);
const char *path_join(const char *dirpath, const char *entry_name);
int mode_to_str(char *buf, mode_t mode);
int longlistfmt_init(longlistfmt_t *longlist,
					 const char *entry_name,
					 struct stat *statbuf);
void longlistfmt_print(longlistfmt_t *longlist);

#endif
