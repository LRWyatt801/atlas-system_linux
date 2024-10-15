#include "hreadelf.h"

#include <sys/stat.h>

/**
 * open_file - opens a file
 * @filename: name of file to be opened
 *
 * Return: elf_fmgr_t * on success, otherwise NULL
 */

elf_fmgr_t *open_file(char *fpath)
{
    elf_fmgr_t *open_elf = NULL;
    void *fmap;
    struct stat statbuff;
    int fd;

    if (!fpath)
        return (NULL);

    fd = open(fpath, O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        return (NULL);
    }
    if (fstat(fd, &statbuff) == -1)
    {
        perror("fstat");
        close(fd);
        return (NULL);
    }
    fmap = mmap(NULL, statbuff.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (fmap == MAP_FAILED)
    {
        perror("mmap");
        close(fd);
        return (NULL);
    }

    open_elf = malloc(sizeof(elf_fmgr_t));
    if (open_elf == NULL)
    {
        perror("malloc");
        munmap(fmap, statbuff.st_size);
        close(fd);
        return (NULL);
    }

    open_elf->elfheader.addr = fmap;
    open_elf->fd = fd;
    open_elf->fsize = statbuff.st_size;

    return (open_elf);
}

/**
 * elf_clost - closes an ELF file
 * @filemgr: pointer to struct containing ELF map and file descriptor
 *
 * Return: n/a
 */

void elf_close(elf_fmgr_t *filemgr)
{
    if (!filemgr)
        return;

    munmap(filemgr->elfheader.addr, filemgr->fsize);
    close(filemgr->fd);
    free(filemgr);
}