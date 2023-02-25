
/* StringWrapper.h */

#ifndef _StringWrapper_h_
#define _StringWrapper_h_
    
    #include <stdlib.h>
    #include "LinkedList.h"

    extern int String_MaxLength;
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
