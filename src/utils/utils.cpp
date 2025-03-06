#include "utils.h"
#include <cctype>

MyString RemoveSpaces(const MyString& str) {
    MyString trimmed_str = "";
    int start = 0;
    int end = str.Length() - 1;
    while (start <= end && str[start] == ' ') {
        start++;
    }

    while (end >= start && str[end] == ' ') {
        end--;
    }

    for (int i = start; i <= end; i++) {
        trimmed_str += str[i];
    }

    return trimmed_str;
}

int MyStringToInt(MyString& str) {
    int result = 0;
    for (int i = 0; i < str.Length(); ++i) {
        if (str[i] >= '0' && str[i] <= '9') {
            result = result * 10 + (str[i] - '0');
        }
    }
    return result;
}

bool IsDigit(const char arr[]) {
    int i = 0;
    while (i < strlen(arr)) {
        if (!isdigit(arr[i]))
            return false;
        i++;
    }
    return true;
}

void RemoveDuplicates(DoubleLinkedList<AttributeList>* attribute_list) {
    if (!attribute_list || !attribute_list->head_) {
        return;
    }

    AttributeList* last_node = attribute_list->GetLastNode();
    while (last_node) {
        AttributeList* current_node = attribute_list->head_;
        while (current_node && current_node != last_node) {
            if (current_node->name == last_node->name) {
                AttributeList* temp = current_node;
                if (current_node == attribute_list->head_) {
                    attribute_list->head_ = current_node->next;
                }
                else {
                    current_node->prev->next = current_node->next;
                }
                if (current_node->next) {
                    current_node->next->prev = current_node->prev;
                }
                current_node = current_node->next;
                delete temp;
            }
            else {
                current_node = current_node->next;
            }
        }
        last_node = last_node->prev;
    }
}
