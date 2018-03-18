/**
* A testing program that reads from a
* text file and prints to an Ncurses
* screen.
*      Written By: Christopher Foytek
**/
#include <stdio.h>
#include <ncurses.h>

void read_file_by_line(FILE *);

int main(int argc, char **argv) {
    const char *file_name = "foo.txt";
    char line[255];
    FILE *inFile;
    inFile = fopen(file_name, "r"); //Causes segmentation fault
    if(inFile == NULL) {
        exit(1);
    }

    //Initialize Curses mode
    initscr();
    noecho();
    cbreak();
    int x = 0;  //x coord
    int y = 0;  //y coord
    move(y, x); //Move to top left corner of screen
    while(fgets(line, sizeof(line), inFile) != NULL) {
        printw("%s", line); //Print line read to ncurses screen
        refresh();
    }
    attron(A_BOLD);
    printw("\n\nPress any key to continue...");
    getch();    //Wait for character input before exiting
    attroff(A_BOLD);
    endwin();
    return 0;
}