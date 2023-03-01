
/* ConfusingWrapper.h */

#ifndef _ConfusingWrapper_h_
#define _ConfusingWrapper_h_
    
    #include "LinkedList.h"
    

    typedef struct {
        int a;
    } *Confusing_keyWrapper;

    typedef struct {
        int a_int;
        struct {
            int b_int;
            struct {
                double c_double;
            } *b_struct_ptr;
        } a_struct;
    } *Confusing_dataWrapper;

    size_t Confusing_keyWrapperToInt(void* ckw);
    bool Confusing_keyWrappersEqual(void* ckw1, void* ckw2);
    void* Confusing_keyWrapperCreate(int a);
    void Confusing_keyWrapperDelete(void* ckw);
    Generic_KeyDataContainer Confusing_ContainerCreate(int a, int b, double c);
    void Confusing_ContainerDelete(Generic_KeyDataContainer confusingContainer);
    void Confusing_ContainerPrint(Generic_KeyDataContainer confusingContainer);

#endif
