#ifndef _SCREEN_HANDLER_H
#define _SCREEN_HANDLER_H
#include <ncurses.h>

void print_buf_to_win(WINDOW *win, int startline, int endline);
//Scroll window down one line and update text on screen
void scroll_down(WINDOW *win);
//Scroll window up one line and update text on screen
void scroll_up(WINDOW *win);
//Insert line in Ncurses window and call function to update buffer
void insert_line_at_cursor(WINDOW *win);
//Delete line in Ncurses window and call function to update buffer
void delete_line_at_cursor(WINDOW *win);
#endif