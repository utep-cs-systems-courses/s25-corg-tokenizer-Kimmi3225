#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "bst.h"
#include "tokenizer.h"
#include "history.h"

// Function to compare strings (used for "STOP" check)
int areEqual(const char *str1, const char *str2) {
    while (*str1 != '\0' && *str2 != '\0') {
        if (*str1 != *str2)
            return 0; // Not equal
        str1++;
        str2++;
    }
    return (*str1 == '\0' && *str2 == '\0'); // Equal if both strings ended
}

void remove_newline(char *str) {
    str[strcspn(str, "\n")] = 0; 
}

int main(void) {
    int looping = 1;
    char userInput[100];
    List *history = init_history();  // Initialize history list
    printf("Welcome to TOKENIZER\n");
    bstRoot = NULL;

    while (looping == 1) {
        printf("What would you like to do?\n1. Tokenize a String\n2. View History\nEnter 1, 2 or STOP to exit: ");
        fgets(userInput, sizeof(userInput), stdin);
        remove_newline(userInput); 
    // Will check if the user enters 1 then the code will Tokenize a String 
        if (areEqual(userInput, "1")) {
            printf("Enter a string (type 'STOP' to exit): ");
            fgets(userInput, sizeof(userInput), stdin);
            remove_newline(userInput);  // Remove the newline character
            printf("You entered: %s\n", userInput);

            // Tokenize the user input and insert each token into the BST
            char **tokens = tokenize(userInput);
            for (int i = 0; tokens[i] != NULL; i++) {
                bstInsert(&bstRoot, tokens[i]); // Insert each token into the global BST
            }

            // Add to history
            add_history(history, userInput);

            // Print sorted tokens from the BST
            printf("Sorted tokens:\n");
            bstPrint(bstRoot); // Print the BST contents

            // Clear the BST for the next input
            bstClear(&bstRoot); // Reset the BST for the next loop
        }
        // Else if the user enters 2 then the code with show the history and user can tokenize strings fron the history 
        else if (areEqual(userInput, "2")) {
            printf("History:\n");
            print_history(history); // Print the entire history

            printf("What string would you like to tokenize? Enter the ID: ");
            fgets(userInput, sizeof(userInput), stdin);
            remove_newline(userInput);  // Remove the newline character

            int historyId = atoi(userInput);  // Convert input to integer (ID)
            char *historyString = get_history(history, historyId);

            if (historyString != NULL) {
                printf("You selected: %s\n", historyString);

                // Tokenize the string from history
                char **tokens = tokenize(historyString);
                printf("Tokens from history:\n");
                for (int i = 0; tokens[i] != NULL; i++) {
                    printf("%s\n", tokens[i]); // Print each token
                }
            } else {
                printf("Invalid history ID.\n");
            }
        }

        else if (areEqual(userInput, "STOP") == 1) {
            printf("Thank you for using Tokenizer\n");
            looping = 0; // Exit the loop
        }
    }

    free_history(history);  // Free the history memory
    return 0;
}
