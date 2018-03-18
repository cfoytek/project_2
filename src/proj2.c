#include<stdio.h>
#include <ncurses.h>

void print_coords(WINDOW *, int, int);

WINDOW *create_newwin(int height, int width, int starty, int startx)
{
  WINDOW *local_win = newwin(height, width, starty, startx);
  box(local_win, 0, 0);
  wrefresh(local_win);

  return (local_win);
}

int main(){	
	int ch;
	enum modes {NORMAL = 0, INSERT = 1}; //0 = Normal, 1 = Insert
	WINDOW *e_win; //Editor window
	int x = 1;
  int y = 1;
	int maxx, maxy, xbound, ybound;

	initscr();			/* Start curses mode 		*/
	//cbreak();			/* Enable character at a time buffering */
	raw();				/* Line buffering disabled	*/
	keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
	noecho();			/* Don't echo() while we do getch */

  printw("Press ESC to quit\n");
	refresh();

	getmaxyx(stdscr, maxy, maxx);
	//Set boundaries for window
	xbound = maxx - 5;
	ybound = maxy - 5;
	e_win = create_newwin(ybound, xbound - 5, y, x);
	scrollok(e_win, TRUE);
	wmove(e_win, y, x);
	wrefresh(e_win);

	getbegyx(e_win, y, x);
	print_coords(e_win, x, y);
	wmove(e_win, y, x);
	while((ch = getch()) != 27) { //27 is char code for ESC or ALT
			//Using ESC to exit will cause a delay because ncurses will
			//Wait to see if the character is ALT and wait for another 
			//keypress before accepting that the key is ESC
			print_coords(e_win, x, y); //Print current window coordinates
			refresh();
			switch (ch){
				case KEY_LEFT:
					if(x > 0)
						x--;
					break;
				case KEY_RIGHT:
					if(x < xbound)
						x++;
					break;
				case KEY_UP:
					if(y > 0)
						y--;
					break;
				case KEY_DOWN:
					if(y < ybound)
						y++;
					break;
				case KEY_ENTER:
					break;
				case 127: //Backspace char code
				case KEY_DC:
				case KEY_BACKSPACE:
					delch();
					wrefresh(e_win);
					break;
				default:
					waddch(e_win, (char)ch);
					x++;
					wrefresh(e_win);
		}
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
	int maxy, maxx;
	getmaxyx(win, maxy, maxx);
	move(maxy, maxx - 10);
	printw("(%d, %d)", x, y);
}