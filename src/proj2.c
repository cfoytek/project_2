#include "file_handler.h"
#include "edit_buffer.h"
#include <ncurses.h>

void print_coords(WINDOW *, int, int);
void refresh_text(WINDOW *win, int startline, int endline);

WINDOW *create_newwin(int height, int width, int starty, int startx)
{
  WINDOW *local_win = newwin(height, width, starty, startx);
  //box(local_win, 0, 0);
  wrefresh(local_win);

  return (local_win);
}

int main(int argc, char **argv) {	
  char *filename;
  int linecount;
  if(argc != 2) {
    //Don't read file, initialize with empty buffer.
  }
  else {
    filename = argv[1];
    //Read file to buffer
    read_file(filename, &linecount);
  }
	int ch;
	enum modes {COMMAND = 0, INSERT = 1}; //0 = Command, 1 = Insert
	WINDOW *e_win; //Editor window
  WINDOW *stat_win;
	int x = 0;
  int y = 0;
	int maxx; //Max screen width, width of terminal
  int maxy; //Max screen height, height of terminal
  int xbound; //Editor window width
  int ybound; //Editor window height

	initscr();			/* Start curses mode */
	//cbreak();			/* Enable character at a time buffering */
	raw();				/* Line buffering disabled */
	keypad(stdscr, TRUE);		/* We get F1, F2 etc.. */
	noecho();			/* Don't echo() while we do getch */

	getmaxyx(stdscr, maxy, maxx); //Get maximum dimensions for terminal
	//Set boundaries for editor window
	xbound = maxx - 1; //Set editor width to max width - 1
	ybound = maxy - 4; //Set editor height to max height - 5
  //Set boundaries for file buffer
  buf_ystart = 0;
  buf_yend = ybound - 1;
	e_win = create_newwin(ybound, xbound, y, x);
  line = 0;
  move(ybound + 1, 0);
  printw("Buffer Line: %d Buffer Col: ", line, line_char);
	refresh();
	scrollok(e_win, TRUE);
  idlok(e_win, TRUE);
	wmove(e_win, y, x);
	wrefresh(e_win);

	getbegyx(e_win, y, x);
	print_coords(e_win, x, y);
	wmove(e_win, y, x);
  refresh_text(e_win, buf_ystart, buf_yend);
  
  wrefresh(e_win);
	while((ch = getch()) != 27) { //27 is char code for ESC or ALT
    //Using ESC to exit will cause a delay because ncurses will
    //Wait to see if the character is ALT and wait for another 
    //keypress before accepting that the key is ESC
    switch (ch) {
      case KEY_LEFT:
        if(x > 0)
          x--;
        else
          beep();
        break;
      case KEY_RIGHT:
        if(x < xbound - 1)
          x++;
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
      default:
        //Add character at cursor in buffer
        //call inser_char_at_cursor
        waddch(e_win, (char)ch);
        if(x < xbound)
          x++;
        else {
          x = 1;
          y++;
        }
		}
    move(ybound + 1, 0);
    printw("Buffer Line: %d Buffer Col: %d", line, line_char);
    print_coords(e_win, x, y); //Print current window coordinates
    refresh_text(e_win, buf_ystart, buf_yend);
		wmove(e_win, y, x);
		wrefresh(e_win);   
  }
	endwin();			/* End curses mode		  */
	return 0;
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

void refresh_text(WINDOW *win, int startline, int endline) {
  int i;
  wmove(win, 0, 0);
  for(i = startline; i < endline; i++) {
    char *line = file_buf[i];
    wprintw(win, line);
  }
}