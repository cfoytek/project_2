#include "edit_buffer.h"

void insert_char_at_cursor(char c) {
    file_buf[line] = realloc(file_buf[line], sizeof(char) * (line_size + 1));
    line_size = strlen(file_buf[line]); //Not updating the size right?
    int i;
    for(i = line_size; i > line_char; i--) {
        file_buf[line][i] = file_buf[line][i-1];
    }
    file_buf[line][line_char] = c;
    line_char++;
}

void advance_cursor_line(int numpos) {
    line += numpos;
    line_size = strlen(file_buf[line]);
}

void advance_cursor_char(int numpos) {
    line_char += numpos;
}