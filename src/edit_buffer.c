#include "edit_buffer.h"
#include "globals.h"

char** insert_char_at_cursor(char c, int eol, char **file_buf, int *linecount) {
    //Writing a certain number of chars to the screen screws up the string array?
    if(line_size >= eol) {
        file_buf = insert_line_after_current_line(linecount, file_buf);
        x_pos = 0;
        file_buf[line][x_pos] = c;
        file_buf[line][x_pos+1] = '\n';
        file_buf[line][x_pos+2] = '\0';
        x_pos++;
        update_line_size(file_buf);
    }
    else{
        file_buf[line] = (char *)realloc(file_buf[line], sizeof(char) * (line_size + 2));
        line_size++; //Not updating the size right?
        int i;
        for(i = line_size; i > x_pos; i--) {
            file_buf[line][i] = file_buf[line][i-1];
        }
        file_buf[line][x_pos] = c;
        x_pos++; 
    }
    return file_buf;
}

char** insert_line_after_current_line(int *linecount, char **file_buf) {
    file_buf = (char **)realloc(file_buf, sizeof(char *) * ((*linecount) + 1)); //Add extra line at end of buffer
    (*linecount)++;
    int i;
    for(i = (*linecount)-1; i > line; i--) {
        file_buf[i] = file_buf[i - 1];
    }
    advance_cursor_line(1);//Move cursor down one line
    file_buf[line] = (char *)malloc(sizeof(char) * 3);
    file_buf[line][0] = '\n';
    file_buf[line][1] = '\0';
    update_line_size(file_buf);
    return file_buf;
}

char** delete_line_at_cursor(char **file_buf){
    file_buf[line] = (char *)realloc(file_buf[line], sizeof(char) * 2);
    file_buf[line][0] = '\n';
    file_buf[line][1] = '\0';
    return file_buf;
}
void update_line_size(char** file_buf) {
    line_size = strlen(file_buf[line]);
}

void advance_cursor_line(int numpos) {
    line += numpos;
}

void advance_cursor_char(int numpos) {
    x_pos += numpos;
}
char** delete_char_at_cursor(char **file_buf, int *x_pos, int line){
    int i;
    for(i = (*x_pos)-1; i < line_size; i++){
        file_buf[line][i] = file_buf[line][i+1];
    }
    (*x_pos)--;
    return file_buf;
}

char** insert_newline_at_cursor(char** file_buf, int *x_pos, int *line, int line_size, int *linecount){
    int i;
    int numChars = (line_size) - (*x_pos);
    char* temp_buf;
    temp_buf = (char*) malloc(sizeof(char)*(numChars));
    for(i = (*x_pos); i <= line_size; i++){
        temp_buf[i-(*x_pos)] = file_buf[(*line)][i];
        file_buf[*(line)][i] = NULL;
    }
    file_buf[(*line)] = (char*)realloc(file_buf[*(line)], sizeof(char)*(*x_pos + 1));
    file_buf[(*line)][(*x_pos)] = '\n';
    file_buf[(*line)][(*x_pos)+1] = '\0';
    file_buf = insert_line_after_current_line(linecount,file_buf);
    file_buf[(*line)] = temp_buf;
    (*x_pos) = 0;
    return file_buf;
}