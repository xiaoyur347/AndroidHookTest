#ifndef ELF_PARSER_H
#define ELF_PARSER_H

#include <string>
#include <cstdint>
#include <cstdio>

typedef std::uint32_t Elf32_Addr;
typedef std::uint16_t Elf32_Half;
typedef std::uint32_t Elf32_Off;
typedef std::int32_t Elf32_Sword;
typedef std::uint32_t Elf32_Word;


// e_type
#define ET_NONE 0 // No file type
#define ET_REL 1 // Relocatable file
#define ET_EXEC 2 // Executable file
#define ET_DYN 3 // Shared object file
#define ET_CORE 4 // Core file
#define ET_LOPPROC 0xff00 // Processor-specific
#define ET_HIPROC 0xffff // Processor-specific

// e_machine
#define EM_NONE 0 // No machine
#define EM_M32 1 // AT&T WE 32100
#define EM_SPARC 2 // SPARC
#define EM_386 3 // Intel 80386
#define EM_68K 4 // Motorola 68000
#define EM_88K 5 // Motorola 88000
#define EM_860 7 // Intel 80860
#define EM_MIPS 8 // Intel RS3000

#define EI_NIDENT 16
typedef struct {
    unsigned char e_ident[EI_NIDENT];
    Elf32_Half e_type;
    Elf32_Half e_machine;
    Elf32_Word e_version;
    Elf32_Addr e_entry;
    Elf32_Off e_phoff; // program header table offset
    Elf32_Off e_shoff; // section header table offset
    Elf32_Word e_flags;
    Elf32_Half e_ehsize;
    Elf32_Half e_phentsize;
    Elf32_Half e_phnum;
    Elf32_Half e_shentsize;
    Elf32_Half e_shnum;
    Elf32_Half e_shstrndx;

    void debug();
}Elf32_Ehdr;

class ElfParser
{
public:
    ElfParser(const char* elf_name);
    ~ElfParser();
    bool parse();

private:
    std::string _fileName;
    FILE* _pFile;
};

#endif //ELF_PARSER_H
