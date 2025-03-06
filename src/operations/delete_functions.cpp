#include "delete_functions.h"
#include "../utils/utils.h"
#include <cstdio>

MyString DeleteSection(DoubleLinkedList<BlockList>& block_list, MyString section_num) {
    int section_number = MyStringToInt(section_num);
    int current_section = 0;
    char section_number_char[CSS_PROCESSOR_MAX_SIZE];

    for (BlockList* current_block = block_list.GetFirstNode(); current_block; current_block = current_block->next) {
        if (!current_block->sections) continue;
        for (int i = 0; i < current_block->sections_counter; i++) {
            current_section++;
            if (current_section == section_number) {
                if (current_block->sections[i].selectors) {
                    delete current_block->sections[i].selectors;
                    current_block->sections[i].selectors = nullptr;
                }

                if (current_block->sections[i].attributes) {
                    delete current_block->sections[i].attributes;
                    current_block->sections[i].attributes = nullptr;
                }

                for (int j = i; j < current_block->sections_counter - 1; j++) {
                    current_block->sections[j] = current_block->sections[j + 1];
                }

                current_block->sections_counter--;
                sprintf(section_number_char, "%d", section_number);
                MyString return_string = section_number_char;
                return_string += { ",D,* == deleted" };
                return return_string;
            }
        }
    }
    return "";
}

MyString DeleteAttributeFromSection(DoubleLinkedList<BlockList>& block_list, MyString attribute_name, MyString section_num) {
    int section_number = MyStringToInt(section_num);
    int current_section = 0;
    char section_number_char[CSS_PROCESSOR_MAX_SIZE];

    for (BlockList* current_block = block_list.GetFirstNode(); current_block; current_block = current_block->next) {
        if (!current_block->sections) continue;
        for (int i = 0; i < current_block->sections_counter; i++) {
            if (++current_section != section_number) continue;
            if (!current_block->sections[i].attributes) continue;

            AttributeList* current_attribute = current_block->sections[i].attributes->GetFirstNode();
            while (current_attribute) {
                if (current_attribute->name == attribute_name) {
                    AttributeList* next_attribute = current_attribute->next;
                    current_block->sections[i].attributes->RemoveNode(current_attribute);
                    current_attribute = next_attribute;
                }
                else {
                    current_attribute = current_attribute->next;
                }
            }

            if (!current_block->sections[i].attributes->head_) {
                SectionList* next_section = current_block->sections[i].next;
                if (i == 0) {
                    current_block->sections = next_section;
                    if (next_section) next_section->prev = NULL;
                }
                else {
                    current_block->sections[i - 1].next = next_section;
                    if (next_section) next_section->prev = &current_block->sections[i - 1];
                }
                if (next_section) {
                    current_block->sections[i] = *next_section;
                    current_block->sections[i].prev = next_section->prev;
                    current_block->sections[i].next = next_section->next;
                    if (current_block->sections[i].prev) {
                        current_block->sections[i].prev->next = &current_block->sections[i];
                    }
                    if (current_block->sections[i].next) {
                        current_block->sections[i].next->prev = &current_block->sections[i];
                    }
                }
                current_block->sections_counter--;
            }

            sprintf(section_number_char, "%d", section_number);
            MyString return_string = section_number_char;
            return_string += { ",D," };
            return_string += attribute_name;
            return_string += { " == deleted" };
            return return_string;
        }
    }
    return "";
}
