#include "file_handler.h"
char** read_file(const char *file_name, int *line_count) {
    char **file_buf = NULL;
    FILE *fp = NULL;
    int i;
    int line_counter = 0;
    int line_len;
    int line[M_LN_SIZE];    //Adds restriction that lines must be less than M_LN_SIZE
    *line_count = 0;        //Zero out return value
    fp = fopen(file_name, "r");
    if(fp == NULL) {
        fprintf(stderr, "Cannot read file.\n%s", strerror(errno));
        exit(1);
    }
    //Count number of lines in the file
    while(fgets(line, sizeof(line), fp) != NULL) {
        line_counter++;
    }
    if(line_counter == 0){
        file_buf = (char**)malloc(sizeof(char *));
        file_buf[0] = (char*)malloc(sizeof(char)*2);
        file_buf[0][0] = '\n';
        file_buf[0][1] = '\0';
        *line_count = 1;
        return file_buf;
    }
    rewind(fp);
    //Allocate space for lines in buffer
    file_buf = malloc(line_counter * sizeof(char *));
    if(file_buf == NULL) {
       exit(1);            //Error allocating memory
    }
    //Copy lines from file into buffer
    for(i = 0; i < line_counter; i++) {
        fgets(line, sizeof(line), fp);  //We will preserve '\n'
        line_len = strlen(line);
        file_buf[i] = malloc((line_len + 1) * sizeof(char));
        strcpy(file_buf[i], line);
    }
    if(file_buf[line_counter - 1][line_len] != '\n') {
        file_buf[line_counter - 1] = (char *) realloc(file_buf[line_counter - 1], sizeof(char) * (line_len + 1));
        file_buf[line_counter - 1][line_len] = '\n';
    }
    *line_count = line_counter;
    f_lines = line_counter;
    return file_buf;
}

void write_file(const char *file_name, char **file_buf, int line_count) {
    FILE *fp = NULL;
    fp = fopen(file_name, "w");
    if(fp == NULL) {
        fprintf(stderr, "Cannot open file for writing.\n%s", strerror(errno));
        exit(1);
    }
    int i = 0;
    while(i < line_count) {
        const char *line = file_buf[i];
        fputs(line, fp);
        i++;
    }
    fclose(fp);
}

void free_buf(char ** file_buf) {
    int line_count = sizeof(file_buf) / sizeof(file_buf[0]);
    line_count = 37;
    int i;
    for(i = 0; i < line_count; i++) {
        free(file_buf[i]);
    }
    free(file_buf);
    file_buf = NULL;
}

// void write_file_free_buf(const char *file_name) {
//     write_file(file_name);
//     free_buf(file_buf);
// }