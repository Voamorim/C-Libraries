#include "../string_obj.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

char* input_file0_path = "TestFiles/test_file0.txt"; 
char* input_file1_path = "TestFiles/test_file1.txt";
char* input_file2_path = "TestFiles/test_file2.txt";
char* input_file3_path = "TestFiles/test_file3.txt";

char* readFileCString(char* input_file_path);

void testGetLineFromFileToString(void);
void testReadWordFromFileToString(void);
void testGetCopyString(void);
void testCopyStringToString(void);
void testReadFileToString(void);

int main(){
    testGetLineFromFileToString();
    testReadWordFromFileToString();
    testGetCopyString();
    testCopyStringToString();
    testReadFileToString();
    return 0;
}

void testGetLineFromFileToString(void){
    FILE* input_file0 = fopen(input_file0_path, "r");
    FILE* input_file1 = fopen(input_file1_path, "r");
    FILE* input_file2 = fopen(input_file2_path, "r");

    char *file0_contents = readFileCString(input_file0_path);
    String* string_file0 = getLineFromFileToString(input_file0);
    String* aux = NULL;

    while((aux = getLineFromFileToString(input_file0))){
        concatenateString(string_file0, aux);
        freeString(aux);
    }

    assert(compareStringCString(string_file0, file0_contents) == 0);
    puts("getLineFromFileToString() works for big text files.");

    free(file0_contents);
    freeString(string_file0);
    rewind(input_file0);

    char *file1_contents = readFileCString(input_file1_path);
    String* string_file1 = getLineFromFileToString(input_file1); 

    assert(compareStringCString(string_file1, file1_contents) == 0);
    puts("getLineFromFileToString() works for files with only a single word.");

    free(file1_contents);
    freeString(string_file1);
    rewind(input_file1);

    char *file2_contents = readFileCString(input_file2_path);
    String* string_file2 = getLineFromFileToString(input_file2);

    assert(compareStringCString(string_file2, file2_contents) == 0);
    puts("getLineFromFileToString() works for files with only a single letter.");

    free(file2_contents);
    freeString(string_file2);
    rewind(input_file2);
    
    fclose(input_file0);
    fclose(input_file1);
    fclose(input_file2);
}

void testReadWordFromFileToString(void){
    FILE* input_file3 = fopen(input_file3_path, "r");

    int nwords = 7;
    String* read_words[nwords];
    int i = 0;
    while(i < nwords){
        read_words[i] = readWordFromFileToString(input_file3);
        i++;
    }

    char* file3_words[] = {
        "Hello", "World", "Ola", "Mundo", "Bonjour", "le", "Monde"
    };
    String* actual_words[nwords];
    for(int j = 0; j < nwords; ++j){
        actual_words[j] = cstringToString(file3_words[j]);
    }

    for(int j = 0; j < nwords; ++j){
        assert(compareStrings(read_words[j], actual_words[j]) == 0);
    }
    puts("readWordFromFilesToString() works!");

    for(int j = 0; j < nwords; ++j){
        freeString(read_words[j]);
        freeString(actual_words[j]);
    }

    fclose(input_file3);
}

void testGetCopyString(void){
    char *cstring = "Hello World!!!";
    String* test_string = cstringToString(cstring);
    String *copy = getCopyString(test_string);

    assert(compareStrings(test_string, copy) == 0);
    puts("getCopyStringToString() works!!!");
}

void testCopyStringToString(void){
    char *cstring = "Hello World!!!";
    String* test_string = cstringToString(cstring);
    String* copy = createString(1); 
    copyStringToString(copy, test_string);

    assert(compareStrings(test_string, copy) == 0);
    puts("copyStringtoString() works!!!");
}

void testReadFileToString(void){
    String* input_file_path = cstringToString(input_file0_path);
    
    String* read_input_file0 = readFileToString(input_file_path);
    char* cstring_input_file0 = readFileCString(input_file0_path);

    assert(compareStringCString(read_input_file0, cstring_input_file0) == 0);
    puts("readFileToString() works!");
}

char* readFileCString(char* input_file_path){
    FILE* input_file = fopen(input_file_path, "rb");

    fseek(input_file, 0, SEEK_END);
    unsigned int file_size = ftell(input_file);
    rewind(input_file);

    char *file = (char*) malloc (sizeof(char) * (file_size + 1));
    fread(file, sizeof(char), file_size, input_file);

    file[file_size] = '\0';
    fclose(input_file);
    return file;
}