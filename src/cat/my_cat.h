#ifndef SRC_CAT_MAIN_H_
#define SRC_CAT_MAIN_H_
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
} Flags;

int analyze_arguments(Flags *p, int argc, char *argv[], int *fcount, char ***files);
void print_no_file_error(char **files, int i);
int read_str(char *str, FILE *fp);
int run_text_processing(Flags p, int fcount, char **files);
void process_flag_t(char *buffer, int *count);
void process_flag_e(char *buffer, int *count);
void process_flag_v(char *buffer, int *count);
int print_str(Flags p, int *last_empty, int *num_of_line, int *lastendsnewstr, char *str, int count, int empty);


#endif  // SRC_CAT_MAIN_H_