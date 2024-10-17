#include "hreadelf.h"

#define ELFCLASS(elf_file) ((elf_file)->class == 1 ? "ELF32" : "ELF64")
#define ELFDATA(elf_file) ((elf_file)->class == ELFCLASS32 ? \
		((elf_file)->elfheader.v32->e_ident[EI_DATA] == ELFDATA2LSB ? \
			"Two's complement, little-endian" : "Two's complement, big-endian") : \
		((elf_file)->elfheader.v64->e_ident[EI_DATA] == ELFDATA2LSB ? \
			"Two's complement, little-endian" : "Two's complement, big-endian"))
#define ELFVERSION(elf_file) \
	((elf_file)->class == ELFCLASS32 ? \
		((elf_file)->elfheader.v32->e_ident[EI_VERSION] == EV_CURRENT ? \
			"1 (current)" : "Unknown version") : \
		((elf_file)->elfheader.v64->e_ident[EI_VERSION] == EV_CURRENT ? \
			"1 (current)" : "Unknown version"))
#define ELFABIVERSION(elf_file) ((elf_file)->class == ELFCLASS32 ? \
		(elf_file)->elfheader.v32->e_ident[EI_ABIVERSION] : \
		(elf_file)->elfheader.v64->e_ident[EI_ABIVERSION])
#define ELFVERSIONINBIT(elf_file) ((elf_file)->class == ELFCLASS32 ? \
		(elf_file)->elfheader.v32->e_version : \
		(elf_file)->elfheader.v64->e_version)
#define ELFENTRYPOINT(elf_file) ((elf_file)->class == ELFCLASS32 ? \
		(elf_file)->elfheader.v32->e_entry : \
		(elf_file)->elfheader.v64->e_entry)
#define ELFPROGRAMOFFSET(elf_file) ((elf_file)->class == ELFCLASS32 ? \
		(elf_file)->elfheader.v32->e_phoff : \
		(elf_file)->elfheader.v64->e_phoff)
#define ELFSECOFFSET(elf_file) ((elf_file)->class == ELFCLASS32 ? \
		(elf_file)->elfheader.v32->e_shoff : \
		(elf_file)->elfheader.v64->e_shoff)
#define ELFFLAGS(elf_file) ((elf_file)->class == ELFCLASS32 ? \
		(elf_file)->elfheader.v32->e_flags : \
		(elf_file)->elfheader.v64->e_flags)
#define ELFSIZEOFHDR(elf_file) ((elf_file)->class == ELFCLASS32 ? \
		(elf_file)->elfheader.v32->e_ehsize : \
		(elf_file)->elfheader.v64->e_ehsize)
#define ELFSIZEPRGHDRS(elf_file) ((elf_file)->class == ELFCLASS32 ? \
		(elf_file)->elfheader.v32->e_phentsize : \
		(elf_file)->elfheader.v64->e_phentsize)
#define ELFNUMPRGHDRS(elf_file) ((elf_file)->class == ELFCLASS32 ? \
		(elf_file)->elfheader.v32->e_phnum : \
		(elf_file)->elfheader.v64->e_phnum)
#define ELFSIZESECHDRS(elf_file) ((elf_file)->class == ELFCLASS32 ? \
		(elf_file)->elfheader.v32->e_shentsize : \
		(elf_file)->elfheader.v64->e_shentsize)
#define ELFNUMSECHDRS(elf_file) ((elf_file)->class == ELFCLASS32 ? \
		(elf_file)->elfheader.v32->e_shnum : \
		(elf_file)->elfheader.v64->e_shnum)
#define SECHDRSTRTABLE(elf_file) ((elf_file)->class == ELFCLASS32 ? \
		(elf_file)->elfheader.v32->e_shstrndx : \
		(elf_file)->elfheader.v64->e_shstrndx)

/**
 * print_elf_hdr - prints ELF Header
 * @elf_file: struct containing necessary variables
 *
 * Return: n/a
 */

void print_elf_hdr(elf_fmgr_t *elf_file)
{
	int i;

	printf("ELF Header:\n");
	printf("\tMagic: ");
	for (i = 0; i < 16; i++)
		printf("%02x ", elf_file->elfheader.v64->e_ident[i]);
	printf("\n");
	printf("\tClass:                             %s\n",
		   ELFCLASS(elf_file));
	printf("\tData:                              %s\n",
		   ELFDATA(elf_file));
	printf("\tVersion:                           %s\n",
		   ELFVERSION(elf_file));
	printf("\tOS/ABI:                            %s\n",
		   getelfosabi(elf_file));
	printf("\tABI Version:                       %d\n",
		   ELFABIVERSION(elf_file));
	printf("\tType:                              %s\n",
		   getelftype(elf_file));
	printf("\tMachine:                           %s\n",
		   getelfmachine(elf_file));
	printf("\tVersion:                           0x%01x\n",
		   ELFVERSIONINBIT(elf_file));
	printf("\tEntry point address:               0x%lx\n",
		   ELFENTRYPOINT(elf_file));
	printf("\tStart of program headers:          %lu (bytes into file)\n",
		   ELFPROGRAMOFFSET(elf_file));
	printf("\tStart of section headers:          %lu (bytes into file)\n",
		   ELFSECOFFSET(elf_file));
	printf("\tFlags:                             0x%x\n",
		   ELFFLAGS(elf_file));
	printf("\tSize of this header:               %d (bytes)\n",
		   ELFSIZEOFHDR(elf_file));
	printf("\tSize of program headers:           %d (bytes)\n",
		   ELFSIZEPRGHDRS(elf_file));
	printf("\tNumber of program headers:         %d\n",
		   ELFNUMPRGHDRS(elf_file));
	printf("\tSize of section headers:           %d (bytes)\n",
		   ELFSIZESECHDRS(elf_file));
	printf("\tNumber of section headers:         %d\n",
		   ELFNUMSECHDRS(elf_file));
	printf("\tSection header string table index: %d\n",
		   SECHDRSTRTABLE(elf_file));

}

/**
 * getelfosabi - gets the os/abi information for an elf file
 * @elf_file: struct containing all necessary variables
 *
 * Return: OS/ABI str, otherwise NULL
 */

char *getelfosabi(elf_fmgr_t *elf_file)
{
	unsigned char osabi;
	if (!elf_file)
		return NULL;
	
	osabi = (elf_file->class == ELFCLASS32 ? \
		elf_file->elfheader.v32->e_ident[EI_OSABI] : \
		elf_file->elfheader.v64->e_ident[EI_OSABI]);
	
	switch(osabi)
	{
		case ELFOSABI_SYSV:
            return "UNIX - System V";
        case ELFOSABI_HPUX:
            return "UNIX - HP-UX";
        case ELFOSABI_NETBSD:
            return "UNIX - NetBSD";
        case ELFOSABI_LINUX:
            return "UNIX - Linux";
        case ELFOSABI_SOLARIS:
            return "UNIX - Solaris";
        case ELFOSABI_AIX:
            return "UNIX - AIX";
        case ELFOSABI_IRIX:
            return "UNIX - IRIX";
        case ELFOSABI_FREEBSD:
            return "UNIX - FreeBSD";
        case ELFOSABI_TRU64:
            return "UNIX - TRU64";
        case ELFOSABI_MODESTO:
            return "Novell - Modesto";
        case ELFOSABI_OPENBSD:
            return "UNIX - OpenBSD";
        case ELFOSABI_ARM_AEABI:
            return "ARM EABI";
        case ELFOSABI_ARM:
            return "ARM";
        case ELFOSABI_STANDALONE:
            return "Standalone App";
        default:
            return "Unknown OS/ABI";
	}
}

/**
 * getelftype - gets the type of elf
 * @elf_file: struct containing all necessary variables
 *
 * Return: type str, otherwise NULL
 */

char *getelftype(elf_fmgr_t *elf_file)
{
	unsigned short type;
	if (!elf_file)
		return NULL;

	type = (elf_file->class == ELFCLASS32 ? \
		elf_file->elfheader.v32->e_type : \
		elf_file->elfheader.v64->e_type);

	switch(type)
	{
		case ET_NONE:
            return ("NONE (No file type)");
        case ET_REL:
			return ("REL (Relocatable file)");
		case ET_EXEC:
			return ("EXEC (Executable file)");
		case ET_DYN:
			return ("DYN (Shared object file)");
		case ET_CORE:
			return ("CORE (Core file)");
		default:
			return ("Unknown type");
	}
}

/**
 * getelfmachine - gets the machine type of elf
 * @elf_file: struct containing all necessary variables
 *
 * Return: machine str, otherwise NULL
 */

char *getelfmachine(elf_fmgr_t *elf_file)
{
	unsigned short machine;
	if (!elf_file)
		return NULL;

	machine = (elf_file->class == ELFCLASS32 ? \
		elf_file->elfheader.v32->e_machine : \
		elf_file->elfheader.v64->e_machine);

	switch(machine)
	{
		case EM_NONE:
			return ("No machine");
		case EM_M32:
			return ("AT&T WE 32100");
		case EM_SPARC:
			return ("SPARC");
		case EM_386:
			return ("Intel 80386");
		case EM_68K:
			return ("Motorola 68000");
		case EM_88K:
			return ("Motorola 88000");
		case EM_860:
			return ("Intel 80860");
		case EM_MIPS:
			return ("MIPS RS3000");
		case EM_PARISC:
			return ("HP/PA");
		case EM_SPARC32PLUS:
			return ("SPARC with enhanced instruction set");
		case EM_PPC:
			return ("PowerPC");
		case EM_PPC64:
			return ("PowerPC 64-bit");
		case EM_S390:
			return ("IBM S390");
		case EM_ARM:
			return ("ARM");
		case EM_SH:
			return ("Renesas SuperH");
		case EM_SPARCV9:
			return ("SPARC v9 64-bit");
		case EM_IA_64:
			return ("Intel IA-64");
		case EM_X86_64:
			return ("AMD x86-64");
		case EM_VAX:
			return ("VAX");
		default:
			return ("Unknown machine");
	}
}