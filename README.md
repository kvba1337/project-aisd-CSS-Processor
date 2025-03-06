# CSS Processor

> A simple engine for processing and manipulating CSS structures

## Overview

The "CSS Processor" project implements a basic CSS processing engine that parses CSS blocks and executes commands on these structures. The system reads from standard input, alternating between CSS sections and command sections, then processes these inputs and outputs the results.

## Features

- **CSS Parsing**: Read and parse CSS blocks with selectors and attributes
- **Command Processing**: Execute various queries and modifications on CSS data
- **Data Manipulation**: Add, retrieve, and delete CSS components
- **Efficient Storage**: Optimized data structures for CSS representation
- **Query System**: Comprehensive command set for analyzing CSS structure

## Implementation Requirements

- **No Standard Library Containers**: STL containers, including `string`, cannot be used
- **Custom Data Structures**: All data structures must be implemented from scratch
- **Memory Management**: Proper memory handling required (no memory leaks)
- **No Smart Pointers**: Standard library smart pointers are forbidden (custom implementations allowed)
- **Code Readability**: Emphasis on clean, readable code structure

## CSS Representation

The CSS content is syntactically correct and consists of:

- **Selectors**: Optional comma-separated selectors preceding attribute blocks
- **Attribute Blocks**: Collections of attributes enclosed in curly braces
- **Attributes**: Name-value pairs separated by colons within blocks, terminated by semicolons

### Processing Rules
- Selectors may be omitted (applies attributes to everything)
- Valid CSS selectors are supported (assumed not to contain commas or braces)
- Attribute values can be any valid CSS constructs (assumed non-malicious)
- If an attribute name appears multiple times in a block, the last value takes precedence
- Selectors and attribute names/values don't require semantic interpretation
- CSS doesn't contain comments, @-type selectors, or nested blocks

## Command System

Commands are processed after being read from the input. They control and query the CSS data structures:

### Command Types
- **????** - Start command section
- **\*\*\*\*** - Resume reading CSS
- **?** - Print number of CSS blocks
- **i,S,?** - Print number of selectors for block i
- **i,A,?** - Print number of attributes for block i
- **i,S,j** - Print j-th selector for i-th block
- **i,A,n** - Print value of attribute n for i-th block
- **n,A,?** - Print total occurrences of attribute n across all blocks
- **z,S,?** - Print total occurrences of selector z across all blocks
- **z,E,n** - Print value of attribute n for selector z (last occurrence)
- **i,D,\*** - Delete entire block i
- **i,D,n** - Delete attribute n from block i

## Implementation Details

- Selectors and attributes must be stored as lists
- CSS blocks should be organized as a doubly-linked list for efficient lookups
- Each list node should contain an array of T=8 block structures (T configurable at compile time)
- The list should track occupancy count for efficient block-number-based operations
- Memory management must be optimized by reusing space in nodes and removing empty nodes

## Input Format

```
[CSS blocks]         # One or more CSS blocks
????                 # Command section marker
[commands]           # One or more commands
****                 # Optional: resume CSS input
[more CSS blocks]    # Optional: more CSS blocks
????                 # Optional: another command section
[more commands]      # Optional: more commands
```

## Output Format

For each command that produces output, the system outputs one line with the result after `==`:
- Command results are printed in the format: `command == result`

## Example

### Input

```
#breadcrumb { width: 80%; font-size: 9pt; }

h1, body { min-width: 780px; margin: 0; padding: 0; font-family: "Trebuchet MS", "Lucida Grande", Arial; font-size: 85%; color: #666666; }

h1, h2, h3, h4, h5, h6 {color: #0066CB;}
????
?
1,S,?
1,S,1
1,A,?
2,A,font-family
h1,S,?
color,A,?
h1,E,color
1,A,padding
1,D,*
?
2,D,color
?

h1, h2, h3, h4, h5, h6 {color: #0066FF;}
????
?
```

### Output

```
? == 3
1,S,? == 1
1,S,1 == #breadcrumb
1,A,? == 2
2,A,font-family == "Trebuchet MS", "Lucida Grande", Arial
h1,S,? == 2
color,A,? == 2
h1,E,color == #0066CB
1,D,* == deleted
? == 2
2,D,color == deleted
? == 1
? == 2
```

## Testing

The project should be tested with various inputs to ensure:
- Correct CSS parsing
- Accurate command processing
- Memory management efficiency
- Edge case handling
