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
	WINDOW *my_win;
	int x = 2;
        int y = 2;

	initscr();			/* Start curses mode 		*/
	cbreak();
	raw();				/* Line buffering disabled	*/
	keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
	noecho();			/* Don't echo() while we do getch */

    	printw("Press q  to quit\n");
	refresh();

	my_win = create_newwin(30, 70, y, x);
	wmove(my_win, y, x);
	wrefresh(my_win);

	while((ch = getch()) != 'q')
        {
	    //addch(ch);
            switch (ch)
            {
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
	      default:
		waddch(my_win, (char)ch);
 	    }

          wmove(my_win, y, x);
          wrefresh(my_win);
          
        }
    
	endwin();			/* End curses mode		  */
	return 0;
}
