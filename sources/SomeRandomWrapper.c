
/* SomeRandomWrapper.c */

#include <stdio.h>
#include <stdlib.h>
#include "SomeRandomWrapper.h"


size_t SomeRandom_keyWrapperToInt(void* ckw) {
    return ((SomeRandom_keyWrapper)ckw)->a;
}

bool SomeRandom_keyWrappersEqual(void* ckw1, void* ckw2) {
    return ((SomeRandom_keyWrapper)ckw1)->a ==
        ((SomeRandom_keyWrapper)ckw2)->a;
}

void* SomeRandom_keyWrapperCreate(int a) {
    SomeRandom_keyWrapper ckw = malloc(sizeof *ckw);
    ckw->a = a;
    return ckw;
}

void SomeRandom_keyWrapperDelete(void* ckw) {
    free(ckw);
}

void* SomeRandom_dataWrapperCreate(int a, int b, double c) {
    SomeRandom_dataWrapper cdw = malloc(sizeof *cdw);
    cdw->a_int = a;
    cdw->a_struct.b_int = b;
    cdw->a_struct.b_struct_ptr = malloc(sizeof *(cdw->a_struct.b_struct_ptr));
    cdw->a_struct.b_struct_ptr->c_double = c;
    return cdw;
}

void SomeRandom_dataWrapperDelete(void* cdw) {
    free(((SomeRandom_dataWrapper)cdw)->a_struct.b_struct_ptr);
    free(cdw);
}

Generic_KeyDataContainer SomeRandom_ContainerCreate(int a, int b, double c) {
    Generic_KeyDataContainer SomeRandomContainer = malloc(sizeof *SomeRandomContainer);
    SomeRandomContainer->keyWrapper = SomeRandom_keyWrapperCreate(a);
    SomeRandomContainer->dataWrapper = SomeRandom_dataWrapperCreate(a, b, c);
    return SomeRandomContainer;
}

void SomeRandom_ContainerDelete(Generic_KeyDataContainer SomeRandomContainer) {
    if (SomeRandomContainer == NULL) return;
    
    SomeRandom_keyWrapperDelete(SomeRandomContainer->keyWrapper);
    SomeRandom_dataWrapperDelete(SomeRandomContainer->dataWrapper);
    free(SomeRandomContainer);
}

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
