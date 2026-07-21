#include "string_obj.h"

String* createString(const unsigned int initial_capacity) {
    String* string = (String*) malloc (sizeof(String));

    if (!string) {
        perror("[string.c][createString()] ERROR: Failed to allocate memory for String object.\n");
        return NULL;
    }

    // Allocates a char array with initial_capacity + 1 items
    string->buffer = (char*) malloc (sizeof(char) * (initial_capacity + 1));

    if (!string->buffer) {
        perror(
            "[string.c][createString()] ERROR: Failed to allocate memory for String object "
            "data.\n");
        return NULL;
    }

    // Always sets the first character to the null-terminator
    string->buffer[0] = '\0';
    string->size = 1;  
    string->capacity = initial_capacity + 1;

    return string;
}

unsigned int getSizeString(const String* string) {
    if (!string) {
        perror("[string.c][getSizeString()] WARNING: String object doesn't exist.\n");
        return 0;
    }

    if (string->capacity < 1) {
        perror(
            "[string.c][getSizeString()] WARNING: String object doesn't have a valid reserved "
            "capacity.\n");
        return 0;
    }

    if(!string->buffer){
        perror("[string.c][getSizeString()] WARNING: String object contents doesn't exist.\n");
        return 0;
    }

    if (string->buffer[string->size - 1] != '\0') {
        perror("[string.c][getSizeString()] WARNING: String object doesn't end with the expected character.\n");
    }

    return string->size;
}

unsigned int getReservedSizeString(const String* string) {
    if (!string) {
        perror("[string.c][getReservedSizeString()] WARNING: String object doesn't exist.\n");
        return 0;
    }

    if (string->capacity < 1) {
        perror(
            "[string.c][getReservedSizeString()] WARNING: String object doesn't have a valid reserved "
            "capacity.\n");
        return 0;
    }
    
    if(!string->buffer){
        perror("[string.c][getReservedSizeString()] WARNING: String object contents doesn't exist.\n");
        return 0;
    }

    if (string->buffer[string->size - 1] != '\0') {
        perror("[string.c][getReservedSizeString()] WARNING: String object doesn't end with the expected character.\n");
    }

    return string->capacity;
}

unsigned int getRemainingCapacityString(const String* string) {
    if (!string) {
        perror("[string.c][getRemainingCapacityString()] WARNING: String object doesn't exist.\n");
        return 0;
    }

    if (string->capacity < 1) {
        perror(
            "[string.c][getRemainingCapacityString()] WARNING: String object doesn't have a valid reserved "
            "capacity.\n");
        return 0;
    }
    
    if(!string->buffer){
        perror("[string.c][getRemainingCapacityString()] WARNING: String object contents doesn't exist.\n");
        return 0;
    }

    if (string->buffer[string->size - 1] != '\0') {
        perror("[string.c][getRemainingCapacityString()] WARNING: String object doesn't end with the expected character.\n");
    }

    return getReservedSizeString(string) - getSizeString(string);
}

void copyStringToString(String* dest, const String* src) {
    // Allocates more memory if there isn't enough space to hold the string to be copied
    if (getSizeString(src) > getReservedSizeString(dest)) {
        reallocCapacityString(dest, getSizeString(src));
    }

    strcpy(dest->buffer, src->buffer);
    dest->size = src->size;
}

void copyCStringToString(String* dest, const char* src) {
    if(!src) {
        perror("[string.c][copyCStringToString()] WARNING: Failed to copy CString to String object. CString doesn't exist.\n");
        return;
    }
    
    unsigned int cstring_size = strlen(src) + 1;

    // Allocates more memory if there isn't enough space to hold the string to be copied
    if (cstring_size > getReservedSizeString(dest)) {
        reallocCapacityString(dest, cstring_size);
    }

    strcpy(dest->buffer, src);
    dest->size = cstring_size;
}

String* getCopyString(const String* string) {
    if (!string) {
        perror("[string.c][getCopyString()] WARNING: String object doesn't exist.\n");
        return NULL;
    }

    if (string->capacity < 1) {
        perror(
            "[string.c][getCopyString()] WARNING: String object doesn't have a valid reserved "
            "capacity.\n");
        return NULL;
    }

    if(!string->buffer){
        perror("[string.c][getCopyString()] WARNING: String object contents doesn't exist.\n");
        return 0;
    }

    if (string->buffer[string->size - 1] != '\0') {
        perror("[string.c][getCopyString()] WARNING: String object doesn't end with the expected character.\n");
        return NULL;
    }

    String* new_string = createString(string->capacity - 1);

    strcpy(new_string->buffer, string->buffer);

    new_string->size = string->size;
    return new_string;
}

int compareStrings(const String* string_1, const String* string_2) {
    if (!string_1) {
        perror("[string.c][compareStrings()] WARNING: String string_1 object doesn't exist.\n");
        return 0;
    }

    if(!string_1->buffer){
        perror("[string.c][compareStrings()] WARNING: String string_1 object contents doesn't exist.\n");
        return 0;
    }

    if (string_1->buffer[string_1->size - 1] != '\0') {
        perror("[string.c][compareStrings()] WARNING: String string_1 object doesn't end with the expected character.\n");
        return 0;
    }

    if (!string_2) {
        perror("[string.c][compareStrings()] WARNING: String string_2 object doesn't exist.\n");
        return 0;
    }
    
    if(!string_2->buffer){
        perror("[string.c][compareStrings()] WARNING: String string_2 object contents doesn't exist.\n");
        return 0;
    }
    
    if (string_2->buffer[string_2->size - 1] != '\0') {
        perror("[string.c][compareStrings()] WARNING: String string_2 object doesn't end with the expected character.\n");
        return 0;
    }

    return strcmp(string_1->buffer, string_2->buffer);
}

int compareStringCString(const String* string, const char* cstring) {
    if (!string) {
        perror("[string.c][compareStringCString()] WARNING: String object doesn't exist.\n");
        return 0;
    }

    if(!string->buffer){
        perror("[string.c][compareStringCString()] WARNING: String object contents doesn't exist.\n");
        return 0;
    }

    if (string->capacity < 1) {
        perror(
            "[string.c][getCopyString()] WARNING: String object doesn't have a valid reserved "
            "capacity.\n");
        return 0;
    }

    if (string->buffer[string->size - 1] != '\0') {
        perror("[string.c][getCopyString()] WARNING: String object doesn't end with the expected character.\n");
    }

    return strcmp(string->buffer, cstring);
}

void concatenateString(String* dest, String* string) {
    // Allocates more memory if there isn't enough space to hold the contents of both strings inside the dest string
    if (getRemainingCapacityString(dest) <= getSizeString(string)) {
        reallocCapacityString(dest, getSizeString(dest) + getSizeString(string));
    }

    strcat(dest->buffer, string->buffer);

    dest->size = strlen(dest->buffer) + 1;
}

void pushBackCharString(String* string, const char c) {
    if (!string) {
        perror("[string.c][pushBackCharString()] WARNING: String object doesn't exist.\n");
        return;
    }

    if(!string->buffer){
        perror("[string.c][pushBackCharString()] WARNING: String object contents doesn't exist.\n");
        return;
    }

    if (string->capacity < 1) {
        perror(
            "[string.c][pushBackCharString()] WARNING: String object doesn't have a valid reserved "
            "capacity.\n");
        return;
    }

    if (string->buffer[string->size - 1] != '\0') {
        perror("[string.c][pushBackCharString()] WARNING: String object doesn't end with the expected character.\n");
    } 

    // Doubles string capacity if there's not any more space to fit the new character
    if (getRemainingCapacityString(string) <= 1) {
        reallocCapacityString(string, string->capacity * 2);
    }

    unsigned int last_char_pos = getSizeString(string) - 1;

    string->buffer[last_char_pos] = c;
    string->buffer[last_char_pos + 1] = '\0';
    string->size++;
}

void reallocCapacityString(String* string, const int size) {
    if (!string) {
        perror("[string.c][reallocCapacityString()] WARNING: String object doesn't exist.\n");
        return;
    }

    if(!string->buffer){
        perror("[string.c][reallocCapacityString()] WARNING: String object contents doesn't exist.\n");
        return;
    }

    if (string->capacity < 1) {
        perror(
            "[string.c][reallocCapacityString()] WARNING: String object doesn't have a valid reserved "
            "capacity.\n");
        return;
    }

    if (string->buffer[string->size - 1] != '\0') {
        perror("[string.c][reallocCapacityString()] WARNING: String object doesn't end with the expected character.\n");
    }

    string->buffer = (char*) realloc (string->buffer, sizeof(char) * size);

    if(!string->buffer) {
        perror("[string.c][reallocCapacityString()] WARNING: Failed to reallocate memory for String object contents.\n");
        return;
    }

    string->capacity = size;
}

String* getLineFromFileToString(FILE* input_file) {
    String* string = createString(10);

    while (1) {
        char c;
        
        // If EOF is reached, returns the string read so far.
        // If no characters were read, returns NULL.
        if ((c = fgetc(input_file)) == EOF) {
            if (string->size == 1) {
                freeString(string);
                return NULL;
            }
            break;
        }
       
        pushBackCharString(string, c);
        
        if (c == '\n') break;
    }

    return string;
}

String* readWordFromFileToString(FILE* input_file) {
    char c = fgetc(input_file);

    if (c == EOF) {
        perror("[string.c][readWordFromFileToString()] WARNING: Failed to read word from input file. Input file doesn't have any words.\n");
        return NULL;
    }

    while (c == ' ') {
        c = fgetc(input_file);

        if (c == EOF){
            perror("[string.c][readWordFromFileToString()] WARNING: Failed to read word from input file. Input file doesn't have any words.\n");
            return NULL;
        }
    }

    String* string = createString(10);

    while (!feof(input_file)) {
        if (!isalnum(c)) break;

        pushBackCharString(string, c);
        c = fgetc(input_file);
    }
    
    if(c != EOF) fseek(input_file, -1, SEEK_CUR);

    return string;
}

String* readFileToString(String* input_file_path){
    if(!input_file_path){
        perror("[string.c][readFileToString()] ERROR: Input file path string doesn't exist.\n");
        return NULL;
    }
    
    if (input_file_path->capacity < 1) {
        perror(
            "[string.c][readFileToString()] WARNING: Input file path string object doesn't have a valid reserved "
            "capacity.\n");
        return NULL;
    }

    if (input_file_path->buffer[input_file_path->size - 1] != '\0') {
        perror("[string.c][readFileToString()] ERROR: String object doesn't end with the expected null termination character.\n");
        return NULL;
    }

    FILE* input_file = fopen(input_file_path->buffer, "rb");
   
    if(!input_file){
        perror("[string.c][readFileToString()] ERROR: Failed to open input file.\n");
        fclose(input_file);
        return NULL;
    }

    if(fseek(input_file, 0, SEEK_END) != 0){
        perror("[string.c][readFileToString()] ERROR: Failed to measure total input file size.\n");
        fclose(input_file);
        return NULL;
    }


    int file_size = ftell(input_file);
    rewind(input_file);
    if(file_size < 0){
        perror("[string.c][readFileToString()] ERROR: Failed to measure total input file size.\n");
        fclose(input_file);
        return NULL;
    }

    String* str = createString(file_size + 1);

    if(!str){
        perror("[string.c][readFileToString()] ERROR: Failed to allocate memory for the string object.\n");
        fclose(input_file);
        freeString(str);
        return NULL;
    }

    unsigned int bytes_read = fread(str->buffer, sizeof(char), file_size, input_file);

    if(bytes_read != (unsigned int) file_size){
        perror("[string.c][readFileToString()] ERROR: Failed to read input file.\n");
        fclose(input_file);
        freeString(str);
        return NULL;
    }

    str->buffer[file_size] = '\0';
    str->size = file_size + 1;

    fclose(input_file);
    return str;
}

String* cstringToString(char* cstring) {
    if(!cstring){
        perror("[string.c][copyCStringToString()] WARNING: Failed to build String from CString. CString doesn't exist.\n");
        return NULL;
    }

    unsigned int cstring_len = strlen(cstring);
    String* new_string = createString(cstring_len);
    copyCStringToString(new_string, cstring);
    return new_string;
}

void printString(const String *string){
    printf("%s", string->buffer);
}

void freeString(String* string) {
    if (!string) {
        perror("[string.c][freeString()] WARNING: String object doesn't exist.\n");
        return;
    }

    if (string->buffer) 
        free(string->buffer);

    free(string);
}
