
/* main.c */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ChainedHashTable.h"
#include "StringWrapper.h"
#include "ConfusingWrapper.h"

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
    strcpy(str, string);

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

    strcpy(string, str);
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

    #if 1  // toggle to switch between 'String' and 'Confusing' data type

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
    void* confusing_keyWrapper;
    Generic_KeyDataContainer confusingContainer;

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
            confusingContainer = Confusing_ContainerCreate(a, b, c);

            if (ChainedHash_Insert(
                T, confusingContainer, Confusing_keyWrappersEqual, Confusing_keyWrapperToInt)
            ) {
                Confusing_ContainerPrint(confusingContainer);
                printf(" inserted\n");
            } else {
                printf("Key %d already exists\n", a);
                Confusing_ContainerDelete(confusingContainer);
            }
            break;
        
        case 'd':  // delete
            printf("Give key 'a' to delete: ");
            scanf("%d%*c", &a);
            confusing_keyWrapper = Confusing_keyWrapperCreate(a);
            confusingContainer = ChainedHash_Delete(
                T, confusing_keyWrapper, Confusing_keyWrappersEqual, Confusing_keyWrapperToInt
            );

            if (confusingContainer) {
                Confusing_ContainerPrint(confusingContainer);
                printf(" deleted\n");
                Confusing_ContainerDelete(confusingContainer);
            }
            else printf("Key %d not found\n", a);

            Confusing_keyWrapperDelete(confusing_keyWrapper);
            break;
        
        case 's':  // search
            printf("Give a to search: ");
            scanf("%d%*c", &a);
            confusing_keyWrapper = Confusing_keyWrapperCreate(a);
            confusingContainer = ChainedHash_Search(
                T, confusing_keyWrapper, Confusing_keyWrappersEqual, Confusing_keyWrapperToInt
            );

            if (confusingContainer) Confusing_ContainerPrint(confusingContainer);
            else printf("Key %d not found", a);
            printf("\n");

            Confusing_keyWrapperDelete(confusing_keyWrapper);
            break;
        
        case 'p':  // print
            printf("\n");
            ChainedHash_PrintTable(T, Confusing_ContainerPrint);
            printf("\n");
            break;
        
        case 'c':  // clear
            printf("Table cleared\n");
            ChainedHash_ClearTable(T, Confusing_ContainerDelete, Confusing_keyWrappersEqual);
            break;
        
        case '\0':
            break;

        default:
            printf("Command not recognised\n");
            break;
    }
    
    ChainedHash_DeleteTable(T, Confusing_ContainerDelete, Confusing_keyWrappersEqual);
    
    #endif

    printf("\nExitting...\n");
    return 0;
}