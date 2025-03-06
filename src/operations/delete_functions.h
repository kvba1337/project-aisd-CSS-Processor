#ifndef DELETE_FUNCTIONS_H
#define DELETE_FUNCTIONS_H

#include "../data_structures/my_string.h"
#include "../data_structures/data_structures.h"
#include "../data_structures/double_linked_list.h"

/**
 * Delete an entire section from the CSS document
 * @param block_list CSS block list
 * @param section_num Section number to delete
 * @return String confirming deletion
 */
MyString DeleteSection(DoubleLinkedList<BlockList>& block_list, MyString section_num);

/**
 * Delete a specific attribute from a section
 * @param block_list CSS block list
 * @param attribute_name Name of attribute to delete
 * @param section_num Section number containing the attribute
 * @return String confirming deletion
 */
MyString DeleteAttributeFromSection(DoubleLinkedList<BlockList>& block_list, MyString attribute_name, MyString section_num);

#endif // DELETE_FUNCTIONS_H
