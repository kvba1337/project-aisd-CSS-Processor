#ifndef UTILS_H
#define UTILS_H

#include "../data_structures/my_string.h"
#include "../data_structures/data_structures.h"

/**
 * Remove leading and trailing spaces from a string
 * @param str String to trim
 * @return New string without leading and trailing spaces
 */
MyString RemoveSpaces(const MyString& str);

/**
 * Convert a string to an integer
 * @param str String to convert
 * @return Integer representation of the string
 */
int MyStringToInt(MyString& str);

/**
 * Check if a C-style string contains only digits
 * @param arr C-style string to check
 * @return true if string contains only digits, false otherwise
 */
bool IsDigit(const char arr[]);

/**
 * Remove duplicate attributes based on name from an attribute list
 * @param attribute_list List of attributes to process
 */
void RemoveDuplicates(DoubleLinkedList<AttributeList>* attribute_list);

#endif // UTILS_H
