#include "command_processor.h"
#include "../utils/utils.h"
#include "css_parser.h"
#include "../operations/query_functions.h"
#include "../operations/delete_functions.h"
#include <cstdio>
#include <iostream>

void ProcessParameters(DoubleLinkedList<BlockList>& block_list, CommandParameters& cmd) {
    MyString temp = "";
    cmd.first_parameter = "";
    cmd.second_parameter = "";
    cmd.third_parameter = "";
    int param_index = 1;
    for (int i = 0; i <= cmd.input.Length(); i++) {
        if (cmd.input[i] == ',' || i == cmd.input.Length()) {
            switch (param_index) {
            case 1:
                cmd.first_parameter = RemoveSpaces(temp);
                cmd.is_first_param_int = IsDigit(cmd.first_parameter.CStr());
                if (cmd.is_first_param_int) cmd.section_number = cmd.first_parameter;
                param_index++;
                break;
            case 2:
                cmd.second_parameter = RemoveSpaces(temp);
                param_index++;
                break;
            case 3:
                cmd.third_parameter = RemoveSpaces(temp);
                cmd.is_third_param_int = IsDigit(cmd.third_parameter.CStr());
                param_index++;
                break;
            default:
                break;
            }
            temp = "";
        }
        else {
            temp += cmd.input[i];
        }
    }
}

void HandleDCommand(DoubleLinkedList<BlockList>& block_list, CommandParameters& cmd) {
    if (cmd.is_first_param_int) {
        if (cmd.third_parameter == "*") {
            cmd.output += DeleteSection(block_list, cmd.section_number);
        }
        else {
            cmd.output += DeleteAttributeFromSection(block_list, cmd.third_parameter, cmd.section_number);
        }
    }
}

void HandleECommand(DoubleLinkedList<BlockList>& block_list, CommandParameters& cmd) {
    if (!cmd.is_first_param_int && !cmd.is_third_param_int) {
        cmd.output += GetAttributeValueForSelector(block_list, cmd.third_parameter, cmd.first_parameter);
    }
}

void HandleSCommand(DoubleLinkedList<BlockList>& block_list, CommandParameters& cmd) {
    if (cmd.third_parameter == "?") {
        if (cmd.is_first_param_int) {
            cmd.output += GetAmountOfSelectorsInSectionI(block_list, cmd.section_number);
        }
        else {
            cmd.output += GetSelectorOccurrences(block_list, cmd.first_parameter);
        }
    }
    else if (cmd.is_third_param_int && cmd.is_first_param_int) {
        cmd.output += GetJselectorForIsection(block_list, cmd.third_parameter, cmd.section_number);
    }
}

void HandleACommand(DoubleLinkedList<BlockList>& block_list, CommandParameters& cmd) {
    if (cmd.third_parameter == "?") {
        if (cmd.is_first_param_int) {
            cmd.output += GetAmountOfAttributesInSectionI(block_list, cmd.section_number);
        }
        else {
            cmd.output += GetAttributeOccurrences(block_list, cmd.first_parameter);
        }
    }
    else if (cmd.is_first_param_int && !cmd.is_third_param_int) {
        cmd.output += GetAttributeValueForSection(block_list, cmd.third_parameter, cmd.section_number);
    }
}

void ProcessCommand(DoubleLinkedList<BlockList>& block_list, CommandParameters& cmd) {
    char cmd_type = cmd.second_parameter[0];

    switch (cmd_type) {
    case 'S':
        HandleSCommand(block_list, cmd);
        break;
    case 'A':
        HandleACommand(block_list, cmd);
        break;
    case 'E':
        HandleECommand(block_list, cmd);
        break;
    case 'D':
        HandleDCommand(block_list, cmd);
        break;
    default:
        cmd.output += "";
        break;
    }
}

void ParseCommands(DoubleLinkedList<BlockList>& block_list, CommandParameters& cmd, bool flag) {
    if ((cmd.character == '\n' || cmd.character == ' ' || cmd.character == '\t' || cmd.character == EOF || flag)) {
        if (cmd.input == "????") {
            cmd.input = "";
        }
        else if (cmd.input == "****") {
            ParseCSS(block_list);
            cmd.input = "";
        }
        else if (cmd.input == "?") {
            cmd.output += GetAmountOfSections(block_list);
            cmd.input = "";
        }
        else {
            ProcessParameters(block_list, cmd);
            ProcessCommand(block_list, cmd);
        }
        cmd.output += '<';
        cmd.input = "";
    }
    else if (cmd.character != '\n' && cmd.character != ' ' && cmd.character != '\t' && !flag) {
        cmd.input += cmd.character;
    }
}

void PrintOutput(CommandParameters& cmd, bool& flag) {
    int i = 0;
    while (i < cmd.output.Length()) {
        char c = cmd.output[i];
        if (c == '\n' || c == '<' || c == '/' || c == '\t') {
            if (c == '<' && i != 0 && flag) {
                std::cout << '\n';
                flag = false;
            }
            i++;
            continue;
        }
        std::cout << c;
        flag = true;
        i++;
    }
}
