#include "edit_buffer.h"
#include "globals.h"

void insert_char_at_cursor(char c, int eol, char **file_buf, int linecount) {
    //Writing a certain number of chars to the screen screws up the string array?
    if(line_size >= eol) {
        insert_line_after_current_line(linecount, file_buf);
    }
    file_buf[line] = (char *)realloc(file_buf[line], sizeof(char) * (line_size + 2));
    line_size++; //Not updating the size right?
    int i;
    for(i = line_size; i > x_pos; i--) {
        file_buf[line][i] = file_buf[line][i-1];
    }
    file_buf[line][x_pos] = c;
    x_pos++; 
}

void insert_line_after_current_line(int linecount, char **file_buf) {
    char **temp = malloc(sizeof(char *) * (linecount + 1));
    int i;
    //linecount++;
    for(i = 0; i <= line; i++) {
        int line_len = strlen(file_buf[i]);
        temp[i] = malloc((line_len + 1) * sizeof(char));
        strncpy(temp[i], file_buf[i], line_len);
    }
    temp[line + 1] = malloc(sizeof(char) * 2);
    temp[line + 1] = "\n\0";
    int k;
    for(k = line + 2; k < linecount; k++) {
        int line_len = strlen(file_buf[k]);
        temp[k] = malloc((line_len + 1) * sizeof(char));
        strncpy(temp[k], file_buf[k], line_len);
    }
    line++;
    x_pos = 0;
    free_buf(file_buf);
    file_buf = temp;
    // file_buf = (char **)realloc(file_buf, sizeof(char *) * (linecount + 1)); //Add extra line at end of buffer
    // linecount++;
    // int i;
    // for(i = linecount-1; i > line; i--) {
    //     file_buf[i] = file_buf[i - 1];
    // }
    // line++; //Move cursor down one line
    // file_buf[line] = "\n";
    // x_pos = 0;
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