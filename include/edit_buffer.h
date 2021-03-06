#ifndef _EDIT_BUFFER_H
#define _EDIT_BUFFER_H
#include "file_handler.h"
int x_pos; //Absolute character number in line
int line; //Absolute line number in buffer
int line_size; //Size fo the current line

int buf_ystart; //Start of buffer chunk to print to screen
int buf_yend; //End of buffer chunk to print to screen

void advance_cursor_char(int numpos); //Advance cursor one position in the x direction
void advance_cursor_line(int numpos); //Advance cursor one position in the y direction
char** insert_char_at_cursor(char c, int eol, char **file_buf, int *linecount);
void update_line_size(char **);
char** delete_line_at_cursor(char **file_buf);
char** insert_line_after_current_line(int *linecount, char **file_buf); //Allocate new line in buffer, shift every line after current down one
char** insert_newline_at_cursor(char** file_buf, int *x_pos, int *line, int line_size, int *linecount); //Allocate new line in buffer, insert newline character at buffer, copy all text to end of line to new string, shift all lines down one, insert copied line after previous line
void allocate_new_string(); //Allocate a new char * in the file buffer
void update_buffer_cursor_y(int win_y);
char** delete_char_at_cursor(char **file_buf, int *x_pos, int line);
#endif