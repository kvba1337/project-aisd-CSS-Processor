#ifndef CSS_PARSER_H
#define CSS_PARSER_H

#include "../data_structures/my_string.h"
#include "../data_structures/data_structures.h"
#include "../data_structures/double_linked_list.h"

/**
 * Parse a selector string into a list of selectors
 * @param selector_input String containing CSS selectors
 * @param selector_list List to store the parsed selectors
 */
void ParseSelectors(MyString& selector_input, DoubleLinkedList<SelectorList>* selector_list);

/**
 * Parse an attribute string into a list of attribute name-value pairs
 * @param attribute_input String containing CSS attributes
 * @param attribute_list List to store the parsed attributes
 */
void ParseAttributes(MyString& attribute_input, DoubleLinkedList<AttributeList>* attribute_list);

/**
 * Parse a CSS section containing selectors and attributes
 * @param selector_input String with selectors
 * @param attribute_input String with attributes
 * @param block_list Block list to add the section to
 */
void ParseSection(MyString& selector_input, MyString& attribute_input, DoubleLinkedList<BlockList>& block_list);

/**
 * Parse a complete CSS document from standard input
 * @param block_list Block list to store the parsed CSS structure
 */
void ParseCSS(DoubleLinkedList<BlockList>& block_list);

#endif // CSS_PARSER_H
