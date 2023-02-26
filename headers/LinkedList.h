
/* LinkedList.h */

#ifndef _LinkedList_h_
#define _LinkedList_h_
    
    #include <stdbool.h>

    /* Pointer to key-data container. */
    typedef struct {
        void* keyWrapper;  // Κey wrapper of the element.
        void* dataWrapper;  // Satellite data wrapper of the element.
    } *Generic_KeyDataContainer;

    /* Pointer to Linked-List structure */
    typedef struct LinkedList_Struct* LinkedList;

    LinkedList LinkedList_CreateList();

    Generic_KeyDataContainer LinkedList_Search(
        LinkedList L, void* keyWrapper, 
        bool (*keyWrappers_equal)(void* keyWrapper1, void* keyWrapper2));

    Generic_KeyDataContainer LinkedList_Delete(
        LinkedList L, void* keyWrapper, 
        bool (*keyWrappers_equal)(void* keyWrapper1, void* keyWrapper2));

    bool LinkedList_Insert(
        LinkedList L, Generic_KeyDataContainer kdcont, 
        bool (*keyWrappers_equal)(void* keyWrapper1, void* keyWrapper2));

    void LinkedList_PrintList(
        LinkedList L, void (*KeyDataContainer_print)(Generic_KeyDataContainer kdcont));

    void LinkedList_ClearList(
        LinkedList L, void (*KeyDataContainer_delete)(Generic_KeyDataContainer kdcont), 
        bool (*keyWrappers_equal)(void* keyWrapper1, void* keyWrapper2));
        
    void LinkedList_DeleteList(
        LinkedList L, void (*KeyDataContainer_delete)(Generic_KeyDataContainer kdcont), 
        bool (*keyWrappers_equal)(void* keyWrapper1, void* keyWrapper2));
    
#endif
