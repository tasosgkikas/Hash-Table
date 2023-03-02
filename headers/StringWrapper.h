
/* StringWrapper.h */

#ifndef _StringWrapper_h_
#define _StringWrapper_h_
    
    #include <stdlib.h>
    #include "LinkedList.h"


    typedef struct {
        char* string_key;
    } *String_keyWrapper;

    typedef struct {
        char* string;
        void* other_data;
    } *String_dataWrapper;

    // Upper bound of the number of characters a string can contain (including the null terminator \0).
    extern int String_MaxLength;  

    // Maximum integer key any string can be mapped to.
    extern size_t String_MaxIntKey;

    void String_init();
    size_t String_keyWrapperToInt(void* skw);
    bool String_keyWrappersEqual(void* skw1, void* skw2);
    void* String_keyWrapperCreate(char* string);
    void String_keyWrapperDelete(void* skw);
    Generic_KeyDataContainer String_ContainerCreate(char* string);
    void String_ContainerDelete(Generic_KeyDataContainer stringContainer);
    void String_ContainerPrint(Generic_KeyDataContainer stringContainer);

#endif
