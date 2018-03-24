#include "edit_buffer.h"
#include "globals.h"

void insert_char_at_cursor(char c, int eol, char **file_buf) {
    //Writing a certain number of chars to the screen screws up the string array?
    if(line_size >= eol) {
        insert_line_after_current_line();
    }
    file_buf[line] = realloc(file_buf[line], sizeof(char) * (line_size + 2));
    line_size++; //Not updating the size right?
    int i;
    for(i = line_size; i > x_pos; i--) { //line_size + 1 to include null char?
        file_buf[line][i] = file_buf[line][i-1];
    }
    file_buf[line][x_pos] = c;
    x_pos++; 
}

void insert_line_after_current_line() {
    file_buf = realloc(file_buf, sizeof(char *) * (linecount + 1)); //Add extra line at end of buffer
    linecount++;
    int i;
    for(i = linecount; i > line; i--) {
        file_buf[line] = file_buf[line - 1];
    }
    line++; //Move cursor down one line
    file_buf[line] = "\n\0";
    x_pos = 0;
}

void update_line_size() {
    line_size = strlen(file_buf[line]);
}

void advance_cursor_line(int numpos) {
    line += numpos;
}

void advance_cursor_char(int numpos) {
    x_pos += numpos;
}