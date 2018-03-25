/**
 * Defines a 2-dimensional array of character
 * pointers that hold the contents of the
 * currently opened file in memory. Functions
 * to support reading and writing the file
 * buffer to the disk are also defined.
 **/
#ifndef _FILE_HANDLER_H
#define _FILE_HANDLER_H
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>

static const int M_LN_SIZE = 156;
static int f_lines;
extern int errno;
/**
 * Fill buffer with contents of file.
 **/
char** read_file(const char *file_name, int *line_count);
/**
 * Write buffer's contents to file.
 **/
void write_file(const char *file_name, char **file_buf, int line_count);
/**
 * Free all memory associated with the file
 * buffer.
 **/
void free_buf(char ** file_buf);
/**
 * This overridden free_buf will first write
 * the file buffer to the file file_name before
 * destorying the buffer.
 **/
// void write_file_free_buf(const char *file_name);
#endif