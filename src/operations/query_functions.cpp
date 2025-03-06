#include "query_functions.h"
#include "../utils/utils.h"
#include <cstdio>

MyString GetAmountOfSections(const DoubleLinkedList<BlockList>& block_list) {
    int section_counter = 0;
    char section_counter_char[CSS_PROCESSOR_MAX_SIZE];
    BlockList* current_block = const_cast<BlockList*>(block_list.head_);

    while (current_block) {
        section_counter += current_block->sections_counter;
        current_block = current_block->next;
    }

    sprintf(section_counter_char, "%d", section_counter);
    MyString return_string = { "? == " };
    return_string += section_counter_char;
    return return_string;
}

MyString GetAmountOfSelectorsInSectionI(DoubleLinkedList<BlockList>& block_list, MyString section_num) {
    int section_number = MyStringToInt(section_num);
    int current_section = 0;
    char section_number_char[CSS_PROCESSOR_MAX_SIZE];
    char selectors_counter_char[CSS_PROCESSOR_MAX_SIZE];

    for (BlockList* current_block = block_list.GetFirstNode(); current_block; current_block = current_block->next) {
        if (!current_block->sections) continue;
        for (int i = 0; i < current_block->sections_counter; i++) {
            current_section++;
            if (current_section == section_number) {
                int selectors_counter = 0;
                if (!current_block->sections[i].selectors) continue;
                for (SelectorList* current_selector = current_block->sections[i].selectors->GetFirstNode(); current_selector; current_selector = current_selector->next) {
                    selectors_counter++;
                }

                sprintf(section_number_char, "%d", section_number);
                sprintf(selectors_counter_char, "%d", selectors_counter);
                MyString return_string = section_number_char;
                return_string += { ",S,? == " };
                return_string += selectors_counter_char;
                return return_string;
            }
        }
    }
    return "";
}

MyString GetAmountOfAttributesInSectionI(DoubleLinkedList<BlockList>& block_list, MyString section_num) {
    int section_number = MyStringToInt(section_num);
    int current_section = 0;
    char section_number_char[CSS_PROCESSOR_MAX_SIZE];
    char attributes_counter_char[CSS_PROCESSOR_MAX_SIZE];

    for (BlockList* current_block = block_list.GetFirstNode(); current_block; current_block = current_block->next) {
        if (!current_block->sections) continue;
        for (int i = 0; i < current_block->sections_counter; i++) {
            current_section++;
            if (current_section == section_number) {
                SectionList& section_list = current_block->sections[i];
                AttributeList* attr = section_list.attributes->GetFirstNode();
                RemoveDuplicates(section_list.attributes);
                int counter_attributes = 0;
                if (section_list.attributes) {
                    for (AttributeList* attr = section_list.attributes->GetFirstNode(); attr; attr = attr->next) {
                        counter_attributes++;
                    }
                }
                else {
                    return "";
                }

                sprintf(section_number_char, "%d", section_number);
                sprintf(attributes_counter_char, "%d", counter_attributes);
                MyString return_string = section_number_char;
                return_string += { ",A,? == " };
                return_string += attributes_counter_char;
                return return_string;
            }
        }
    }
    return "";
}

MyString GetJselectorForIsection(DoubleLinkedList<BlockList>& block_list, MyString selector_num, MyString section_num) {
    if (block_list.GetFirstNode() == nullptr) {
        return "";
    }

    int section_number = MyStringToInt(section_num);
    int selector_number = MyStringToInt(selector_num);
    int current_section = 0;

    for (BlockList* current_block = block_list.GetFirstNode(); current_block; current_block = current_block->next) {
        if (!current_block->sections) continue;
        for (int i = 0; i < current_block->sections_counter; i++) {
            current_section++;
            if (current_section == section_number) {
                if (current_block->sections[i].selectors == nullptr) return "";

                SelectorList* selector = current_block->sections[i].selectors->GetFirstNode();
                int current_selector = 0;
                while (selector) {
                    current_selector++;
                    if (current_selector == selector_number) {
                        if (selector == nullptr) return "";

                        char section_number_char[CSS_PROCESSOR_MAX_SIZE];
                        char selector_number_char[CSS_PROCESSOR_MAX_SIZE];
                        sprintf(section_number_char, "%d", section_number);
                        sprintf(selector_number_char, "%d", selector_number);
                        MyString return_string = section_number_char;
                        return_string += { ",S," };
                        return_string += selector_number_char;
                        return_string += {" == "};
                        return_string += selector->name;
                        return return_string;
                    }
                    selector = selector->next;
                }
                return "";
            }
        }
    }
    return "";
}

MyString GetAttributeValueForSection(DoubleLinkedList<BlockList>& block_list, MyString attr_name, MyString section_num) {
    int section_number = MyStringToInt(section_num);
    int current_section = 0;

    for (BlockList* current_block = block_list.GetFirstNode(); current_block; current_block = current_block->next) {
        if (!current_block->sections) continue;
        for (int i = 0; i < current_block->sections_counter; i++) {
            current_section++;
            if (current_section == section_number) {
                SectionList& section_list = current_block->sections[i];
                if (!section_list.attributes) continue;
                AttributeList* attr = section_list.attributes->GetFirstNode();
                while (attr) {
                    if (!attr->name || !attr->value) continue;
                    if (attr->name == attr_name) {
                        char section_number_char[CSS_PROCESSOR_MAX_SIZE];
                        sprintf(section_number_char, "%d", section_number);
                        MyString return_string = section_number_char;
                        return_string += { ",A," };
                        return_string += attr_name;
                        return_string += {" =="};
                        return_string += attr->value;
                        return return_string;
                    }
                    attr = attr->next;
                }
            }
        }
    }
    return "";
}

MyString GetAttributeOccurrences(DoubleLinkedList<BlockList>& block_list, MyString attribute_name) {
    int occurrences_counter = 0;
    char occurrences_counter_char[CSS_PROCESSOR_MAX_SIZE];

    for (BlockList* current_block = block_list.GetFirstNode(); current_block; current_block = current_block->next) {
        if (!current_block->sections) continue;
        for (int i = 0; i < current_block->sections_counter; i++) {
            SectionList* current_section = &(current_block->sections[i]);
            if (!current_section->attributes) continue;

            for (AttributeList* current_attribute = current_section->attributes->GetFirstNode(); current_attribute; current_attribute = current_attribute->next) {
                if (current_attribute->name == attribute_name) {
                    occurrences_counter++;
                    break;
                }
            }
        }
    }

    sprintf(occurrences_counter_char, "%d", occurrences_counter);
    MyString return_string = attribute_name;
    return_string += { ",A,? == " };
    return_string += occurrences_counter_char;
    return return_string;
}

MyString GetSelectorOccurrences(DoubleLinkedList<BlockList>& block_list, MyString selector_name) {
    int occurrences_counter = 0;
    char occurrences_counter_char[CSS_PROCESSOR_MAX_SIZE];

    for (BlockList* current_block = block_list.GetFirstNode(); current_block; current_block = current_block->next) {
        for (int i = 0; i < current_block->sections_counter; i++) {
            SectionList* current_section = &(current_block->sections[i]);

            if (current_section->selectors) {
                for (SelectorList* current_selector = current_section->selectors->GetFirstNode(); current_selector; current_selector = current_selector->next) {
                    if (current_selector && current_selector->name == selector_name) {
                        occurrences_counter++;
                    }
                }
            }
        }
    }

    sprintf(occurrences_counter_char, "%d", occurrences_counter);
    MyString return_string = selector_name;
    return_string += { ",S,? == " };
    return_string += occurrences_counter_char;
    return return_string;
}

MyString GetAttributeValueForSelector(DoubleLinkedList<BlockList>& block_list, MyString attribute_name, MyString selector_name) {
    MyString attribute_value = "";
    bool has_matching_selector = false;
    bool has_matching_attribute = false;

    for (BlockList* current_block = block_list.GetFirstNode(); current_block; current_block = current_block->next) {
        for (int i = 0; i < current_block->sections_counter; i++) {
            SectionList* current_section = &(current_block->sections[i]);

            if (current_section->selectors) {
                SelectorList* last_matching_selector = nullptr;

                for (SelectorList* current_selector = current_section->selectors->GetFirstNode(); current_selector; current_selector = current_selector->next) {
                    if (current_selector && current_selector->name == selector_name) {
                        last_matching_selector = current_selector;
                        has_matching_selector = true;
                    }
                }

                if (last_matching_selector && current_section->attributes) {
                    for (AttributeList* current_attribute = current_section->attributes->GetFirstNode(); current_attribute; current_attribute = current_attribute->next) {
                        if (current_attribute && current_attribute->name == attribute_name) {
                            attribute_value = current_attribute->value;
                            has_matching_attribute = true;
                        }
                    }
                }
            }
        }
    }
    if (has_matching_selector && has_matching_attribute) {
        MyString return_string = selector_name;
        return_string += { ",E," };
        return_string += attribute_name;
        return_string += { " ==" };
        return_string += attribute_value;
        return return_string;
    }
    else return "";
}
