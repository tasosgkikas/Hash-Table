
/* StringWrapper.c */

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "StringWrapper.h"


// printable characters are in the range [32, 126] of the ASCII code,
// this interval will be mapped to [32-31, 126-31]=[1, 95] to reduce computational complexity
#define ASCII_REPR_RADIX 127 - 31


int String_MaxLength;
size_t String_MaxIntKey;

/* Initializes the global String_MaxLength and String_MaxIntKey variables properly. */
void String_init() {
    String_MaxLength = log((double)SIZE_MAX + 1.0) / log(ASCII_REPR_RADIX);
    String_MaxIntKey = pow(ASCII_REPR_RADIX, String_MaxLength - 1) - 1;  // String_MaxLength - 1 because '\0' doesn't contribute to the key calculation
}


/* Interprets the string-key as a tuple of ASCII-code characters and expresses it as an equivalent-radix integer. */
size_t String_keyWrapperToInt(void* skw) {
    char* string_ptr = ((String_keyWrapper)skw)->string_key;
    int length = strlen(string_ptr);
    char string_arr[length];
    strncpy_s(string_arr, length, string_ptr, String_MaxLength);
    
    size_t integer = 0;
    for (int i = 0; i < length; i++)
        integer += (string_arr[i] - 31) * pow(ASCII_REPR_RADIX, i);
    return integer;
}


/* Returns true if the keys of the given keyWrappers are equal, else false. */
bool String_keyWrappersEqual(void* skw1, void* skw2) {
    return !strcmp(
        ((String_keyWrapper)skw1)->string_key,
        ((String_keyWrapper)skw2)->string_key
        );
}


/* Returns a new String_keyWrapper pointer, initialized with the given string. */
void* String_keyWrapperCreate(char* string) {
    String_keyWrapper skw = malloc(sizeof *skw);
    skw->string_key = malloc(String_MaxLength);
    strncpy_s(skw->string_key, strlen(string), string, String_MaxLength);
    return skw;
}


/* Deletes the given String_keyWrapper. */
void String_keyWrapperDelete(void* skw) {
    free(((String_keyWrapper)skw)->string_key);
    free(skw);
}


/* Returns a new String_dataWrapper pointer, initialized with the given string. */
void* String_dataWrapperCreate(char* string) {
    String_dataWrapper sdw = malloc(sizeof *sdw);
    sdw->string = malloc(String_MaxLength);
    strncpy_s(sdw->string, strlen(string), string, String_MaxLength);
    return sdw;
}


/* Deletes the given String_keyWrapper. */
void String_dataWrapperDelete(void* sdw) {
    free(((String_dataWrapper)sdw)->string);
    free(sdw);
}


/* Returns a pointer to a new String key-data wrappers container. Each wrapper is assigned the given string. */
Generic_KeyDataContainer String_ContainerCreate(char* string) {
    Generic_KeyDataContainer stringContainer = malloc(sizeof *stringContainer);
    stringContainer->keyWrapper = String_keyWrapperCreate(string);
    stringContainer->dataWrapper = String_dataWrapperCreate(string);
    return stringContainer;
}


/* Deletes the given String key-data wrappers container, as well as the contained wrappers. */
void String_ContainerDelete(Generic_KeyDataContainer stringContainer) {
    if (stringContainer == NULL) return;

    String_keyWrapperDelete(stringContainer->keyWrapper);
    String_dataWrapperDelete(stringContainer->dataWrapper);
    free(stringContainer);
}


/* Prints the string of the data wrapper of the given key-data wrappers container. */
void String_ContainerPrint(Generic_KeyDataContainer stringContainer) {
    if (stringContainer != NULL)  {
        String_dataWrapper sdw = stringContainer->dataWrapper;
        printf("%s", sdw->string);
    }
}
