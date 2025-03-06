#ifndef COMMAND_PROCESSOR_H
#define COMMAND_PROCESSOR_H

#include "../data_structures/my_string.h"
#include "../data_structures/data_structures.h"
#include "../data_structures/double_linked_list.h"
#include "../operations/query_functions.h"
#include "../operations/delete_functions.h"

/**
 * Process command parameters from input string
 * @param block_list CSS block list
 * @param cmd Command parameters to parse and fill
 */
void ProcessParameters(DoubleLinkedList<BlockList>& block_list, CommandParameters& cmd);

/**
 * Handle delete commands
 * @param block_list CSS block list
 * @param cmd Command parameters
 */
void HandleDCommand(DoubleLinkedList<BlockList>& block_list, CommandParameters& cmd);

/**
 * Handle extract commands
 * @param block_list CSS block list
 * @param cmd Command parameters
 */
void HandleECommand(DoubleLinkedList<BlockList>& block_list, CommandParameters& cmd);

/**
 * Handle selector commands
 * @param block_list CSS block list
 * @param cmd Command parameters
 */
void HandleSCommand(DoubleLinkedList<BlockList>& block_list, CommandParameters& cmd);

/**
 * Handle attribute commands
 * @param block_list CSS block list
 * @param cmd Command parameters
 */
void HandleACommand(DoubleLinkedList<BlockList>& block_list, CommandParameters& cmd);

/**
 * Process a command based on its type
 * @param block_list CSS block list
 * @param cmd Command parameters
 */
void ProcessCommand(DoubleLinkedList<BlockList>& block_list, CommandParameters& cmd);

/**
 * Parse command from input
 * @param block_list CSS block list
 * @param cmd Command parameters
 * @param flag Flag indicating special processing conditions
 */
void ParseCommands(DoubleLinkedList<BlockList>& block_list, CommandParameters& cmd, bool flag);

/**
 * Print output from command processing
 * @param cmd Command parameters containing output
 * @param flag Flag used for formatting
 */
void PrintOutput(CommandParameters& cmd, bool& flag);

#endif // COMMAND_PROCESSOR_H
