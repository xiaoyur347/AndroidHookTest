#include "elf_parser.h"

int main(int argc, char* argv[])
{
    ElfParser parser(argv[1]);
    parser.parse();
    return 0;
}
