---

# Assignment 3 - Dave Ranola, Ewa Zoladek

---

## How to Compile the Program

To compile the program, use the following command in your terminal:

```bash
gcc -o kanban main.c board.c
```

**Explanation:**

* `gcc` — GNU Compiler Collection
* `-o kanban` — output executable named `kanban`
* `main.c board.c` — source files for the project

Run the compiled program with:

```bash
./kanban
```

> Make sure all source files (`main.c`, `board.c`) are in the same directory when compiling.

---

## How to Load a Board?

In our project, we decided to load a board from a binary file (`.dat`).

### Function Used

```c
void loadBoard(Board **header, char FILENAME[80])
```

**Parameters:**

* `Board** header` – the head of the linked list, double pointer because it needs to be edited
* `char FILENAME[80]` – the name of the file to load data from

**How it works:**

* Opens the file with `fopen(FILENAME, "rb")` (`rb` since it's a binary file, reading mode)

* If the file pointer is `NULL`, it indicates an error opening the file.

* Reads the first integer from the file, which is the board count, using:

  ```c
  fread(&boardCount, sizeof(int), 1, fptr);
  ```

* Then repeatedly reads the board name (`boardName`), item count (`itemCount`), and item names until no data is left:

  * Reads board name with:

    ```c
    fread(boardName, sizeof(char), 80, fptr);
    ```

  * Adds this board to the end of the list using:

    ```c
    addBoardEnd(header, boardName);
    ```

  * Reads item count and item names, adding them to the board's item list using:

    ```c
    addItem(&((*header)->firstItem), itemName); // if list is empty
    addItemEnd(&(current->firstItem), itemName); // if items exist
    ```

* Finally, closes the file with `fclose(fptr);`.

---

## How to Edit Lists and Items

### Edit Boards

```c
void editBoard(Board **header, char boardName[80], char newBoardName[80])
```

**Parameters:**

* `Board** header` – head of the linked list, double pointer because it needs to be edited
* `char boardName[80]` – the current name of the board to be edited
* `char newBoardName[80]` – the new name to replace the old one

**How it works:**

* Uses a pointer `Board *current = *header;` to traverse the list.
* Loops through until the board with `boardName` is found or until reaching `NULL`.
* If no matching board is found, returns without changes.
* If found, copies the new name over the old one:

  ```c
  strcpy(current->boardName, newBoardName);
  ```

---

### Edit Items

```c
void editItem(Item **firstItem, char itemName[80], char newName[80])
```

**Parameters:**

* `Item **firstItem` – head of the linked list, double pointer to be edited
* `char itemName[80]` – current name of the item to edit
* `char newName[80]` – new name to replace the old one

**How it works:**

* Uses `Item *current = *firstItem;` to traverse the item list.
* Loops until it finds an item matching `itemName` or reaches `NULL`.
* Returns if no matching item is found.
* If found, copies the new name:

  ```c
  strcpy(current->itemName, newName);
  ```

---

## How to Save a Board

```c
void saveBoard(Board *header, char FILENAME[80])
```

**Parameters:**

* `Board *header` – head of the linked list, single pointer since it is not modified
* `char FILENAME[80]` – name of the file to save data to

**How it works:**

* Opens the file with:

  ```c
  fopen(FILENAME, "wb");
  ```

  (`wb` for binary write mode).

* If `NULL`, indicates an error opening the file.

* Initializes a pointer to traverse the board list:

  ```c
  Board *current = header;
  ```

* Counts total boards and writes this count:

  ```c
  fwrite(&boardCount, sizeof(int), 1, fptr);
  ```

* For each board:

  * Writes the board name:

    ```c
    fwrite(current->boardName, sizeof(char), 80, fptr);
    ```

  * Counts and writes how many items the board has:

    ```c
    fwrite(&itemCount, sizeof(int), 1, fptr);
    ```

  * Writes all item names in a loop:

    ```c
    while (currentItem != NULL) {
      fwrite(currentItem->itemName, sizeof(char), 80, fptr);
      currentItem = currentItem->next;
    }
    ```

  * Moves to the next board until the list ends.

* Closes the file with `fclose(fptr);`.

---

## Format of the Binary File

The binary file format stores:

* An integer board count
* For each board:

  * Board name (fixed size 80 chars)
  * Integer item count
  * Item names (each fixed size 80 chars)

---

## What ASCII Art is About

The ASCII art informs the user that they are about to use a Kanban board-like program.

---

## Git Repository

[https://csgitlab.ucd.ie/DaveRanola/comp10050-assignment-3.git](https://csgitlab.ucd.ie/DaveRanola/comp10050-assignment-3.git)
**Project:** “2025 Assignment 3 AA” + “Assignment 3”

---


