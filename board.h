//struct to hold each item 
typedef struct Item {
    char itemName[50];
    struct Item *next;
}Item;


//struct skeleton for a board
typedef struct Board{
    char boardName[50];
    struct Board* prev;
    struct Board* next;
    struct Item *firstItem;
} Board;


//display the board
void displayBoards(Board*header);
// load the board
void loadBoard(Board **header, char FILENAME[80]);
//get user input to edit list
void edit_list_user_input(Board**header);
//get user input to edit board
void edit_board_user_input(Board**header);
// save board
void saveBoard(Board *header, char FILENAME[80]);
//test data
void testData(Board**header);
//add item to list
void addItem(Item **firstItem, char newItem[80]);
//edit item
void editItem(Item **firstItem, char itemName[80], char newName[80]);
//delete item
void deleteItem(Item **firstItem, char itemName[80]);
//add board to list
void addBoard(Board **header, char newBoard[80]);
// edit the board
void editBoard(Board **header, char boardName[80], char newBoardName[80]);
//delete board
void deleteBoard(Board **header, char boardName[80]);
//display Boardmenu for user
void listMenu(); 
//display main menu for user 
void mainMenu();
//board menu
void boardMenu();

void addBoardEnd(Board **header, char boardName[80]);

void addItemEnd(Item **firstItem, char newItem[80]);

void freeMemory(Board **header);

void ASCIIart();
