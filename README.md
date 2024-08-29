# About Chained Hashing Program
This project implements a hash table using Chained Hashing, which resolves hash collisions. This is done by using an array of pointers, where each pointer references the head of a linked list that stores all records with the same hash index. I focused on the implementation of hash tables, specifically focusing on efficient memory management, collision resolution using linked lists, and dynamic memory allocation. The implementation includes key operations such as insertion, removal, and lookup of records, as well as the necessary functions to manage the dynamic memory utilized by the hash table.

# Implementation
The project includes the implementation of a templated Table class, which uses a chained hash table to store records. The hash table is implemented using an array of linked lists, where each linked list stores records that hash to the same index.

## Key Components:
Memory Allocation and Deallocation: The table manages dynamic memory by allocating nodes for linked lists on insertions and properly deallocating them on deletions and during object destruction.
Collision Resolution: Collisions in the hash table are resolved using linked lists, ensuring efficient storage and retrieval even when multiple records hash to the same index.
Table Operations: The table supports basic operations such as insert, remove, is_present, and find, providing efficient handling of records based on their keys.
Helper Functions: Private helper functions are used to find nodes and manage linked lists, streamlining the implementation of public operations.
Memory Management: The implementation includes a custom memory management mechanism that ensures the efficient use of heap memory and prevents memory leaks. The destructor, copy constructor, and assignment operator are carefully designed to handle dynamic memory correctly.

# Testing
The project includes two test programs:

## Interactive Test Program (testtab2.cxx) 
This program allows for interactive testing of the table operations, providing immediate feedback on the functionality.
## Automated Test Program (tabexam.cxx)
This program performs automated testing, verifying the correctness of the table implementation through a series of predefined tests. The tests cover operations such as insertion, removal, and checking for memory leaks. The results of these tests provide a measure of the table's reliability and efficiency.
