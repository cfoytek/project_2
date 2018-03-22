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

/** File Buffer **/
char **file_buf;
/**
 * Fill buffer with contents of file.
 **/
void read_file(const char *file_name);
/**
 * Write buffer's contents to file.
 **/
void write_file(const char *file_name);
#endif