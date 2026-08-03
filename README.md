# C Data Structures and Algorithms
 
This repository contains implementations of fundamental data structures and algorithms written in **C** using **generic programming with void pointers**, allowing complete type flexibility and abstraction.
 
All implementations are designed to be reusable and can work with any data type.
 
## Repository Structure
 
The project is organized into folders, each containing the implementation of a specific data structure or algorithm, along with tests and examples demonstrating usage:
 
| Folder / Module | Type | Description |
| :--- | :--- | :--- |
| 📂 [**`Vector`**](./Vector) | Data Structure | Dynamic array with automatic resizing |
| 📂 [**`LinkedList`**](./LinkedList) | Data Structure | Singly-linked list with generic nodes |
| 📂 [**`BinaryTree`**](./BinaryTree) | Data Structure | Binary search tree with in-order traversal |
| 📂 [**`MinHeap`**](./MinHeap) | Data Structure | Min-priority heap for efficient sorting and priority queues |
| 📂 [**`Trie`**](./Trie) | Data Structure | Prefix tree for string storage and retrieval |
| 📂 [**`String`**](./String) | Data Structure | Custom string object with manipulation methods |
| 📂 [**`QuickSort`**](./QuickSort) | Algorithm | Quick sort with divide-and-conquer approach |
| 📂 [**`MergeSort`**](./MergeSort) | Algorithm | Merge sort with stable sorting guarantees |
| 📂 [**`SegTree`**](./SegTree) | Data Structure | Segment tree for range queries and updates |
 
## Key Features
 
- **Generic Programming:** All implementations use `void*` pointers to work with any data type.
- **Flexible Comparators:** Custom comparison functions allow sorting and ordering of arbitrary types.
- **Memory Management:** Proper allocation and deallocation with cleanup functions.
- **Comprehensive Tests:** Each module includes test files demonstrating usage patterns.
- **C Standard:** Written in pure C without external dependencies. 
