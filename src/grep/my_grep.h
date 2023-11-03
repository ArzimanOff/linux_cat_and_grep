#ifndef GREP_H
#define GREP_H

#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
  bool e;
  bool v;
  bool i;
  bool l;
  bool c;
  bool n;
  bool h;
  bool s;
  bool f;
  bool o;
} grep_flags;

regex_t *get_compiled_regex(regex_t *regex_list, char **patterns,
                            int lines_count, int cflags, int *regerr);
char **get_regex_pattern(char **patterns, char *template_line, int *lines_count,
                         int *reg_getting_status);
void get_regex_from_file(char ***patterns, char *regex_file_name,
                         int *lines_count, int *reg_getting_status);
int parser(int argc, char *argv[], grep_flags *flags, char ***patterns,
           int *lines_count);
void print_line(grep_flags *flags, char *line, int *line_num);
void print_line_with_file_name(char *current_file_name, grep_flags *flags,
                               char *line, int *line_num);
void property_output(int argc, char *current_file_name, grep_flags *flags,
                     int matches_count, int is_need_filename);
void other_optoins_to_invert(int argc, char *current_file_name,
                             grep_flags *flags, char *line, int *line_num,
                             int *matches_count, int *is_need_filename);
void run_process(int argc, char *argv[], regex_t **regex_list, char **patterns,
                 int lines_count, grep_flags *flags);
void freeArrays(char **patterns, regex_t *regex_list, int lines_count);
void usage_error();

#endif