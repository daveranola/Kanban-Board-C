#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "board.h"

// ============================================= LIST FUNCTIONS ============================================================

void edit_list_user_input(Board **header) {
    char inputName[80];
    //current pointer, which points at the item it is at
    Board *current = *header;

    //gets user input
    printf("\nEnter the name of the list to edit: ");
    fgets(inputName, 80, stdin);
    //replaces the last charachter, '\n' with null terminator '\0'
    inputName[strlen(inputName)-1] = '\0';
    //find the node which has the same name as input name
    while (current != NULL && strcmp(current->boardName, inputName) != 0) {
        current = current->next;    
    }

    //if current == NULL, means there is no name with input name
    if (current == NULL) {
        printf("\nCan't find list");
        return;
    } 


    char itemName[80], newName[80], newItem[80];

    while (1) {
        int choice;
        
        //display the menu for the user to choose from
        listMenu();

        //scans the users input
        if (scanf("%d", &choice) != 1) {
            //invalid input (not an integer)
            printf("\nPlease enter a number from 1-4!\n");
            
            //clear the input buffer
            while(getchar() != '\n');
            
            //skip the rest of this iteration
            continue; 
        }

        //clears the input buffer
        while(getchar() != '\n');

        //switch statement for the user's choice
        switch (choice)
        {
        case 1:
            //gets user input
            printf("\nEnter the name of the item to edit: ");
            fgets(itemName, 80, stdin);
            //replaces the last charachter, '\n' with null terminator '\0'
            itemName[strlen(itemName) - 1] = '\0';

            //gets user input
            printf("\nEnter new name for %s: ", itemName);
            fgets(newName, 80, stdin);
            //replaces the last charachter, '\n' with null terminator '\0'
            newName[strlen(newName) - 1] = '\0';

            //edit the item, replaces the old name of the list with the new name
            editItem(&(current->firstItem), itemName, newName);
            break;
        case 2:
            //gets user input
            printf("\nEnter the name of the new item: ");
            fgets(newItem, 80, stdin);
            //replaces the last charachter, '\n' with null terminator '\0'
            newItem[strlen(newItem)-1] = '\0';

            //add item to the beginning of the list
            addItem(&(current->firstItem), newItem);
            break;
        case 3:
            //gets user input
            printf("\nEnter the name of the item to delete: ");
            fgets(itemName, 80, stdin);
            //replaces the last charachter, '\n' with null terminator '\0'
            itemName[strlen(itemName) - 1] = '\0';

            //deletes the item with the name provided by the user
            deleteItem(&(current->firstItem),itemName);
            break;
        case 4:
            return;
        default:
            printf("\nEnter a choice from 1-4 ! ! !");
            break;
        }
    }    
}

void addItem(Item **firstItem, char newItem[80]) {
    //allocates memory for the new item to be added
    Item *new = malloc(sizeof(Item));
    //copies the name provied from the user, to the itemName 
    strcpy(new->itemName, newItem);
    //points the new->next to the first item, as it will be the new head
    new->next = (*firstItem);
    //update that the new head, is the new item
    *firstItem = new;
}

void addItemEnd(Item **firstItem, char newItem[80]) {
    //if the item is to be added to an empty list, use the addItem funciton will add the
    //the item to the front
    if ((*firstItem) == NULL) {
        addItem(firstItem, newItem);
    } else {
        //allocate memory for new item
        Item *new = malloc(sizeof(Item));
        //copy the user input name, to the new->itemName
        strcpy(new->itemName, newItem);
        //the item will be added to the end of the list, so it should point to NULL
        //indicating is is the end of the list
        new->next = NULL;

        //current item points to the firstItem in the list
        Item *current = *firstItem;

        //while loop will point current to the end of the list
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new;
    }
}

void editItem(Item **firstItem, char itemName[80], char newName[80]) {
    Item *current = *firstItem;

    //finds the item with the name 'itemName'
    while (current != NULL && strcmp(current->itemName, itemName) != 0) {
        current = current->next;
    }

    //if current reaches NULL, is indicates that item does not exist
    if (current == NULL) {
        printf("Item not found!");
        return;
    }

    //copt the newName to the old itemName
    strcpy(current->itemName, newName);
}

void deleteItem(Item **firstItem, char itemName[80]) {
    //current pointer
    Item *curr = (*firstItem)->next;
    //previous pointer
    Item *prev = *firstItem;

    //special case, if the item to be deleted is at the head
    if (strcmp((*firstItem)->itemName, itemName) == 0) {
        //make a temp pointer which points at the item to be deleted
        Item *deleteItem = *firstItem;
        //the first item should now point to the item after
        *firstItem = (*firstItem)->next;
        //free the deleted item
        free(deleteItem);
        return;
    }

    //finds the first occurence of the node with the corresponding 'itemName'
    while (curr != NULL && strcmp(curr->itemName, itemName) != 0) {
        prev = curr;
        curr = curr->next;
    }

    //if curr points at NULL, it means it reachs the end of the list without finding a matching 'itemName' -> item is not in the list
    if (curr == NULL) {
        printf("Item not found!");
        return;
    } else {
        //make a temp pointer which is the item to be deleted
        Item *deleteNode = curr;
        //point the previous pointer to the next item
        prev->next = deleteNode->next;
        //free the node
        free(deleteNode);
    }

}


// ===================================================== BOARD FUNCTIONS ====================================================

void displayBoards(Board *header) {
    //clears the board for every new board
    system("clear");

    //current list, is the current board it is at
    Board *currentList = header;

    while (currentList != NULL) {
        //print the board Name
        printf("%s\n", currentList->boardName);
        
        //the currentItem first points at the firstItem of the board
        Item *currentItem = currentList->firstItem;

        //prints out all the items of the board
        while (currentItem != NULL) {
            printf("\t%s\n", currentItem->itemName);
            currentItem = currentItem->next;
        }
        currentList = currentList->next;
    }
}

void edit_board_user_input(Board **header) {
    char newBoardName[80], boardName[80];

    while (1) {
        //displays the options for the user to choose from
        boardMenu();

        //holds the choice user selects
        int choice;
        
        //scans the users input
        if (scanf("%d", &choice) != 1) {
            //invalid input (not an integer)
            printf("\nPlease enter a number from 1-6!\n");
            
            //clear the input buffer
            while(getchar() != '\n');
            
            //skip the rest of this iteration
            continue; 
        }

        //clears the input buffer
        while(getchar() != '\n');

        //switch statement for the user's choice
        switch (choice)
        {
        case 1:
            //get user input
            printf("\nEnter the name if the list to edit: ");
            fgets(boardName, 80, stdin);
            //replaces the last charachter, '\n' with null terminator '\0'
            boardName[strlen(boardName) - 1] = '\0';

            //get user input
            printf("\nEnter new name for list %s: ", boardName);
            fgets(newBoardName, 80, stdin);
            //replaces the last charachter, '\n' with null terminator '\0'
            newBoardName[strlen(newBoardName) - 1] = '\0';

            //edits the board, with the given name by the user
            editBoard(header, boardName, newBoardName);
            break;
        case 2:
            //get user input
            printf("\nEnter the name of the new list: ");
            fgets(newBoardName, 80, stdin);
            //replaces the last charachter, '\n' with null terminator '\0'
            newBoardName[strlen(newBoardName)-1] = '\0';
            
            //adds a board to the begginining of the list
            addBoard(header, newBoardName);
            break;
        case 3:
            //get user input
            printf("\nEnter the name of the list to delete: ");
            fgets(boardName, 80, stdin);
            //replaces the last charachter, '\n' with null terminator '\0'
            boardName[strlen(boardName) - 1] = '\0';

            //deletes the board with the matching name provided by the user
            deleteBoard(header, boardName);
            break;
        case 4:
            return;
        default:
            printf("\nEnter a choice from 1-4 ! ! !");
            break;
        }
    }
}

void addBoard(Board **header, char boardName[80]) {
    //allocate memory for a new board
    Board *new = malloc(sizeof(Board));

    //copy the boardName provided by the user to the new board
    strcpy(new->boardName, boardName);
    //sets the firstItem to be NULL, as there are no items yet
    new->firstItem = NULL;
    //the next ptr should now point to the head, as it is the new head
    new->next = *header;    
    //no prev, as it is the new head
    new->prev = NULL; 

    //if the list is empty, set the the header as the new board
    if ((*header) == NULL) {
        *header = new;
    } else {
        //if its not empty, set the old header prev pointer to the new board
        (*header)->prev = new;
        //set the new head as new
        *header = new;
    }
}

void addBoardEnd(Board **header, char boardName[80]) {
    //if the header is NULL (empty list)
    // add a board to the begininng of the list with the addBoard function
    if ((*header) == NULL) {
        addBoard(header, boardName);
    } else {
        //allocate memory for a new board
        Board *new = malloc(sizeof(Board));

        //copy the boardName provided by the user to the new board
        strcpy(new->boardName, boardName);
        //sets the firstItem to be NULL, as there are no items yet
        new->firstItem = NULL;
        //the next ptr should now point to the head, as it is the new head
        new->next = NULL;

        //a pointer which keeps track of where they are at the list
        Board *current = *header;

        //keeps traversing list until it reachees the end of the list (last board)
        while (current->next != NULL) {
            current = current->next;
        }

        //the current->next should now point at the new board
        current->next = new;
        //the new->prev should point at the current board
        new->prev = current;
    }
}

void editBoard(Board **header, char boardName[80], char newBoardName[80]) {
    Board *current = *header;

    //finds the board with the same 'boardName' provided by the user
    while (current != NULL && strcmp(current->boardName, boardName) != 0) {
        current = current->next;
    }

    //if current reaches NULL, it means that the item does not exist
    if (current == NULL) {
        printf("\nBoard could not be found!");
        return;
    } else {
        //copy the newBoardName to the old boardName
        strcpy(current->boardName, newBoardName);
    }
}

void deleteBoard(Board **header, char boardName[80]) {
    Board *current = *header;

    //special case, if the head is the board to be deleted
    if (strcmp(boardName, (*header)->boardName) == 0) {
        //point the header to the next item
        (*header) = (*header)->next;
        //set the rrev as NULL, as there should be no item before it, (new head)
        if ((*header) != NULL) {
            (*header)->prev = NULL;
        }
        

        //pointer to the firstItem of the board
        Item *firstItem = current->firstItem;

        while (firstItem != NULL) {
            //temp pointer which points at the item to be deleted
            Item *deleteTempItem = firstItem;
            //traverse the firstItem to the next item
            firstItem = firstItem->next;
            //free the item to be deleted
            free(deleteTempItem);
        }

        //free current, which is the node before the new head
        free(current);

        return;
    }

    while (current != NULL && strcmp(boardName, current->boardName) != 0) {
        current = current->next;
    }

    if (current == NULL) {
        printf("Board not found!");
        return;
    }

    

    //pointer to the firstItem of the board
    Item *firstItem = current->firstItem;

    while (firstItem != NULL) {
        //temp pointer which points at the item to be deleted
        Item *deleteTempItem = firstItem;
        //traverse the firstItem to the next item
        firstItem = firstItem->next;
        //free the item to be deleted
        free(deleteTempItem);
    }

    // the current->prev (the item before) should now point to the next to the current->next (the item after current)
    // the current->next (the item after) prev pointer should now point to the current->prev (the item before current) 
    if (current->prev != NULL) {
        current->prev->next = current->next;
    }
    if (current->next != NULL) {
        current->next->prev = current->prev;
    }


    //free the current board, which is the board to be deleted
    free(current);
}

// ====================================================== MENUS ===============================================================

void listMenu() {
    printf("\nOptions:");
    printf("\n1. Edit an item");
    printf("\n2. Add a new item");
    printf("\n3. Delete an item");
    printf("\n4. Return to main menu");
    printf("\nEnter your option: ");
}

void mainMenu() {
    printf("\nMenu\n");
    printf("1. Display board\n");
    printf("2. Load board from a file\n");
    printf("3. Edit list\n");
    printf("4. Edit Board \n");
    printf("5. Save board to a file\n");
    printf("6. Quit\n");
}

void boardMenu() {
    printf("\nOptions:");
    printf("\n1. Edit the name of the list");
    printf("\n2. Add a new list");
    printf("\n3. Delete a list");
    printf("\n4. Return to main menu");
    printf("\nEnter your option: ");
}

// ==================================================== LOAD / SAVE FUNCITONS =====================================================
void saveBoard(Board *header, char FILENAME[80]) {
    //file ptr to the file to be manipulated
    FILE *fptr;

    //open the file, error handling, if NULL it implies error
    if ((fptr = fopen(FILENAME, "wb")) == NULL) {
        printf("\nError opening file!");
        return;
    } else {
        int boardCount = 0;

        //find how many board there are
        Board *current = header;
        //goes through every board and keeps track of how many board there are
        while (current != NULL) {
            boardCount++;
            current = current->next;
        }

        //save how many number of boards there are
        //writes it into the file
        fwrite(&boardCount, sizeof(int), 1, fptr);

        //reset the current pointer to the beginning of the list again'
        //after the boardcount loop, the current pointer will point at the last item
        current = header;


        while (current != NULL) {
            int itemCount = 0;
            //save the board name
            fwrite(current->boardName, sizeof(char), 80, fptr);

            //pointer to the first item of the current board
            Item *currentItem = current->firstItem;

            //find how many items board 'x' has 
            while (currentItem != NULL) {
                itemCount++;
                currentItem = currentItem->next;
            }

            //write how may items there are in the board into the file
            fwrite(&itemCount, sizeof(int), 1, fptr);

            //reset the currentItem to the firstItem again, as after finding how many items the board has
            //will point at the last item of the board
            currentItem = current->firstItem;

            //writes all the itemNames of the given board
            while (currentItem != NULL) {
                fwrite(currentItem->itemName, sizeof(char), 80, fptr);
                currentItem = currentItem->next;
            }

            //traverse the current pointer to the next board
            current = current->next;
        }
        fclose(fptr);
    }
}

void loadBoard(Board **header, char FILENAME[80]) {
    FILE *fptr;

    //open the file, error handling, if NULL it implies error
    if ((fptr = fopen(FILENAME, "rb")) == NULL) {
        printf("\nError: could not open file %s", FILENAME);
    } else {
        *header = NULL;
        int boardCount, itemCount;
        //read the board count
        fread(&boardCount, sizeof(int), 1, fptr);

        //go through all the boards
        for (int i = 0; i < boardCount; i++) {
            char boardName[80], itemName[80];
            //get board name
            fread(boardName, sizeof(char), 80, fptr);
            //add board, add at the end to keep correct format
            addBoardEnd(header, boardName);

            //find how many items the board is holding
            fread(&itemCount, sizeof(int), 1, fptr);

            for (int i = 0; i < itemCount; i++) {
                //read the itemName from the file
                fread(itemName, sizeof(char), 80, fptr);

                //current pointer to keep track of where we are in the list
                Board *current = *header;
                
                //go through all the boards until the last one, add items to the last board
                while (current->next != NULL) {
                    current = current->next;
                }
                addItemEnd(&(current->firstItem), itemName);
                
            }
        }
        fclose(fptr);   
    }
}
// ====================================================== TEST DATA ===========================================================

void testData(Board **header) {
    //List **header because we want to change the address of the pointer, to where the new head would be.
    //In this case the new address of the head would be board4.
    //If it wasnt a double pointer, we couldnt modify the address of the pointer.
    // Create board1 (Abey)
    Board* board1 = malloc(sizeof(Board));
    strcpy(board1->boardName, "Abey:");
    board1->next = NULL;

    Item* item1_1 = malloc(sizeof(Item));
    strcpy(item1_1->itemName, "Oculus Pro");
    Item* item1_2 = malloc(sizeof(Item));
    strcpy(item1_2->itemName, "Oculus Quest 1");

    item1_2->next = NULL;
    board1->firstItem = item1_1;
    item1_1->next = item1_2;

    // Create board2 (Dante)
    Board* board2 = malloc(sizeof(Board));
    strcpy(board2->boardName, "Dante:");
    board2->next = board1;
    
    Item* item2_1 = malloc(sizeof(Item));
    strcpy(item2_1->itemName, "Oculus Quest 1");
    item2_1->next = NULL;
    Item* item2_2 = malloc(sizeof(Item));
    strcpy(item2_2->itemName, "3070 RTX");
    item2_2->next = NULL;
    
    board2->firstItem = item2_1;
    item2_1->next = item2_2;

    // Create board3 (Tim)
    Board* board3 = malloc(sizeof(Board));
    strcpy(board3->boardName, "Tim:");
    board3->next = board2;

    Item* item3_1 = malloc(sizeof(Item));
    strcpy(item3_1->itemName, "Oculus Quest 2");
    board3->firstItem = item3_1;
    item3_1->next = NULL;

    // Create board4 (Nick)
    Board* board4 = malloc(sizeof(Board));
    strcpy(board4->boardName, "Nick:");
    Item* item4_1 = malloc(sizeof(Item));
    strcpy(item4_1->itemName, "3070 RTX");
    item4_1->next = NULL;
    board4->firstItem = item4_1;
    board4->next = board3;

    // Set up prev pointers
    board1->prev = board2;
    board2->prev = board3;
    board3->prev = board4;
    board4->prev = NULL;

    *header = board4;
}

// ================================================ FREE MEMORY ===============================================================

void freeMemory(Board **header) {
    //goes through every board
    while (*header != NULL) {
        //temp pointer to the board to be deleted
        Board *deleteTempBoard = *header;
        //the header should now point to the next item
        *header = (*header)->next;

        //
        Item *firstItem = deleteTempBoard->firstItem;
        while (firstItem != NULL) {
            Item *deleteTempItem = firstItem;
            firstItem = firstItem->next;
            free(deleteTempItem);
        }
        free(deleteTempBoard);
    }
}

// ========================================================= ASCII Art ===========================================================
void ASCIIart() {
    printf(" _   __  ___   _   _ ______  ___   _   _  ______  _____  ___  ____________ \n");
    printf("| | / / / _ \\ | \\ | || ___ \\/ _ \\ | \\ | | | ___ \\|  _  |/ _ \\ | ___ \\  _  \\\n");
    printf("| |/ / / /_\\ \\|  \\| || |_/ / /_\\ \\|  \\| | | |_/ /| | | / /_\\ \\| |_/ / | | |\n");
    printf("|    \\ |  _  || . ` || ___ \\  _  || . ` | | ___ \\| | | |  _  ||    /| | | |\n");
    printf("| |\\  \\| | | || |\\  || |_/ / | | || |\\  | | |_/ /\\ \\_/ / | | || |\\ \\| |/ / \n");
    printf("\\_| \\_/\\_| |_/\\_| \\_/\\____/\\_| |_/\\_| \\_/ \\____/  \\___/\\_| |_/\\_| \\_|___/  \n");
}