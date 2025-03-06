#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include "my_string.h"
#include "double_linked_list.h"

#define CSS_PROCESSOR_SECTIONS_IN_BLOCK 8
#define CSS_PROCESSOR_MAX_SIZE 500

struct AttributeList {
    MyString name = "";
    MyString value = "";
    AttributeList* next = nullptr;
    AttributeList* prev = nullptr;
};

struct SelectorList {
    MyString name = "";
    SelectorList* next = nullptr;
    SelectorList* prev = nullptr;
};

struct SectionList {
    DoubleLinkedList<SelectorList>* selectors;
    DoubleLinkedList<AttributeList>* attributes;
    SectionList* next = nullptr;
    SectionList* prev = nullptr;
};

struct BlockList {
    SectionList* sections = new SectionList[CSS_PROCESSOR_SECTIONS_IN_BLOCK];
    BlockList* next = nullptr;
    BlockList* prev = nullptr;
    int sections_counter = 0;
};

struct CommandParameters {
    char character;
    MyString input = "";
    MyString output = "";
    MyString first_parameter = "";
    MyString second_parameter = "";
    MyString third_parameter = "";
    MyString section_number = "";
    bool is_first_param_int = false;
    bool is_third_param_int = false;
};

#endif // DATA_STRUCTURES_H
