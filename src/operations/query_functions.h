#ifndef QUERY_FUNCTIONS_H
#define QUERY_FUNCTIONS_H

#include "../data_structures/my_string.h"
#include "../data_structures/data_structures.h"
#include "../data_structures/double_linked_list.h"

/**
 * Get the total number of sections in the CSS document
 * @param block_list CSS block list
 * @return String with the section count
 */
MyString GetAmountOfSections(const DoubleLinkedList<BlockList>& block_list);

/**
 * Get the number of selectors in a specific section
 * @param block_list CSS block list
 * @param section_num Section number as string
 * @return String with the selector count for the section
 */
MyString GetAmountOfSelectorsInSectionI(DoubleLinkedList<BlockList>& block_list, MyString section_num);

/**
 * Get the number of attributes in a specific section
 * @param block_list CSS block list
 * @param section_num Section number as string
 * @return String with the attribute count for the section
 */
MyString GetAmountOfAttributesInSectionI(DoubleLinkedList<BlockList>& block_list, MyString section_num);

/**
 * Get the selector at specific position in a section
 * @param block_list CSS block list
 * @param selector_num Selector position as string
 * @param section_num Section number as string
 * @return String with the selector information
 */
MyString GetJselectorForIsection(DoubleLinkedList<BlockList>& block_list, MyString selector_num, MyString section_num);

/**
 * Get attribute value for a specific section
 * @param block_list CSS block list
 * @param attr_name Attribute name
 * @param section_num Section number as string
 * @return String with the attribute value
 */
MyString GetAttributeValueForSection(DoubleLinkedList<BlockList>& block_list, MyString attr_name, MyString section_num);

/**
 * Get the number of occurrences of an attribute across all sections
 * @param block_list CSS block list
 * @param attribute_name Attribute name to count
 * @return String with the occurrence count
 */
MyString GetAttributeOccurrences(DoubleLinkedList<BlockList>& block_list, MyString attribute_name);

/**
 * Get the number of occurrences of a selector across all sections
 * @param block_list CSS block list
 * @param selector_name Selector name to count
 * @return String with the occurrence count
 */
MyString GetSelectorOccurrences(DoubleLinkedList<BlockList>& block_list, MyString selector_name);

/**
 * Get attribute value for a specific selector
 * @param block_list CSS block list
 * @param attribute_name Attribute name
 * @param selector_name Selector name
 * @return String with the attribute value
 */
MyString GetAttributeValueForSelector(DoubleLinkedList<BlockList>& block_list, MyString attribute_name, MyString selector_name);

#endif // QUERY_FUNCTIONS_H
