
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "LinkedList.h"


/* Structure of each element in a doubly linked list. It contains a pointer to a key-data container and the next/prev list pointers . */
typedef struct _LinkedList_Element_Struct* _LinkedList_Element;
struct _LinkedList_Element_Struct {
    Generic_KeyDataContainer kdcont;
    _LinkedList_Element next, prev;
};


/* Returns a pointer to a new Linked-List element with given key-data container. */
_LinkedList_Element _LinkedList_CreateElement(
    Generic_KeyDataContainer kdcont
) {
    _LinkedList_Element element = malloc(sizeof *element);
    assert(element != NULL);

    element->kdcont = kdcont;

    return element;
}


/* Linked-List structure */
struct LinkedList_Struct {
    _LinkedList_Element nil;  // Τhe sentinel node of the Linked-List, kdcont = NULL.
};


/* Returns a pointer to a new, empty Linked-List containing only the sentinel node. */
LinkedList LinkedList_CreateList() {
    LinkedList L = malloc(sizeof *L);
    assert(L != NULL);

    L->nil = _LinkedList_CreateElement(NULL);
    L->nil->next = L->nil->prev = L->nil;

    return L;
}


/* Returns a pointer to the Linked-List element with the key of the given key wrapper (or L.nil if no such element exists). It uses the given keyWrappers_equal function to check for key equality. */
_LinkedList_Element _LinkedList_Search(
    LinkedList L, void* keyWrapper, 
    bool (*keyWrappers_equal)(void* keyWrapper1, void* keyWrapper2)
) {
    assert(L != NULL);
    assert(keyWrapper != NULL);

    _LinkedList_Element element = L->nil->next;
    while (element != L->nil && !keyWrappers_equal(element->kdcont->keyWrapper, keyWrapper))
        element = element->next;
    return element;
}


/* Returns a pointer to the key-data container with the key of the given key wrapper (or NULL if no such element exists). It uses the given keyWrappers_equal function to check for key equality. */
Generic_KeyDataContainer LinkedList_Search(
    LinkedList L, void* keyWrapper, 
    bool (*keyWrappers_equal)(void* keyWrapper1, void* keyWrapper2)
) {
    return _LinkedList_Search(L, keyWrapper, keyWrappers_equal)->kdcont;
}


/* Deletes the Linked-List element with the key of the given key wrapper and returns a pointer to the key-data container of the element (or NULL if no such element exists). It uses the given keyWrappers_equal function to check for key equality. Make sure to delete the returned key-data container accordingly. */
Generic_KeyDataContainer LinkedList_Delete(
    LinkedList L, void* keyWrapper, 
    bool (*keyWrappers_equal)(void* keyWrapper1, void* keyWrapper2)
) {
    _LinkedList_Element element = _LinkedList_Search(L, keyWrapper, keyWrappers_equal);
    if (element == L->nil) return NULL;

    Generic_KeyDataContainer kdcont = element->kdcont;
    
    element->prev->next = element->next;
    element->next->prev = element->prev;
    free(element);
    
    return kdcont;
}


/* Inserts the given key-data container at the head of the Linked-List and returns true (or false if another element with the given key already exists). It uses the given keyWrappers_equal function to check for key equality. */
bool LinkedList_Insert(
    LinkedList L, Generic_KeyDataContainer kdcont, 
    bool (*keyWrappers_equal)(void* keyWrapper1, void* keyWrapper2)
) {
    assert(kdcont != NULL);
    if (_LinkedList_Search(L, kdcont->keyWrapper, keyWrappers_equal) != L->nil) 
        return false;
    
    _LinkedList_Element element = _LinkedList_CreateElement(kdcont);
    element->next = L->nil->next;
    L->nil->next->prev = element;
    L->nil->next = element;
    element->prev = L->nil;

    return true;
}


/* Prints the contents of the Linked-List using the given KeyDataContainer_print function. */
void LinkedList_PrintList(
    LinkedList L, void (*KeyDataContainer_print)(Generic_KeyDataContainer kdcont)
) {
    assert(L != NULL);

    printf("[");
    _LinkedList_Element element = L->nil->next;
    while (element != L->nil) {
        if (element != L->nil->next) printf(", ");
        KeyDataContainer_print(element->kdcont);
        element = element->next;
    }
    printf("]");
}


/* Clears the contents of the Linked-List using the given KeyDataContainer_delete function. */
void LinkedList_ClearList(
    LinkedList L, void (*KeyDataContainer_delete)(Generic_KeyDataContainer kdcont), 
    bool (*keyWrappers_equal)(void* keyWrapper1, void* keyWrapper2)
) {
    assert(L != NULL);

    while (L->nil->next != L->nil)  // iterative head deletion, where head = L.nil.next
        KeyDataContainer_delete(LinkedList_Delete(L, L->nil->next->kdcont->keyWrapper, keyWrappers_equal));
}


/* Deletes the whole structure of the Linked-List using the given KeyDataContainer_delete function. CAUTION: after the execution of this method, LinkedList given argument is unusable, unless it is reinitialized using LinkedList_CreateList() method. */
void LinkedList_DeleteList(
    LinkedList L, void (*KeyDataContainer_delete)(Generic_KeyDataContainer kdcont), 
    bool (*keyWrappers_equal)(void* keyWrapper1, void* keyWrapper2)
) {
    assert(L != NULL);

    LinkedList_ClearList(L, KeyDataContainer_delete, keyWrappers_equal);
    free(L->nil);
    free(L);
}
