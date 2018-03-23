#ifndef _EDIT_BUFFER_H
#define _EDIT_BUFFER_H
#include "file_handler.h"
int buf_xpos; //Absolute character number in line
int buf_ypos; //Absolute line number in buffer

int buf_ystart; //Start of buffer chunk to print to screen
int buf_yend; //End of buffer chunk to print to screen

void insert_char_at_cursor(char c);
void delete_line_at_cursor();
void insert_line_after_current_line(); //Allocate new line in buffer, shift every line after current down one
void insert_newline_at_cursor(); //Allocate new line in buffer, insert newline character at buffer, copy all text to end of line to new string, shift all lines down one, insert copied line after previous line
void allocate_new_string(); //Allocate a new char * in the file buffer
void update_buffer_cursor_y(int win_y);
#endif