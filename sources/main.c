
/* main.c */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ChainedHashTable.h"
#include "StringWrapper.h"
#include "SomeRandomWrapper.h"

void getLine(char* string, size_t max_length) {
    int i;
    char c;
    for (i = 0; (c = getchar()) != '\n'; i++) 
        if (i < max_length - 1) string[i] = c;

    int length = i < max_length - 1 ? i : max_length - 1;
    string[length] = '\0';
}

void showCommands() {
    printf(
        "\nCommands and corresponding actions"
        "\ni : insert"
        "\nd : delete"
        "\ns : search"
        "\np : print"
        "\nc : clear"
        "\ne : exit"
        "\nh : commands"
        "\n"
    );
}

bool white(char c) {
    return (
        c == '\0' ||
        c == ' '  ||
        c == '\n'
    );
}

void strip(char* string) {
    int length = strlen(string);
    char str[length];
    strncpy_s(str, length, string, String_MaxLength);

    while (length > 0 && white(str[length - 1])) 
        length--;
    str[length] = '\0';

    int text = length - 1;
    while (text - 1 >= 0 && !white(str[text - 1]))
        text--;

    int i = 0;
    while (i < text && white(str[i]) && text + i <= length) {
        str[i] = str[text + i];
        i++;
    }

    strncpy_s(string, length, str, String_MaxLength);
}

char commandPrompt() {
    printf(">> ");

    char* buffer = malloc(BUFSIZ);
    getLine(buffer, BUFSIZ);
    strip(buffer);
    
    char command = buffer[0];
    if (strlen(buffer) > 1) command = '\r';
    free(buffer);

    return command;
}

int main() {

    #if 1  // toggle to switch between 'String' and 'SomeRandom' data type

    String_init();
    printf("\nmax %d chars per string\n", String_MaxLength - 1);
    char* input = malloc(String_MaxLength);
    void* string_keyWrapper;
    Generic_KeyDataContainer stringContainer;
    
    ChainedHash_Table T = ChainedHash_CreateTable(10, String_MaxIntKey);

    showCommands();
    char command;
    while ((command = commandPrompt()) != 'e') switch (command) {
        case 'h':  // commands
            showCommands();
            break;

        case 'i':  // insert
            printf("Give string to insert: ");
            getLine(input, String_MaxLength);
            if (!strcmp(input, "\0")) break;
            stringContainer = String_ContainerCreate(input);

            printf("%s", input);
            if (ChainedHash_Insert(
                T, stringContainer, String_keyWrappersEqual, String_keyWrapperToInt
                )) printf(" inserted\n");
            else {
                printf(" already exists\n");
                String_ContainerDelete(stringContainer);
            }
            break;
        
        case 'd':  // delete
            printf("Give key to delete: ");
            getLine(input, String_MaxLength);
            if (!strcmp(input, "\0")) break;
            string_keyWrapper = String_keyWrapperCreate(input);
            stringContainer = ChainedHash_Delete(
                T, string_keyWrapper, String_keyWrappersEqual, String_keyWrapperToInt
            );
            
            printf("%s", input);
            if (stringContainer) printf(" deleted\n");
            else printf(" not found\n");

            String_ContainerDelete(stringContainer);
            String_keyWrapperDelete(string_keyWrapper);
            break;
        
        case 's':  // search
            printf("Give key to search: ");
            getLine(input, String_MaxLength);
            if (!strcmp(input, "\0")) break;
            string_keyWrapper = String_keyWrapperCreate(input);
            stringContainer = ChainedHash_Search(
                T, string_keyWrapper, String_keyWrappersEqual, String_keyWrapperToInt
            );
            
            if (stringContainer) String_ContainerPrint(stringContainer);
            else printf("%s not found", input);
            printf("\n");

            String_keyWrapperDelete(string_keyWrapper);
            break;
        
        case 'p':  // print
            printf("\n");
            ChainedHash_PrintTable(T, String_ContainerPrint);
            printf("\n");
            break;
        
        case 'c':  // clear
            printf("Table cleared\n");
            ChainedHash_ClearTable(T, String_ContainerDelete, String_keyWrappersEqual);
            break;
        
        case '\0':
            break;

        default:
            printf("Command not recognised\n");
            break;
    }
    
    ChainedHash_DeleteTable(T, String_ContainerDelete, String_keyWrappersEqual);
    free(input);

    #else

    int a, b;
    double c;
    void* someRandom_keyWrapper;
    Generic_KeyDataContainer someRandomContainer;

    ChainedHash_Table T = ChainedHash_CreateTable(10, ULONG_MAX);

    showCommands();
    char command;
    while ((command = commandPrompt()) != 'e') switch (command) {
        case 'h':  // commands
            showCommands();
            break;

        case 'i':  // insert
            printf("Give a b c to insert: ");
            scanf("%d %d %lf%*c", &a, &b, &c);
            someRandomContainer = SomeRandom_ContainerCreate(a, b, c);

            if (ChainedHash_Insert(
                T, someRandomContainer, SomeRandom_keyWrappersEqual, SomeRandom_keyWrapperToInt)
            ) {
                SomeRandom_ContainerPrint(someRandomContainer);
                printf(" inserted\n");
            } else {
                printf("Pair %d %d already exists\n", a, b);
                SomeRandom_ContainerDelete(someRandomContainer);
            }
            break;
        
        case 'd':  // delete
            printf("Give pair 'a b' to delete: ");
            scanf("%d %d%*c", &a, &b);
            someRandom_keyWrapper = SomeRandom_keyWrapperCreate(a, b);
            someRandomContainer = ChainedHash_Delete(
                T, someRandom_keyWrapper, SomeRandom_keyWrappersEqual, SomeRandom_keyWrapperToInt
            );

            if (someRandomContainer) {
                SomeRandom_ContainerPrint(someRandomContainer);
                printf(" deleted\n");
                SomeRandom_ContainerDelete(someRandomContainer);
            }
            else printf("Pair %d %d not found\n", a, b);

            SomeRandom_keyWrapperDelete(someRandom_keyWrapper);
            break;
        
        case 's':  // search
            printf("Give pair 'a b' to search: ");
            scanf("%d %d%*c", &a, &b);
            someRandom_keyWrapper = SomeRandom_keyWrapperCreate(a, b);
            someRandomContainer = ChainedHash_Search(
                T, someRandom_keyWrapper, SomeRandom_keyWrappersEqual, SomeRandom_keyWrapperToInt
            );

            if (someRandomContainer) SomeRandom_ContainerPrint(someRandomContainer);
            else printf("Pair %d %d not found", a, b);
            printf("\n");

            SomeRandom_keyWrapperDelete(someRandom_keyWrapper);
            break;
        
        case 'p':  // print
            printf("\n");
            ChainedHash_PrintTable(T, SomeRandom_ContainerPrint);
            printf("\n");
            break;
        
        case 'c':  // clear
            printf("Table cleared\n");
            ChainedHash_ClearTable(T, SomeRandom_ContainerDelete, SomeRandom_keyWrappersEqual);
            break;
        
        case '\0':
            break;

        default:
            printf("Command not recognised\n");
            break;
    }
    
    ChainedHash_DeleteTable(T, SomeRandom_ContainerDelete, SomeRandom_keyWrappersEqual);
    
    #endif

    printf("\nExitting...\n");
    return 0;
}