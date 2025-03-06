#include "css_parser.h"
#include "../utils/utils.h"
#include <iostream>

void ParseSelectors(MyString& selector_input, DoubleLinkedList<SelectorList>* selector_list) {
    MyString selector_name = "";
    int i = 0;
    while (i < selector_input.Length()) {
        if ((selector_input[i] == ',' || (i == selector_input.Length() - 1 && !selector_name.IsEmpty()))) {
            if (selector_input.Length() - 1 == i) {
                selector_name += selector_input[i];
            }
            SelectorList* new_selector = new SelectorList;
            new_selector->name = RemoveSpaces(selector_name);
            selector_list->AddNode(new_selector);
            selector_name = "";
        }
        else {
            selector_name += selector_input[i];
        }
        i++;
    }
}

void ParseAttributes(MyString& attribute_input, DoubleLinkedList<AttributeList>* attribute_list) {
    MyString temp = "";
    int i = 0;
    while (i < attribute_input.Length()) {
        if (attribute_input[i] == ';' || (i == attribute_input.Length() - 1 && !temp.IsEmpty())) {
            if (attribute_input[i] != ';' && i == attribute_input.Length() - 1) {
                temp += attribute_input[i];
            }
            MyString attr_name = "";
            MyString attr_value = "";
            bool beginning_of_value = false;

            for (int j = 0; j < temp.Length(); j++) {
                if (temp[j] == ':') {
                    beginning_of_value = true;
                }
                else if (temp[j] == ';') {
                    beginning_of_value = false;
                }
                else if (beginning_of_value) {
                    attr_value += temp[j];
                }
                else {
                    attr_name += temp[j];
                }
            }

            AttributeList* new_attr = new AttributeList;
            new_attr->name = attr_name;
            new_attr->value = attr_value;
            attribute_list->AddNode(new_attr);
            temp = "";
        }
        else {
            temp += attribute_input[i];
        }
        i++;
    }
}

void ParseSection(MyString& selector_input, MyString& attribute_input, DoubleLinkedList<BlockList>& block_list) {
    BlockList* current_block = block_list.GetLastNode();
    SectionList current_section = current_block->sections[current_block->sections_counter];
    DoubleLinkedList<SelectorList>* selector_list = new DoubleLinkedList<SelectorList>;
    DoubleLinkedList<AttributeList>* attribute_list = new DoubleLinkedList<AttributeList>;

    if (current_block->sections_counter == CSS_PROCESSOR_SECTIONS_IN_BLOCK - 1) {
        BlockList* new_block = new BlockList;
        block_list.AddNode(new_block);
        current_block = block_list.GetLastNode();
        current_section = current_block->sections[current_block->sections_counter];
    }

    ParseSelectors(selector_input, selector_list);
    ParseAttributes(attribute_input, attribute_list);

    current_section.attributes = attribute_list;
    current_section.selectors = selector_list;
    current_block->sections[current_block->sections_counter] = current_section;
    current_block->sections_counter += 1;
}

void ParseCSS(DoubleLinkedList<BlockList>& block_list) {
    char character;
    MyString selector_input = "";
    MyString attribute_input = "";
    MyString input = "";
    bool beginning_of_attributes = false;

    while (std::cin >> character >> std::noskipws) {
        switch (character) {
        case '\n':
        case '\t':
            break;
        case '{':
            beginning_of_attributes = true;
            break;
        case '}':
            ParseSection(selector_input, attribute_input, block_list);
            selector_input = "";
            attribute_input = "";
            input = "";
            beginning_of_attributes = false;
            break;
        default:
            if (beginning_of_attributes) {
                attribute_input += character;
            }
            else {
                selector_input += character;
            }
            input += character;
            break;
        }

        if (input == "????") {
            return;
        }
        if (character == EOF) {
            return;
        }
    }
}
