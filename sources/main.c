
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "ChainedHashTable.h"
#include "StringWrapper.h"
#include "ConfusingWrapper.h"

void getLine(char* string) {
    int i;
    char c;
    for (i = 0; (c = getchar()) != '\n'; i++) 
        if (i < String_MaxLength - 1) string[i] = c;

    int last_index = i < String_MaxLength - 1 ? i : String_MaxLength - 1;
    string[last_index] = '\0';
}

int option_prompt() {
    int option;
    printf(
        "\n"
        "\nMAIN MENU"
        "\n1 insert"
        "\n2 delete"
        "\n3 search"
        "\n4 print"
        "\n5 stats"
        "\n6 clear"
        "\n0 exit"
        "\nChoose your option: "
    );
    scanf("%d%*c", &option);
    return option;
}

int main() {

    #if 1

    String_init();
    printf("\nmax %d chars per string\n", String_MaxLength - 1);
    char* input = malloc(String_MaxLength);
    void* string_keyWrapper;
    Generic_KeyDataContainer stringContainer;
    srand(time(NULL));
    
    int size = 5000;
    ChainedHash_Table T = ChainedHash_CreateTable(size, String_MaxIntKey);

    int choice;
    while ((choice = option_prompt())) switch (choice) {
        case 1:  // insert
            printf("\nINSERT\n");

            // manual insertion
            /* printf("\nGive string to insert: ");
            getLine(input);
            if (!strcmp(input, "\0")) break;
            stringContainer = String_ContainerCreate(input);

            printf("\n %s", input);
            if (ChainedHash_Insert(T, stringContainer, String_keyWrappersEqual, String_keyWrapperToInt))
                printf("\n inserted");
            else printf("\n already exists"); */

            // massive random insertion
            for (int i = 0; i < size; i++) {
                int length = 1 + ((double)rand()/(double)RAND_MAX)*(String_MaxLength - 1);
                for (int c = 0; c < length; c++)
                    input[c] = 32 + ((double)rand()/(double)RAND_MAX)*(126-32);
                input[length] = '\0';
                if (!strcmp(input, "\0")) continue;
                stringContainer = String_ContainerCreate(input);
                if (!ChainedHash_Insert(T, stringContainer, String_keyWrappersEqual, String_keyWrapperToInt))
                    String_ContainerDelete(stringContainer);
            }

            break;
        
        case 2:  // delete
            printf("\nDELETE\n");
            
            printf("\nGive key to delete: ");
            getLine(input);
            string_keyWrapper = String_keyWrapperCreate(input);
            stringContainer = ChainedHash_Delete(T, string_keyWrapper, String_keyWrappersEqual, String_keyWrapperToInt);
            
            printf("\n %s", input);
            if (stringContainer) printf("\n deleted");
            else printf("\n not found");

            String_ContainerDelete(stringContainer);
            String_keyWrapperDelete(string_keyWrapper);
            break;
        
        case 3:  // search
            printf("\nSEARCH\n");
            
            printf("\nGive key to search: ");
            getLine(input);
            string_keyWrapper = String_keyWrapperCreate(input);
            stringContainer = ChainedHash_Search(T, string_keyWrapper, String_keyWrappersEqual, String_keyWrapperToInt);
            
            if (stringContainer) String_ContainerPrint(stringContainer);
            else printf("\n %s not found", input);

            String_keyWrapperDelete(string_keyWrapper);
            break;
        
        case 4:  // print
            printf("\nPRINT\n");
            ChainedHash_PrintTable(T, String_ContainerPrint);
            break;

        case 5:
            printf("\nSTATS\n");
            size_t elmts = ChainedHash_GetNumberOfElements(T);
            size_t slots = ChainedHash_GetNumberOfActiveSlots(T);
            printf(
                "\n Total number of elements : %d"
                "\n Number of non-empty slots: %d"
                "\n Avg number of elements   : %.2f",
                elmts, slots, (float)elmts/(float)slots
            );
            break;
        
        case 6:  // clear
            printf("\nCLEAR\n");
            ChainedHash_ClearTable(T, String_ContainerDelete, String_keyWrappersEqual);
            break;
        
        default:
            printf("\nPlease choose one of the below:");
            break;
    }
    
    ChainedHash_DeleteTable(T, String_ContainerDelete, String_keyWrappersEqual);
    free(input);

    #else

    int a, b;
    double c;
    void* confusing_keyWrapper;
    Generic_KeyDataContainer confusingContainer;

    ChainedHash_Table T = ChainedHash_CreateTable(9, ULONG_MAX);

    int choice;
    while ((choice = option_prompt())) switch (choice) {
        case 1:  // insert
            printf("\nINSERT\n");

            printf("\nGive a b c to insert: ");
            scanf("%d %d %lf%*c", &a, &b, &c);
            confusingContainer = Confusing_ContainerCreate(a, b, c);

            if (ChainedHash_Insert(T, confusingContainer, Confusing_keyWrappersEqual, Confusing_keyWrapperToInt)) {
                printf("inserted ");
                Confusing_ContainerPrint(confusingContainer);
            }
            else printf("\nkey %d already exists", a);
            break;
        
        case 2:  // delete
            printf("\nDELETE\n");
            
            printf("\nGive a to delete: ");
            scanf("%d%*c", &a);
            confusing_keyWrapper = Confusing_keyWrapperCreate(a);
            confusingContainer = ChainedHash_Delete(T, confusing_keyWrapper, Confusing_keyWrappersEqual, Confusing_keyWrapperToInt);

            if (confusingContainer) {
                printf("deleted ");
                Confusing_ContainerPrint(confusingContainer);
                Confusing_ContainerDelete(confusingContainer);
            }
            else printf("\nkey %d not found", a);

            Confusing_keyWrapperDelete(confusing_keyWrapper);
            break;
        
        case 3:  // search
            printf("\nSEARCH\n");
            
            printf("\nGive a to search: ");
            scanf("%d%*c", &a);
            confusing_keyWrapper = Confusing_keyWrapperCreate(a);
            confusingContainer = ChainedHash_Search(T, confusing_keyWrapper, Confusing_keyWrappersEqual, Confusing_keyWrapperToInt);

            if (confusingContainer) Confusing_ContainerPrint(confusingContainer);
            else printf("\nkey %d not found", a);

            Confusing_keyWrapperDelete(confusing_keyWrapper);
            break;
        
        case 4:  // print
            printf("\nPRINT\n");
            ChainedHash_PrintTable(T, Confusing_ContainerPrint);
            break;
        
        case 5:  // clear
            printf("\nCLEAR\n");
            ChainedHash_ClearTable(T, Confusing_ContainerDelete, Confusing_keyWrappersEqual);
            break;
        
        default:
            printf("\nPlease choose one of the below:");
            break;
    }
    
    ChainedHash_DeleteTable(T, Confusing_ContainerDelete, Confusing_keyWrappersEqual);
    
    #endif

    printf("\nQuitting...\n");
    return 0;
}