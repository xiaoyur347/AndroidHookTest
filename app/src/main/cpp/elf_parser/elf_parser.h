#ifndef ELF_PARSER_H
#define ELF_PARSER_H

#include <string>

class ElfParser
{
public:
    ElfParser(const char* elf_name);
    ~ElfParser();
    bool Parse();

private:
    std::string _fileName;
};

#endif //ELF_PARSER_H
