
/* ConfusingWrapper.c */

#include <stdio.h>
#include <stdlib.h>
#include "ConfusingWrapper.h"


size_t Confusing_keyWrapperToInt(void* ckw) {
    return ((Confusing_keyWrapper)ckw)->a;
}

bool Confusing_keyWrappersEqual(void* ckw1, void* ckw2) {
    return ((Confusing_keyWrapper)ckw1)->a ==
        ((Confusing_keyWrapper)ckw2)->a;
}

void* Confusing_keyWrapperCreate(int a) {
    Confusing_keyWrapper ckw = malloc(sizeof *ckw);
    ckw->a = a;
    return ckw;
}

void Confusing_keyWrapperDelete(void* ckw) {
    free(ckw);
}

void* Confusing_dataWrapperCreate(int a, int b, double c) {
    Confusing_dataWrapper cdw = malloc(sizeof *cdw);
    cdw->a_int = a;
    cdw->a_struct.b_int = b;
    cdw->a_struct.b_struct_ptr = malloc(sizeof *(cdw->a_struct.b_struct_ptr));
    cdw->a_struct.b_struct_ptr->c_double = c;
    return cdw;
}

void Confusing_dataWrapperDelete(void* cdw) {
    free(((Confusing_dataWrapper)cdw)->a_struct.b_struct_ptr);
    free(cdw);
}

Generic_KeyDataContainer Confusing_ContainerCreate(int a, int b, double c) {
    Generic_KeyDataContainer confusingContainer = malloc(sizeof *confusingContainer);
    confusingContainer->keyWrapper = Confusing_keyWrapperCreate(a);
    confusingContainer->dataWrapper = Confusing_dataWrapperCreate(a, b, c);
    return confusingContainer;
}

void Confusing_ContainerDelete(Generic_KeyDataContainer confusingContainer) {
    if (confusingContainer == NULL) return;
    
    Confusing_keyWrapperDelete(confusingContainer->keyWrapper);
    Confusing_dataWrapperDelete(confusingContainer->dataWrapper);
    free(confusingContainer);
}

void Confusing_ContainerPrint(Generic_KeyDataContainer confusingContainer) {
    if (confusingContainer != NULL) {
        Confusing_dataWrapper cdw = confusingContainer->dataWrapper;
        printf(
            "(%d, %d, %lf)", 
            cdw->a_int,
            cdw->a_struct.b_int,
            cdw->a_struct.b_struct_ptr->c_double
        );
    }
}
