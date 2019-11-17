#ifndef ELF_PARSER_H
#define ELF_PARSER_H

#include <string>
#include <cstdint>
#include <cstdio>

// https://blog.csdn.net/navyhu/article/details/45951853

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
struct Elf32_Ehdr{
    unsigned char e_ident[EI_NIDENT];
    Elf32_Half e_type;
    Elf32_Half e_machine;
    Elf32_Word e_version;
    Elf32_Addr e_entry;
    Elf32_Off e_phoff; // program header table offset
    Elf32_Off e_shoff; // section header table offset
    Elf32_Word e_flags;
    Elf32_Half e_ehsize; // ELF header的大小（bytes）
    Elf32_Half e_phentsize; // Program Header table中每个表项（program header）的大小，PHT中所有表项大小相同
    Elf32_Half e_phnum; // Program header table中的表项数量
    Elf32_Half e_shentsize; // Section header table中每个表项（section header）的大小，SHT中所有表项大小相同
    Elf32_Half e_shnum; // Section header table中表项数量
    Elf32_Half e_shstrndx; // Section header table中有一表项是section name string table（节名字表）
                           // 这个变量记录了此表项在SHT中的位置，如果文件中没有这个表项，则变量值为SHN_UNDEF

    void debug();
};

// section header
struct Elf32_Shdr
{
    Elf32_Word sh_name; // section名字，但不是直接存储的名字，而是一个指向section header string table的一个index
    Elf32_Word sh_type;
    Elf32_Word sh_flags;
    Elf32_Addr sh_addr; // 如果这个section会被加载到内存，这个成员就是此section在内存中的地址，否则为0
    Elf32_Off sh_offset; // 此section相对于文件开始的偏移量（字节）
    Elf32_Word sh_size; // section所占的空间大小（字节）
    Elf32_Word sh_link; // 一个section header table index链接，含义取决于section类型
    Elf32_Word sh_info; // 额外信息，含义取决于section类型
    Elf32_Word sh_addralign; // 有些sections有地址对齐的限制，sh_addr模sh_addralign必须为0。 0和1都表示不用地址对齐
    Elf32_Word sh_entsize; // 有些sections由一些固定大小的表项组成的表（比如符号表），对于这些sections，这个成员记录了每个表项的大小。对于不是这种类型的section，值为0
};

class ElfParser
{
public:
    ElfParser(const char* elf_name);
    ~ElfParser();
    bool parse();

private:
    bool parseSectionHeaderTable();
    bool parseProgramHeaderTable();
    std::string _fileName;
    FILE* _pFile;
    Elf32_Ehdr _elfHeader;
};

#endif //ELF_PARSER_H
