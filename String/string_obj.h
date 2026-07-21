#ifndef STRING_OBJ_H
#define STRING_OBJ_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

/**
 * @struct String
 * @brief Represents a dynamically allocated string buffer with length and capacity tracking.
 */
typedef struct String{
	char *buffer;
	unsigned int size;
	unsigned int capacity;
} String;

/**
 * @brief Allocates and initializes a new String object
 * 
 * Allocates memory for a String structure with a reserved capacity equal to initial_capacity + 1. Automatically appends a null-terminator ('\0') to the contents.
 * 
 * @param initial_capacity Reserved memory capacity for the string buffer.
 * @return String* Pointer to the newly allocated String struct, or NULL on allocation failure.
 */
String* createString(const unsigned int initial_capaticy);

/**
 * @brief Gets the current size/length of the String.
 *
 * @param string Pointer to the String struct.
 * @return unsigned int Total length occupied by characters (including the null-terminator).
 */
unsigned int getSizeString(const String* string);

/**
 * @brief Gets the total capacity allocated in memory for the String.
 *
 * @param string Pointer to the String struct.
 * @return unsigned int Number of total characters allocated in memory.
 */
unsigned int getReservedSizeString(const String *string);

/**
 * @brief Calculates the unused buffer space remaining in the String.
 *
 * @param string Pointer to the String struct.
 * @return unsigned int Number of remaining available bytes before a realloc is required.
 */
unsigned int getRemainingCapacityString(const String *string);

/**
 * @brief Copies contents from one String struct to another.
 *
 * @param dest Pointer to the destination String.
 * @param src Pointer to the source String to copy from.
 */
void copyStringToString(String *dest, const String *src);

/**
 * @brief Copies a standard C-style string (null-terminated char array) into a String struct.
 *
 * @param dest Pointer to the destination String struct.
 * @param src Pointer to the source C-string buffer.
 */
void copyCStringToString(String *dest, const char *src);

/**
 * @brief Creates a deep copy of a String struct.
 *
 * @param string Pointer to the String struct to clone.
 * @return String* Pointer to the newly allocated copy of the String.
 */
String* getCopyString(const String *string);

/**
 * @brief Compares two String structs lexicographically.
 *
 * @param string_1 Pointer to the first String struct.
 * @param string_2 Pointer to the second String struct.
 * @return int 
 *          0 if strings are equal,
 *         -1 if string_1 is less than string_2,
 *         +1 if string_1 is greater than string_2.
 */
int compareStrings(const String *string_1, const String *string_2);

/**
 * @brief Compares a String struct against a standard C-style string.
 *
 * @param string Pointer to the String struct.
 * @param cstring Pointer to the null-terminated char array.
 * @return int 
 *          0 if strings are equal,
 *         -1 if string is less than cstring,
 *         +1 if string is greater than cstring.
 */
int compareStringCString(const String *string, const char *cstring);

/**
 * @brief Concatenates the contents of a source String to a destination String.
 *
 * Automatically reallocates memory if the destination string lacks adequate capacity.
 *
 * @param dest Pointer to the destination String struct.
 * @param src Pointer to the String struct to append.
 */
void concatenateString(String *dest, String *string);

/**
 * @brief Appends a single character to the end of a String.
 *
 * Automatically resizes the internal buffer if additional capacity is required.
 *
 * @param string Pointer to the String struct.
 * @param c Character to append.
 */
void pushBackCharString(String *string, const char c);

/**
 * @brief Reallocates the internal buffer capacity for a String struct.
 *
 * @param string Pointer to the String struct.
 * @param size New total capacity size to reserve in memory.
 */
void reallocCapacityString(String *string, const int size);

/**
 * @brief Reads a single line from an open text file into a new String struct.
 *
 * @param input_file Pointer to the active file stream (`FILE*`).
 * @return String* Pointer to a newly created String containing the line read, or NULL on error/EOF.
 */
String* getLineFromFileToString(FILE *input_file);

/**
 * @brief Reads a single word from an open text file into a new String struct.
 *
 * @param input_file Pointer to the active file stream (`FILE*`).
 * @return String* Pointer to a newly created String containing the word read, or NULL on error/EOF.
 */
String* readWordFromFileToString(FILE *input_file);

/**
 * @brief Opens a file from a given path and reads its entire contents into a String struct.
 *
 * @param input_file_path Pointer to a String containing the file path.
 * @return String* Pointer to a newly created String with the entire file contents, or NULL on failure.
 */
String* readFileToString(String* input_file_path);

/**
 * @brief Converts a standard C-string into a dynamic String struct.
 *
 * Note: Does not free the original input C-string parameter.
 *
 * @param cstring Standard C-style string to convert.
 * @return String* Pointer to the newly allocated String struct.
 */
String* cstringToString(char *cstring);

/**
 * @brief Prints the contents of a String struct to `stdout`.
 *
 * @param string Pointer to the String struct to display.
 */
void printString(const String *string);

/**
 * @brief Deallocates a String struct and its internal character buffer from memory.
 *
 * @param string Pointer to the String struct to free.
 */
void freeString(String *string);

#endif