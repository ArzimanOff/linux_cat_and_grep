#ifndef SRC_CAT_H
#define SRC_CAT_H
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define END_OF_LINE_MARK '$'

typedef struct {
  int error;
  bool b;
  bool e;
  bool n;
  bool s;
  bool t;
  bool v;
} cat_flags;

int analyze_arguments(cat_flags *p, int argc, char *argv[], int *fcount,
                      char ***files);
void print_no_file_error(char **files, int i);
int read_str(char *str, FILE *fp);
int run_text_processing(cat_flags p, int fcount, char **files);
void process_flag_t(char *current_line, int *count);
void process_flag_e(char *current_line, int *count);
void process_flag_v(char *current_line, int *count);
int print_str(cat_flags p, int *last_line_empty, int *num_of_line,
              int *last_char_end_line, char *str, int count, int empty);

#endif