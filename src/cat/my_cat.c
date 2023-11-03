#include "my_cat.h"

int main(int argc, char *argv[]) {
  cat_flags cat_flags;
  char **files;
  int files_count = 0;

  analyze_arguments(&cat_flags, argc, argv, &files_count, &files);

  if (cat_flags.error == 0)
    run_text_processing(cat_flags, files_count, files);
  else {
    printf("Ошибка ввода флагов!");
  }

  for (int i = 0; i < files_count; i++) free(files[i]);
  free(files);
  return 0;
}

int analyze_arguments(cat_flags *cat_flags, int argc, char *argv[],
                      int *files_count, char ***files) {
  cat_flags->error = 0;
  cat_flags->b = false;
  cat_flags->e = false;
  cat_flags->n = false;
  cat_flags->s = false;
  cat_flags->t = false;
  cat_flags->v = false;
  char short_opt[] = "beEnstTv";

  static struct option long_opt[] = {
      {"number-nonblank", no_argument, NULL, 'b'},
      {"number", no_argument, NULL, 'n'},
      {"squeeze-blank", no_argument, NULL, 's'},
      {NULL, 0, NULL, 0}};

  int c;
  while ((c = getopt_long(argc, argv, short_opt, long_opt, NULL)) != -1) {
    switch (c) {
      case 'b':
        cat_flags->b = true;
        break;
      case 'e':
        cat_flags->e = true;
        cat_flags->v = true;
        break;
      case 'E':
        cat_flags->e = true;
        break;
      case 'n':
        cat_flags->n = true;
        break;
      case 's':
        cat_flags->s = true;
        break;
      case 't':
        cat_flags->t = true;
        cat_flags->v = true;
        break;
      case 'T':
        cat_flags->t = true;
        break;
      case 'v':
        cat_flags->v = true;
        break;
      case '?':
        cat_flags->error++;
    }
  }

  if (optind < argc) {
    *files_count = argc - optind;
    *files = malloc((*files_count) * sizeof(char *));

    int i = 0;
    do {
      (*files)[i] = malloc((strlen(argv[optind]) + 1) * sizeof(char));
      strcpy((*files)[i], argv[optind]);
      i++;
    } while (++optind < argc);
  } else {
    *files_count = 0;
  }
  return 0;
}

void process_flag_t(char *current_line, int *count) {
  for (int i = 0; i < *count; i++) {
    if (current_line[i] == '\t') {
      for (int j = *count + 1; j > i + 1; j--)
        current_line[j] = current_line[j - 1];
      current_line[i] = '^';
      current_line[i + 1] = 'I';
      (*count)++;
    }
  }
}

void process_flag_e(char *current_line, int *count) {
  current_line[*count - 1] = END_OF_LINE_MARK;
  current_line[*count] = '\n';
  current_line[*count + 1] = 0;
  (*count)++;
}

void process_flag_v(char *current_line, int *count) {
  for (int i = 0; i < *count; i++) {
    if ((current_line[i] >= 0) && (current_line[i] < 32) &&
        (current_line[i] != 9) && (current_line[i] != 10)) {
      for (int j = *count + 1; j > i + 1; j--)
        current_line[j] = current_line[j - 1];
      current_line[i + 1] = current_line[i] + 64;
      current_line[i] = '^';
      (*count)++;
    }
    if (current_line[i] == 127) {
      for (int j = (*count) + 1; j > i + 1; j--)
        current_line[j] = current_line[j - 1];
      current_line[i + 1] = '?';
      current_line[i] = '^';
      (*count)++;
    }
    if (((unsigned char)current_line[i] >= 128) &&
        ((unsigned char)current_line[i] < 160)) {
      for (int j = (*count) + 3; j > i + 1; j--)
        current_line[j] = current_line[j - 3];
      current_line[i + 3] = current_line[i] - 64;
      current_line[i + 2] = '^';
      current_line[i + 1] = '-';
      current_line[i] = 'M';
      (*count) += 3;
    }
#ifdef __APPLE__
    if ((unsigned char)current_line[i] >= 160) {
      for (int j = (*count) + 2; j > i + 1; j--)
        current_line[j] = current_line[j - 2];
      current_line[i + 2] = current_line[i] - 128;
      current_line[i + 1] = '-';
      current_line[i] = 'M';
      (*count) += 2;
    }
#endif
  }
}

void print_no_file_error(char **files, int i) {
  if (i != 0) printf("\n");
  printf("cat: %s: No such file or directory\n", files[i]);
}

int run_text_processing(cat_flags cat_flags, int files_count, char **files) {
  FILE *file;
  int bufsize = 4096;
  char current_line[bufsize];
  int num_of_line = 0;
  int last_line_empty = 0;
  int last_char_end_line = 1;

  for (int i = 0; i < files_count; i++) {
    file = fopen(files[i], "r");

    if (file == NULL) {
      print_no_file_error(files, i);
    } else {
      int count;
      while ((count = read_str(current_line, file)) != -1) {
        int empty = 0;
        if (strcmp(current_line, "\n") == 0) empty = 1;
        if (cat_flags.t) process_flag_t(current_line, &count);
        if ((cat_flags.e) && (current_line[count - 1] == '\n'))
          process_flag_e(current_line, &count);
        if (cat_flags.v) process_flag_v(current_line, &count);

        print_str(cat_flags, &last_line_empty, &num_of_line,
                  &last_char_end_line, current_line, count, empty);
      }
      fclose(file);
#ifdef __APPLE__
      num_of_line = 0;
#endif
    }
  }
  return 0;
}

int read_str(char *str, FILE *file) {
  int i = 0;
  while (1) {
    str[i] = fgetc(file);
    if (feof(file) != 0) break;
    i++;
    if (str[i - 1] == '\n') break;
  }
  str[i] = '\0';
  if (i == 0) i = -1;
  return i;
}

int print_str(cat_flags cat_flags, int *last_line_empty, int *num_of_line,
              int *last_char_end_line, char *str, int count, int empty) {
  if (!((cat_flags.s) && (*last_line_empty == 1) && (empty == 1))) {
#ifndef __APPLE__
    if (*last_char_end_line == 1) {
#endif
      if (((cat_flags.n) && (!cat_flags.b)) ||
          ((cat_flags.b) && (empty == 0))) {
        (*num_of_line)++;
        printf("%6d\t", *num_of_line);
      }
#ifndef __APPLE__
    }
#endif
    for (int i = 0; i < count; i++) {
      fputc(str[i], stdout);
    }

    *last_char_end_line = (str[count - 1] == '\n') ? 1 : 0;
    *last_line_empty = (empty == 1) ? 1 : 0;
  }
  return 0;
}