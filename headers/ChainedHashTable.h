
#ifndef _ChainedHashTable_h_
#define _ChainedHashTable_h_
    
    #include "LinkedList.h"

    /* Pointer to direct-address table structure */
    typedef struct ChainedHash_Table_Struct* ChainedHash_Table;

    ChainedHash_Table ChainedHash_CreateTable(size_t size, size_t max_int_key);
    
    Generic_KeyDataContainer ChainedHash_Search(ChainedHash_Table T, void* keyWrapper, bool (*keyWrappers_equal)(void* keyWrapper1, void* keyWrapper2), size_t (*keyWrapper_to_int)(void* keyWrapper));
    Generic_KeyDataContainer ChainedHash_Delete(ChainedHash_Table T, void* keyWrapper, bool (*keyWrappers_equal)(void* keyWrapper1, void* keyWrapper2), size_t (*keyWrapper_to_int)(void* keyWrapper));
    bool ChainedHash_Insert(ChainedHash_Table T, Generic_KeyDataContainer kdcont, bool (*keyWrappers_equal)(void* keyWrapper1, void* keyWrapper2), size_t (*keyWrapper_to_int)(void* keyWrapper));
    void ChainedHash_PrintTable(ChainedHash_Table T, void (*KeyDataContainer_print)(Generic_KeyDataContainer kdcont));
    void ChainedHash_ClearTable(ChainedHash_Table T, void (*KeyDataContainer_delete)(Generic_KeyDataContainer kdcont), bool (*keyWrappers_equal)(void* keyWrapper1, void* keyWrapper2));
    void ChainedHash_DeleteTable(ChainedHash_Table T, void (*KeyDataContainer_delete)(Generic_KeyDataContainer kdcont), bool (*keyWrappers_equal)(void* keyWrapper1, void* keyWrapper2));
    
#endif
