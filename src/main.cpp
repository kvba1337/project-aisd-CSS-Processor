#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "data_structures/my_string.h"
#include "data_structures/data_structures.h"
#include "data_structures/double_linked_list.h"
#include "utils/utils.h"
#include "core/css_parser.h"
#include "core/command_processor.h"

int main() {
    CommandParameters cmd;
    DoubleLinkedList<BlockList> block_list;
    BlockList* first_block = new BlockList;
    block_list.AddNode(first_block);
    bool flag = false;

    ParseCSS(block_list);

    while (std::cin >> cmd.character >> std::noskipws) {
        ParseCommands(block_list, cmd, false);
    }

    PrintOutput(cmd, flag);

    return 0;
}
