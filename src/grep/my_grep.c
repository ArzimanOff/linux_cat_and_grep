#include "my_grep.h"

regex_t *get_compiled_regex(regex_t *regex_list, char **patterns,
                            int lines_count, int cflags, int *regerr) {
  regex_list = (regex_t *)malloc(lines_count * sizeof(regex_t));

  if (regex_list) {
    for (int i = 0; i < lines_count; i++) {
      *regerr = regcomp(regex_list + i, patterns[i], cflags);
    }
  } else {
    *regerr = -1;
  }
  return regex_list;
}

char **get_regex_pattern(char **patterns, char *new_line, int *lines_count,
                         int *reg_getting_status) {
  char **temp = (char **)realloc(patterns, (*lines_count + 1) * sizeof(char *));

  if (temp) {
    patterns = temp;
    patterns[*lines_count] = (char *)malloc(strlen(new_line) + 1);
    if (patterns[*lines_count]) {
      strcpy(patterns[*lines_count], new_line);
      *lines_count = *lines_count + 1;
    } else {
      *reg_getting_status = -1;
    }
  } else {
    *reg_getting_status = -1;
  }

  return patterns;
}

void get_regex_from_file(char ***patterns, char *regex_file_name,
                         int *lines_count, int *reg_getting_status) {
  FILE *this_file_with_regex = fopen(regex_file_name, "r");
  char str[2048];

  if (this_file_with_regex != NULL) {
    while (fgets(str, 2048, this_file_with_regex) != NULL) {
      if (strchr(str, '\n')) *(strchr(str, '\n')) = '\0';
      // if (index(str, '\n')) *(index(str, '\n')) = '\0';

      *patterns =
          get_regex_pattern(*patterns, str, lines_count, reg_getting_status);
    }
    fclose(this_file_with_regex);
  } else {
    *reg_getting_status = -1;
  }
}

int parser(int argc, char *argv[], grep_flags *flags, char ***patterns,
           int *lines_count) {
  int currenr_flag;
  int err = 0;

  while ((currenr_flag = getopt_long(argc, argv, "e:f:ivcnlhso", 0, NULL)) !=
         -1) {
    switch (currenr_flag) {
      case 'e':
        flags->e = true;
        *patterns = get_regex_pattern(*patterns, optarg, lines_count, &err);
        if (err == -1) {
          fprintf(stderr, "\nНепредвиденная ошибка!\n");
        }
        break;
      case 'i':
        flags->i = true;
        break;
      case 'v':
        flags->v = true;
        break;
      case 'c':
        flags->c = true;
        break;
      case 'n':
        flags->n = true;
        break;
      case 'l':
        flags->l = true;
        break;
      case 'h':
        flags->h = true;
        break;
      case 's':
        flags->s = true;
        break;
      case 'f':
        flags->f = true;
        get_regex_from_file(patterns, optarg, lines_count, &err);
        if (err == -1) {
          fprintf(stderr, "%s: %s: No such file or directory", argv[0], optarg);
        }
        break;
      case 'o':
        flags->o = true;
        break;
      default:
        usage_error();
        err = -1;
    }
  }
  return err;
}

void print_line(grep_flags *flags, char *line, int *line_num) {
  if (flags->n) {
    printf("%d:%s\n", *line_num, line);
  } else {
    printf("%s\n", line);
  }
}

void print_line_with_file_name(char *current_file_name, grep_flags *flags,
                               char *line, int *line_num) {
  if (flags->n) {
    printf("%s:%d:%s\n", current_file_name, *line_num, line);
  } else {
    printf("%s:%s\n", current_file_name, line);
  }
}

void other_optoins_to_invert(int argc, char *current_file_name,
                             grep_flags *flags, char *line, int *line_num,
                             int *matches_count, int *is_need_filename) {
  if ((!flags->c && !flags->l && !flags->o) ||
      (!flags->c && !flags->l && flags->o && flags->v)) {
    if ((argc - optind == 1) || flags->h) {
      print_line(flags, line, line_num);
    } else {
      print_line_with_file_name(current_file_name, flags, line, line_num);
    }
  } else if (flags->c && flags->l) {
    *matches_count = 1;
    *is_need_filename = 1;
  } else if (flags->c && !flags->l) {
    *matches_count = *matches_count + 1;
  } else if (!flags->c && flags->l) {
    *is_need_filename = 1;
  }
}

void property_output(int argc, char *current_file_name, grep_flags *flags,
                     int matches_count, int is_need_filename) {
  if ((argc - optind == 1) || flags->h) {
    if (flags->c && !flags->l) {
      printf("%d\n", matches_count);
    } else if (flags->c && flags->l) {
      printf("%d\n", matches_count);
      if (is_need_filename) printf("%s\n", current_file_name);
    } else if (!flags->c && flags->l && is_need_filename) {
      printf("%s\n", current_file_name);
    }
  } else {
    if (flags->c && !flags->l) {
      printf("%s:%d\n", current_file_name, matches_count);
    } else if (flags->c && flags->l) {
      printf("%s:%d\n", current_file_name, matches_count);
      if (is_need_filename) printf("%s\n", current_file_name);
    } else if (!flags->c && flags->l && is_need_filename) {
      printf("%s\n", current_file_name);
    }
  }
}

void run_process(int argc, char *argv[], regex_t **regex_list, char **patterns,
                 int lines_count, grep_flags *flags) {
  char current_line_from_file[2048];
  int error = 0, matches_count = 0, line_num = 0, is_need_filename = 0,
      offset = 0;
  FILE *current_file;
  regmatch_t match;
  int regerr = 0;

  *regex_list = get_compiled_regex(
      *regex_list, patterns, lines_count,
      flags->i ? REG_ICASE | REG_EXTENDED : REG_EXTENDED, &regerr);

  if (regerr != 0) {
    printf("Regex error");
    return;
  }

  for (int i = optind; i < argc; i++) {
    current_file = fopen(argv[i], "r");
    if (current_file != NULL) {
      is_need_filename = 0;
      line_num = 0;
      matches_count = 0;

      while (fgets(current_line_from_file, 2048, current_file) != NULL) {
        int lines_similar_flag = 0;
        offset = 0;

        if (strchr(current_line_from_file, '\n'))
          *(strchr(current_line_from_file, '\n')) = '\0';

        line_num++;
        for (int j = 0; j < lines_count; j++) {
          if ((error = regexec(*regex_list + j, current_line_from_file, 1,
                               &match, 0)) == 0) {
            lines_similar_flag = 1;
            if (flags->o) {
              while ((error = regexec(*regex_list + j,
                                      current_line_from_file + offset, 1,
                                      &match, 0)) == 0) {
                if (!flags->l && !flags->c && !flags->v) {
                  if (((argc - optind > 1) && !flags->h) && (offset == 0)) {
                    printf("%s:", argv[i]);
                  }
                  if (flags->n && (offset == 0)) {
                    printf("%d:", line_num);
                  }
                  printf("%.*s\n", (int)(match.rm_eo - match.rm_so),
                         (current_line_from_file + offset + match.rm_so));
                }
                offset += match.rm_eo;
              }
            }
          }
        }

        if ((flags->v && !lines_similar_flag) ||
            ((!flags->v && lines_similar_flag))) {
          other_optoins_to_invert(argc, argv[i], flags, current_line_from_file,
                                  &line_num, &matches_count, &is_need_filename);
        }
      }
      property_output(argc, argv[i], flags, matches_count, is_need_filename);
      fclose(current_file);
    } else if (!flags->s) {
      fprintf(stderr, "%s: %s: No such file or directory\n", argv[0], argv[i]);
    }
  }
}

void freeArrays(char **patterns, regex_t *regex_list, int lines_count) {
  if (patterns != NULL) {
    for (int i = 0; i < lines_count; i++) {
      free(patterns[i]);
    }
    free(patterns);
  }
  if (regex_list != NULL) {
    for (int i = 0; i < lines_count; i++) {
      regfree(regex_list + i);
    }
    free(regex_list);
  }
}

void usage_error() {
  fprintf(stderr,
          "usage:\ngrep [-ivclnhso] [file ...]\nor grep [-options] -e [regex] "
          "[file ...]\nor grep [-options] -f [file_with_regex] [file ...]");
}

int main(int argc, char *argv[]) {
  grep_flags flags = {false, false, false, false, false,
                      false, false, false, false, false};
  char **patterns = NULL;
  int err = 0;
  int lines_count = 0;
  int reg_getting_status = 0;
  regex_t *regex_list = NULL;

  if ((err = parser(argc, argv, &flags, &patterns, &lines_count)) == 0) {
    if ((!flags.e) && (!flags.f) && (argc != optind)) {
      patterns = get_regex_pattern(patterns, argv[optind], &lines_count,
                                   &reg_getting_status);
      optind++;
    }
    if (argc == optind) {
      usage_error();
    } else {
      run_process(argc, argv, &regex_list, patterns, lines_count, &flags);
    }
  }

  freeArrays(patterns, regex_list, lines_count);

  return 0;
}