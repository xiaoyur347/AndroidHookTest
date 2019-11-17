#include "elf_parser.h"
#include <cstdint>

void Elf32_Ehdr::debug()
{
    printf("ehdr size=%lu\n", sizeof(Elf32_Ehdr));
    if (e_ident[0] != 0x7f || e_ident[1] != 'E'
        || e_ident[2] != 'L' || e_ident[3] != 'F')
    {
        printf("not elf file\n");
    } else {
        printf("elf file\n");
    }
    printf("e_type=%d\n", e_type);
    printf("e_machine=%d\n", e_machine);
    printf("e_version=%d\n", e_version);
    printf("e_entry=%d\n", e_entry);
    printf("e_phoff=%d\n", e_phoff);
    printf("e_shoff=%d\n", e_shoff);
    printf("e_flags=%d\n", e_flags);
    printf("e_ehsize=%d\n", e_ehsize);
    printf("e_phentsize=%d\n", e_phentsize);
    printf("e_phnum=%d\n", e_phnum);
    printf("e_shentsize=%d\n", e_shentsize);
    printf("e_shnum=%d\n", e_shnum);
    printf("e_shstrndx=%d\n", e_shstrndx);
}

ElfParser::ElfParser(const char* elf_name)
    : _fileName(elf_name)
    , _pFile(NULL)
{

}

ElfParser::~ElfParser()
{
    if (_pFile != NULL)
    {
        fclose(_pFile);
        _pFile = NULL;
    }
}

bool ElfParser::parse()
{
    _pFile = fopen(_fileName.c_str(), "r");
    if (_pFile == NULL)
    {
        return false;
    }

    if (1 != fread(&_elfHeader, sizeof(_elfHeader), 1, _pFile))
    {
        return false;
    }
    _elfHeader.debug();

    parseSectionHeaderTable();
    parseProgramHeaderTable();
    return true;
}

bool ElfParser::parseSectionHeaderTable()
{

}

bool ElfParser::parseProgramHeaderTable()
{

}


