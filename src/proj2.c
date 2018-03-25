#include "file_handler.h"
#include "edit_buffer.h"
#include "globals.h"
#include <ncurses.h>

void print_coords(WINDOW *, int, int);
void refresh_text(WINDOW *win, int startline, int endline, char** file_buf);

WINDOW *create_newwin(int height, int width, int starty, int startx)
{
  WINDOW *local_win = newwin(height, width, starty, startx);
  //box(local_win, 0, 0);
  wrefresh(local_win);

  return (local_win);
}

int main(int argc, char **argv) {	
  int linecount = 0;
  char ** file_buf;
  char *filename;
  if(argc != 2) {
    //Don't read file, initialize with empty buffer.
  }
  else {
    filename = argv[1];
    //Read file to buffer
    file_buf = read_file(filename, &linecount);
  }
	int ch;
	enum modes {COMMAND = 0, INSERT = 1}; //0 = Command, 1 = Insert
  int mode = COMMAND;
	WINDOW *e_win; //Editor window
  WINDOW *stat_win;
	int x = 0;
  int y = 0;
  int maxx;
  int maxy;
  
	

	initscr();			/* Start curses mode */
	//cbreak();			/* Enable character at a time buffering */
	raw();				/* Line buffering disabled */
	keypad(stdscr, TRUE);		/* We get F1, F2 etc.. */
	noecho();			/* Don't echo() while we do getch */

	getmaxyx(stdscr, maxy, maxx); //Get maximum dimensions for terminal
	//Set boundaries for editor window
	int xbound = maxx - 1; //Set editor width to max width - 1
	int ybound = maxy - 4; //Set editor height to max height - 5
  //Set boundaries for file buffer
  buf_ystart = 0;
  buf_yend = ybound - 1;
	e_win = create_newwin(ybound, xbound, y, x);
  line = 0;
  update_line_size(file_buf);
  
  move(ybound + 1, 0);
  printw("MODE:%d Buffer Line: %d Buffer Col: %d LN SIZE: %d", mode, line, x_pos, line_size);
	refresh();
	scrollok(e_win, TRUE);
  idlok(e_win, TRUE);
	wmove(e_win, y, x);
	wrefresh(e_win);

	getbegyx(e_win, y, x);
	print_coords(e_win, x, y);
  refresh_text(e_win, buf_ystart, buf_yend, file_buf);
  wmove(e_win, y, x);
  wrefresh(e_win);
	while(true) {
    ch = getch();
    update_line_size(file_buf);
    switch(mode){
      case COMMAND:
        switch (ch) {
          case 'w':
            write_file(filename,file_buf, linecount);
            break;
          case 'd':
            file_buf = delete_line_at_cursor(file_buf);
            x_pos = 0;
            x = 0;
            break;
          case 'n':
            file_buf = insert_line_after_current_line(&linecount,file_buf);
            y++;
            x_pos = 0;
            x = 0;
          //insert new line after current line
            break;
          case 'y':
          //copy edit_buffer
            break;
          case 'p':
          //paste from buffer
            break;
          case '?':
          //search for string
            break;
          case 'q':
            endwin();
            exit(0);
          case 'i':
            mode = INSERT;
            break;
          case KEY_LEFT:
            if(x > 0) {
              x_pos--;
              x--;
            }
            else
              beep();
            break;
          case KEY_RIGHT:
            if(x < xbound - 1 && x_pos < line_size - 1) {
              x_pos++;
              x++;
            }
            else
              beep();
            break;
          case KEY_UP:
            if(y > 0) {
              advance_cursor_line(-1);
              y--;
            }
            else if((y == 0) && (buf_ystart > 0)) {
              advance_cursor_line(-1);
              buf_yend--;
              buf_ystart--;
              scrl(-1);
            }
            else
              beep();
            break;
          case KEY_DOWN:
            if(y < ybound - 2) {
              advance_cursor_line(1);
              y++;
            }
            else if((y == ybound - 2) && (y <= buf_yend)) {
              if(!(buf_yend == linecount)) {
                advance_cursor_line(1);
                buf_yend++;
                buf_ystart++;
                scrl(1);
              }
              else
                beep();  
            }
            else
              beep();
            break;
          }
          break;
        case INSERT:
          switch (ch) {
            case KEY_LEFT:
              if(x > 0) {
                x_pos--;
                x--;
              }
              else
                beep();
              break;
            case KEY_RIGHT:
              if(x < xbound - 1 && x_pos < line_size - 1) {
                x_pos++;
                x++;
              }
              else
                beep();
              break;
            case KEY_UP:
              if(y > 0) {
                advance_cursor_line(-1);
                y--;
              }
              else if((y == 0) && (buf_ystart > 0)) {
                advance_cursor_line(-1);
                buf_yend--;
                buf_ystart--;
                scrl(-1);
              }
              else
                beep();
              break;
            case KEY_DOWN:
              if(y < ybound - 2) {
                advance_cursor_line(1);
                y++;
              }
              else if((y == ybound - 2) && (y <= buf_yend)) {
                if(!(buf_yend == linecount)) {
                  advance_cursor_line(1);
                  buf_yend++;
                  buf_ystart++;
                  scrl(1);
                }
                else
                  beep();  
              }
              else
                beep();
              break;
            case 10:
            case KEY_ENTER:
              //call insert_newline_at_cursor()
              break;
            case 127: //Backspace char code
            case KEY_DC:
            case KEY_BACKSPACE:
              //Remove character before cursor in buffer
              break;
            case 27:
              mode = COMMAND;
              break;
            default:
              //Add character at cursor in buffer
              //call inser_char_at_cursor
              file_buf = insert_char_at_cursor(ch, xbound, file_buf, &linecount);
              if(x < xbound - 1)
                x++;
              else {
                x = 1;
                y++;
              }
          }
          break;
    }
    
    move(ybound + 1, 0);
    printw("MODE:%d Buffer Line: %d Buffer Col: %d LN SIZE: %d",mode, line, x_pos, line_size);
    print_coords(e_win, x, y); //Print current window coordinates
    refresh_text(e_win, buf_ystart, buf_yend, file_buf);
		wmove(e_win, y, x);
		wrefresh(e_win);   
  }			
  exit(0);
}

/**
 * A function to print the current coordinates in the lower
 * right corner of the stdscr
 **/
void print_coords(WINDOW * win, int x, int y) {
  //TODO: Create another window called "Status Window"
  //      and print these coordinates to it, as well as
  //      input commands to it i.e. how you write and quit
  //      in Vim
	int maxy, maxx;
	getmaxyx(win, maxy, maxx);
	move(maxy + 1, maxx - 7);
	printw("(%d, %d)", x, y);
  refresh();
}

void refresh_text(WINDOW *win, int startline, int endline, char ** file_buf) {
  int i;
  wmove(win, 0, 0);
  for(i = startline; i < endline; i++) {
    char *line = file_buf[i];
    wprintw(win, line);
    wrefresh(win);
  }
}