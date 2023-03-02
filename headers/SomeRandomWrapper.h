
/* SomeRandomWrapper.h */

#ifndef _SomeRandomWrapper_h_
#define _SomeRandomWrapper_h_
    
    #include "LinkedList.h"
    

    typedef struct {
        int a, b;
    } *SomeRandom_keyWrapper;

    typedef struct {
        int a_int;
        struct {
            int b_int;
            struct {
                double c_double;
            } *b_struct_ptr;
        } a_struct;
    } *SomeRandom_dataWrapper;

    size_t SomeRandom_keyWrapperToInt(void* srkw);
    bool SomeRandom_keyWrappersEqual(void* srkw1, void* srkw2);
    void* SomeRandom_keyWrapperCreate(int a, int b);
    void SomeRandom_keyWrapperDelete(void* srkw);
    Generic_KeyDataContainer SomeRandom_ContainerCreate(int a, int b, double c);
    void SomeRandom_ContainerDelete(Generic_KeyDataContainer SomeRandomContainer);
    void SomeRandom_ContainerPrint(Generic_KeyDataContainer SomeRandomContainer);

#endif
