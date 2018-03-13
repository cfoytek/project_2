#include<stdio.h>
#include <ncurses.h>


WINDOW *create_newwin(int height, int width, int starty, int startx)
{
  WINDOW *local_win = newwin(height, width, starty, startx);
  box(local_win, 0, 0);
  wrefresh(local_win);

  return (local_win);
}

int main()
{	int ch;
	WINDOW *e_win; //Editor window
	int x = 2;
        int y = 2;

	initscr();			/* Start curses mode 		*/
	//cbreak();			/* Enable character at a time buffering */
	raw();				/* Line buffering disabled	*/
	keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
	noecho();			/* Don't echo() while we do getch */

    printw("Press q  to quit\n");
	refresh();

	e_win = create_newwin(30, 70, y, x);
	scrollok(e_win, TRUE);
	wmove(e_win, y, x);
	wrefresh(e_win);

	while((ch = getch()) != 'q'){
	    //addch(ch);
        switch (ch){
          case KEY_LEFT:
            x--;
            break;
          case KEY_RIGHT:
            x++;
            break;
          case KEY_UP:
            y--;
            break;
          case KEY_DOWN:
            y++;
            break;
          case KEY_ENTER:
          	break;
          case KEY_BACKSPACE:
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
