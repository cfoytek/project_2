#include "edit_buffer.h"

void insert_char_at_cursor(char c) {

}

void advance_cursor_line(int numpos) {
    line += numpos;
}

void advance_cursor_char(int numpos) {
    line_char += numpos;
}