
/* ChainedHashTable.c */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <time.h>
#include "ChainedHashTable.h"
#include "ChainedHashNumFuncs.h"


/* Hash table structure */
struct ChainedHash_Table_Struct {
    size_t size;  // Number of slots of the hash table.
    LinkedList* table;  // Τhe actual table of pointers to hash-table slots.
    size_t p, a, b;  // parameters of universal hash function
};


/* Returns a pointer to a new hash-table of given size. */
ChainedHash_Table ChainedHash_CreateTable(
    size_t size, size_t max_int_key
) {
    assert(size >= 0);

    ChainedHash_Table T = malloc(sizeof *T);
    assert(T != NULL);

    // memory allocation for all slots through "table" member
    T->size = size;
    T->table = malloc(size * (sizeof *T->table));
    assert(T->table != NULL);

    // slot initialization with new lists
    for (int i = 0; i < size; i++)
        T->table[i] = LinkedList_CreateList();

    // universal hash function parameters initialization
    srand(time(0));
    T->p = next_prime(max_int_key);
    T->a = rand_int(1, T->p - 1);
    T->b = rand_int(0, T->p - 1);

    return T;
}


/* Returns a pointer to the list of the slot of the given hash-table that the given keyWrapper hashes to. */
LinkedList _ChainedHash_GetHashList(
    ChainedHash_Table T, void* keyWrapper, 
    size_t (*keyWrapper_to_int)(void* keyWrapper)
) {
    assert(T != NULL);

    size_t key = keyWrapper_to_int(keyWrapper);
    return T->table[hash(key, T->a, T->b, T->p, T->size)];
}


/* Returns a pointer to the key-data container with the key of the given key wrapper (or NULL if no such element exists). It uses the given keyWrappers_equal function to check for key equality and keyWrapper_to_int function to map the keyWrapper to an integer key. */
Generic_KeyDataContainer ChainedHash_Search(
    ChainedHash_Table T, void* keyWrapper, 
    bool (*keyWrappers_equal)(void* keyWrapper1, void* keyWrapper2),
    size_t (*keyWrapper_to_int)(void* keyWrapper)
) {
    return LinkedList_Search(
        _ChainedHash_GetHashList(T, keyWrapper, keyWrapper_to_int), 
        keyWrapper, keyWrappers_equal
    );
}


/* Deletes from the hash-table the element with the key of the given key wrapper and returns a pointer to the key-data wrappers container of the element (or NULL if no such element exists). It uses the given keyWrappers_equal function to check for key equality. Make sure to accordingly delete the returned key-data wrappers container accordingly. */
Generic_KeyDataContainer ChainedHash_Delete(
    ChainedHash_Table T, void* keyWrapper, 
    bool (*keyWrappers_equal)(void* keyWrapper1, void* keyWrapper2),
    size_t (*keyWrapper_to_int)(void* keyWrapper)
) {
    return LinkedList_Delete(
        _ChainedHash_GetHashList(T, keyWrapper, keyWrapper_to_int), 
        keyWrapper, keyWrappers_equal
    );
}


/* Inserts the given key-data wrappers container in the hash-table and returns true (or false if another element with the same key already exists). It uses the given keyWrappers_equal function to check for key equality. */
bool ChainedHash_Insert(
    ChainedHash_Table T, Generic_KeyDataContainer kdcont, 
    bool (*keyWrappers_equal)(void* keyWrapper1, void* keyWrapper2),
    size_t (*keyWrapper_to_int)(void* keyWrapper)
) {
    return LinkedList_Insert(
        _ChainedHash_GetHashList(T, kdcont->keyWrapper, keyWrapper_to_int), 
        kdcont, keyWrappers_equal
    );
}


/* Traverses the hash-table slots and applies the given LinkedList_function to each encountered slot. LinkedList_function takes the corresponding given KeyDataContainer_function and the keyWrappers_equal function as arguments. */
void _ChainedHash_TraverseTable(
    ChainedHash_Table T, void (*LinkedList_function)(
        LinkedList L, void (*KeyDataContainer_function)(Generic_KeyDataContainer kdcont),
        bool (*keyWrappers_equal)(void* keyWrapper1, void* keyWrapper2)
    ), 
    void (*KeyDataContainer_function)(Generic_KeyDataContainer kdcont),
    bool (*keyWrappers_equal)(void* keyWrapper1, void* keyWrapper2)
) {
    assert(T != NULL);

    for (int i = 0; i < T->size; i++)
        LinkedList_function(T->table[i], KeyDataContainer_function, keyWrappers_equal);
}


/* Wrapper of the LinkedList_PrintList function, with a new line at the end of the list. */
void _ChainedHash_PrintList(
    LinkedList L, void (*KeyDataContainer_print)(Generic_KeyDataContainer kdcont),
    bool (*keyWrappers_equal)(void* keyWrapper1, void* keyWrapper2)
) {
    LinkedList_PrintList(L, KeyDataContainer_print);
    printf("\n");
}


/* Prints the contents of the hash-table using the given KeyDataContainer_print function. */
void ChainedHash_PrintTable(
    ChainedHash_Table T, void (*KeyDataContainer_print)(Generic_KeyDataContainer kdcont)
) {
    _ChainedHash_TraverseTable(
        T, _ChainedHash_PrintList, KeyDataContainer_print, (bool (*)(void *, void *))NULL
    );
}


/* Clears the contents of the hash-table using the given KeyDataContainer_delete function. */
void ChainedHash_ClearTable(
    ChainedHash_Table T, void (*KeyDataContainer_delete)(Generic_KeyDataContainer kdcont), 
    bool (*keyWrappers_equal)(void* keyWrapper1, void* keyWrapper2)
) {
    _ChainedHash_TraverseTable(
        T, LinkedList_ClearList, KeyDataContainer_delete, keyWrappers_equal
    );
}


/* Deletes and frees the whole structure of the hash-table using the given custom data wrapper deleter function. CAUTION: after the execution of this method, ChainedHash_Table given argument is unusable, unless it is recreated using ChainedHash_CreateTable() method with the same argument. */
void ChainedHash_DeleteTable(
    ChainedHash_Table T, void (*KeyDataContainer_delete)(Generic_KeyDataContainer kdcont), 
    bool (*keyWrappers_equal)(void* keyWrapper1, void* keyWrapper2)
) {
    _ChainedHash_TraverseTable(
        T, LinkedList_ClearList, KeyDataContainer_delete, keyWrappers_equal
    );

    free(T->table);
    free(T);
}
