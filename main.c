#include <stdio.h>
#include <string.h>
#include "board.h"

int main() {
    int choice;
    char FILENAME[80];

    Board *header = NULL;
    // testData(&header);

    ASCIIart();

    while (1) {
        mainMenu();
        printf("Enter your choice (1-6): ");
        if (scanf("%d", &choice) != 1) {
            //invalid input (not an integer)
            printf("\nPlease enter a number from 1-6!\n");
            
            //clear the input buffer
            while(getchar() != '\n');
            
            //skip the rest of this iteration
            continue; 
        }

        while(getchar() != '\n');
    
        switch (choice) {
            case 1:                
                displayBoards(header);
                break;  
            case 2:
                //get user input
                printf("\nEnter filename: ");
                fgets(FILENAME, 80, stdin);
                FILENAME[strlen(FILENAME)-1] = '\0';
                
                loadBoard(&header, FILENAME);

                break;
            case 3:
                edit_list_user_input(&header);
                break;
            case 4:
                edit_board_user_input(&header);
                break;
            case 5:
                //get user input
                printf("\nEnter filename: ");
                fgets(FILENAME, 80, stdin);
                FILENAME[strlen(FILENAME)-1] = '\0';

                saveBoard(header, FILENAME);

                // while(getchar() != '\n');

                break;
            case 6:
            freeMemory(&header);
            printf("Exiting...\n");
            return 0;
            default:
                printf("\nEnter a number from 1 - 6 ! ! !");
                break;
        }
    }
    return 0;
}