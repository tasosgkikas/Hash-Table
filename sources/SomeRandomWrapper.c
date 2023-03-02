
/* SomeRandomWrapper.c */

#include <stdio.h>
#include <stdlib.h>
#include "SomeRandomWrapper.h"


/* Uses the Cantor pairing function to map each pair of integers to a unique integer, assuming unsigned integers. */
size_t SomeRandom_keyWrapperToInt(void* srkw) {
    int a = ((SomeRandom_keyWrapper)srkw)->a;
    int b = ((SomeRandom_keyWrapper)srkw)->b;
    return (a + b)*(a + b + 1)/2 + b;
}


/* Returns true if the keys of the given keyWrappers are equal, else false. Uses the fact tha the Cantor pairing function is one-to-one. */
bool SomeRandom_keyWrappersEqual(void* srkw1, void* srkw2) {
    return SomeRandom_keyWrapperToInt(srkw1) ==
        SomeRandom_keyWrapperToInt(srkw2);
}


/* Returns a new SomeRandom_keyWrapper pointer, initialized with the given pair of integers. */
void* SomeRandom_keyWrapperCreate(int a, int b) {
    SomeRandom_keyWrapper srkw = malloc(sizeof *srkw);
    srkw->a = a;
    srkw->b = b;
    return srkw;
}


/* Deletes the given SomeRandom_keyWrapper. */
void SomeRandom_keyWrapperDelete(void* srkw) {
    free(srkw);
}


/* Returns a new SomeRandom_dataWrapper pointer, initialized with the given data. */
void* SomeRandom_dataWrapperCreate(int a, int b, double c) {
    SomeRandom_dataWrapper cdw = malloc(sizeof *cdw);
    cdw->a_int = a;
    cdw->a_struct.b_int = b;
    cdw->a_struct.b_struct_ptr = malloc(sizeof *(cdw->a_struct.b_struct_ptr));
    cdw->a_struct.b_struct_ptr->c_double = c;
    return cdw;
}


/* Deletes the given SomeRandom_dataWrapper. */
void SomeRandom_dataWrapperDelete(void* cdw) {
    free(((SomeRandom_dataWrapper)cdw)->a_struct.b_struct_ptr);
    free(cdw);
}


/* Returns a pointer to a new SomeRandom key-data wrappers container. */
Generic_KeyDataContainer SomeRandom_ContainerCreate(int a, int b, double c) {
    Generic_KeyDataContainer SomeRandomContainer = malloc(sizeof *SomeRandomContainer);
    SomeRandomContainer->keyWrapper = SomeRandom_keyWrapperCreate(a, b);
    SomeRandomContainer->dataWrapper = SomeRandom_dataWrapperCreate(a, b, c);
    return SomeRandomContainer;
}


/* Deletes the given SomeRandom key-data wrappers container, as well as the contained wrappers. */
void SomeRandom_ContainerDelete(Generic_KeyDataContainer SomeRandomContainer) {
    if (SomeRandomContainer == NULL) return;
    
    SomeRandom_keyWrapperDelete(SomeRandomContainer->keyWrapper);
    SomeRandom_dataWrapperDelete(SomeRandomContainer->dataWrapper);
    free(SomeRandomContainer);
}


/* Prints the data of the data wrapper of the given key-data wrappers container. */
void SomeRandom_ContainerPrint(Generic_KeyDataContainer SomeRandomContainer) {
    if (SomeRandomContainer != NULL) {
        SomeRandom_dataWrapper cdw = SomeRandomContainer->dataWrapper;
        printf(
            "(%d, %d, %lf)", 
            cdw->a_int,
            cdw->a_struct.b_int,
            cdw->a_struct.b_struct_ptr->c_double
        );
    }
}
