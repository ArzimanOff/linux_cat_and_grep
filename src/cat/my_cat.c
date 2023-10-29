#include "s21_cat.h"

int main(int argc, char *argv[]) {
  Flags flags;   // структура, хранящая флаги
  char **files;  // массив указателей на массив символов, то есть массив
                 // указателей на строки, здесь будут храниться названия файлов
  int files_count = 0;  // кол-во файлов в argv для дальнейшей обработки

  // анализируем полученные аргументы
  analyze_arguments(&flags, argc, argv, &files_count, &files);

  // если ВСЕ введённые флаги корректны:
  if (flags.error == 0)
    // запускаем обработку текста полученных файлов
    run_text_processing(flags, files_count, files);
  else {
    printf("Ошибка ввода флагов!");
  }

  // не забываем очистить память, выделенную под массив для записи названий
  // файлов:
  for (int i = 0; i < files_count; i++) free(files[i]);
  free(files);
  return 0;
}

int analyze_arguments(Flags *flags, int argc, char *argv[], int *files_count,
                      char ***files) {
  flags->error = 0;
  flags->b = false;
  flags->e = false;
  flags->n = false;
  flags->s = false;
  flags->t = false;
  flags->v = false;
  char short_opt[] = "beEnstTv";  // список хранящий короткие флаги, которые следует обработать

  // список хранящий ДИННЫЕ GNU флаги и их аналоги
  static struct option long_opt[] = {
      {"number-nonblank", no_argument, NULL, 'b'},
      {"number", no_argument, NULL, 'n'},
      {"squeeze-blank", no_argument, NULL, 's'},
      {NULL, 0, NULL, 0}};

  int c;  // текущий символ который прочитал getopt (предполагаемый флаг)

  // считываем символы пока они есть в нужном нам аргументе
  while ((c = getopt_long(argc, argv, short_opt, long_opt, NULL)) != -1) {
    switch (c) {
      case 'b':
        flags->b = true;
        break;
      case 'e':
        flags->e = true;
        flags->v = true;
        break;
      case 'E':
        flags->e = true;
        break;
      case 'n':
        flags->n = true;
        break;
      case 's':
        flags->s = true;
        break;
      case 't':
        flags->t = true;
        flags->v = true;
        break;
      case 'T':
        flags->t = true;
        break;
      case 'v':
        flags->v = true;
        break;
      case '?':
        flags->error++;
    }
  }

  // optind - индекс следующего аргумента для обработки
  // если индекс следующего аргумента строго меньше всего кол-ва аргументов,
  // то аргументы еще не закончены, начинается чтение аргументов с названиями
  // файлов
  if (optind < argc) {
    *files_count = argc - optind;  // кол-во файлов = кол-во всех аргументов -
                                   // индекс первого аргумента файла
    *files = malloc((*files_count) *
                    sizeof(char *));  // массив указателей на названия файлов
                                      // (на массивы char, то есть на строки)
    int i = 0;
    do {
      (*files)[i] = malloc((strlen(argv[optind]) + 1) *
                           sizeof(char));  // выделяем память для каждой ячейки
                                           // массива названий файлов
      strcpy((*files)[i], argv[optind]);  // копируем аргумент с индексом optind
                                          // в массив названий файлов
      i++;
    } while (++optind < argc);  // увеличивает индекс обрабатываемого аргумента,
                                // пока он меньше кол-ва всех аргументов
  } else {
    *files_count = 0;
  }
  return 0;
  // при завершении работы функции имеем:
  // список флагов для обработки
  // список файлов для обработки
  // кол-во файлов для обработки
  // информацию об ошибке, в случае если встретился неизвестный флаг
}

// обрабатываем буффер, если включен флаг t
void process_flag_t(char *buffer, int *count) {
  for (int i = 0; i < *count;
       i++) {  // проходимся по всем символам строки в буффере
    if (buffer[i] == '\t') {  // если текущий символ равен табуляции:
      for (int j = *count + 1; j > i + 1;
           j--)  // делаем сдвиг вправо всех символов посел таба:
        buffer[j] =
            buffer[j -
                   1];  // перекидываем текущи символ, на одну позицию вперед

      // на освободившиеся 2 места, вместо символа таба записываем:
      buffer[i] = '^';
      buffer[i + 1] = 'I';

      // увеличиваем длину строки на 1, т.к один символ таба заменили на два
      // символа: ^I
      (*count)++;
    }
  }
}

// обрабатываем буффер, если включен флаг t
void process_flag_e(char *buffer, int *count) {
  buffer[*count - 1] = END_OF_LINE_MARK; // запишем значение доллара в ячейку вместо переноса строки,
  buffer[*count] = '\n'; // а сам перенос строки перенесем в следующую ячейку
  buffer[*count + 1] = 0; // в следующую ячейку запишем символ завершения строки (пустой символ)
  (*count)++; // увеличиваем кол-во букв в строке, так как мы добавили новый символ $
}

void process_flag_v(char *buffer, int *count) {
  // проходимся по всей длине строки: 
  for (int i = 0; i < *count; i++) { 
    // если текущий символ управляющий ( >=0 и <32), при этом не перенос строки и не таб:
    if ((buffer[i] >= 0) && (buffer[i] < 32) && (buffer[i] != 9) && (buffer[i] != 10)) {
      // проходимся от следующей ячейки после завершения строки, до ячейки с текщим символом
      for (int j = *count + 1; j > i + 1; j--) 
        buffer[j] = buffer[j - 1]; // чтобы передвинуть все символы на 1 ячейку вправо
      buffer[i + 1] = buffer[i] + 64; // в появившуюся ячейку записываем символ на 64 больший текущего
      buffer[i] = '^'; // а в старую ячейку символа запишем ^
      (*count)++; // увеличиваем кол-во букв в строке, так как мы добавили новый символ ^
    }

    // если текущий символ пробел (тоже управляющий):
    if (buffer[i] == 127) {
      for (int j = (*count) + 1; j > i + 1; j--) buffer[j] = buffer[j - 1];
      // записываем в две свободные ячейки ^?
      buffer[i + 1] = '?';
      buffer[i] = '^'; 
      (*count)++; // увеличиваем кол-во символов на 1
    }

    // если текущий символ нестандартный:
    if (((unsigned char)buffer[i] >= 128) && ((unsigned char)buffer[i] < 160)) {
      // сдвигаем все символы после текущего на 3 вперед (вправо)
      for (int j = (*count) + 3; j > i + 1; j--) 
        buffer[j] = buffer[j - 3];
      
      // заполняем освободившиеся 4 ячейки по шаблону "M-^c", где с - текущий символ 
      buffer[i + 3] = buffer[i] - 64;
      buffer[i + 2] = '^';
      buffer[i + 1] = '-';
      buffer[i] = 'M';
      (*count) += 3; // увеличиваем длину строки на 3, так как был сдвиг на 3 ячейки
    }
#ifdef __APPLE__
//#ifndef __APPLE__
    if ((unsigned char)buffer[i] >= 160) {
      for (int j = (*count) + 2; j > i + 1; j--) buffer[j] = buffer[j - 2];
      buffer[i + 2] = buffer[i] - 128;
      buffer[i + 1] = '-';
      buffer[i] = 'M';
      (*count) += 2;
    }
#endif
  }
}

void print_no_file_error(char **files, int i) {
  if (i != 0) {
    printf("\n");
  }
  printf("cat: %s: No such file or directory\n", files[i]);
}

int run_text_processing(Flags flags, int files_count, char **files) {
  FILE *file;            // создаем указатель на файл
  int bufsize = 4096;    // рамер буффера для строки
  char buffer[bufsize];  // массив char (то есть строка)
  int num_of_line = 0; // переменная, хранящая номер строки,
  int last_empty = 0;  // 1 - если предыдущая СТРОКА == '\n', иначе 0
  int lastendsnewstr = 1; // 1 - если последний символ строки равен переносу строки, иначе 0

  // проходимся по всем файлам
  for (int i = 0; i < files_count; i++) {
    // открываем файл
    file = fopen(files[i], "r");

    // возвращаем ошибку если файла нет
    if (file == NULL) {
      print_no_file_error(files, i);
    } else {
      int count;  //  переменная, хранящая длину текущей строки, если её удалось
                  //  прочесть
      // Пока следущую строку удаётся прочесть, выполняем:
      while ((count = read_str(buffer, file)) != -1) {
        int empty = 0;  // Переменная-флаг, хранит 1, 
                        // если строка пустая, иначе 0

        if (strcmp(buffer, "\n") == 0) empty = 1;  
        // проверяем пуста ли строка, если все содержимое строки
        // равно лишь переносу строк, то она пуста
        
        // если включен флаг t:
        if (flags.t) {
          process_flag_t(buffer, &count);
        }

        // если включен флаг -e и последний символ равен переносу строки:
        if ((flags.e) && (buffer[count - 1] == '\n')) {
          process_flag_e(buffer, &count);
        }

        // если включен флаг -v:
        if (flags.v) {
          process_flag_v(buffer, &count);
        }

        // выводим только что обработанную строку, имея переменные, хранящие какие-то значения
        print_str(flags, &last_empty, &num_of_line, &lastendsnewstr, buffer, count, empty);
      }
      fclose(file); // закрываем файл, после того как все его строки были обработаны и выведены

#ifdef __APPLE__
      num_of_line = 0; 
      // обнуляем счетчик строк, если программа запускается на Mac, 
      // иначе, продолжаем нумерацию строк с того места где остановились
#endif
    }
#ifndef __APPLE__
    if (i != files_count - 1 && flags.s){
      if (flags.n){
        printf("\n%6d\t", num_of_line + 1);
        (num_of_line)++;
      } else {
        printf("\n");
      }
    }
#endif
  }
  return 0;
}

int read_str(char *str, FILE *file) {
  int i = 0;  // изначально длина строки равна 0
  while (1) {
    str[i] = fgetc(file);  // пробуем записать на место i-той буквы строки str,
                           // то что получила fgetc() из file
    if (feof(file) != 0)
      break;  // завершение чтения, если встретился EOF (конец файла)
    i++;      // увеличение счетчика символов
    if (str[i - 1] == '\n')
      break;  // завершение чтения строки, если встретился перенос строки
  }
  str[i] = '\0';  // помечаем конец строки через символ конца строк "\0"
  if (i == 0)
    i = -1;  // если никаких символов даже переносов строки встречено не было,
             // то длина равна -1
  return i;  // возвращаем длину строки, либо длину строки если она не
             // существует, то есть если строка пуста
}

int print_str(Flags flags, int *last_empty, int *num_of_line, int *lastendsnewstr, char *str, int count, int empty) {
  // *last_empty = указатель на переменную, хранящую 1, если предыдущая строка
  // был переносом строки, иначе 0

  // если хотябы одно из условий не выполнено: 

  if (!((flags.s) && (*last_empty == 1) && (empty == 1))) {
#ifndef __APPLE__
    if (*lastendsnewstr == 1) {
#endif
      if (((flags.n) && (!flags.b)) || ((flags.b) && (empty == 0))) {
        (*num_of_line)++; // увеличиваем счетчик строки
        printf("%6d\t", *num_of_line); // пишем нумерацию 
      }
#ifndef __APPLE__
    }
#endif
    for (int i = 0; i < count; i++) { // проходимся он первого символа полученной строки до последнего и кладем в стандартный вывод 
      fputc(str[i], stdout);
    }

    if (str[count - 1] == '\n') { // если последний символ строки равен переносу строки
      *lastendsnewstr = 1; // запоминаем это
    } else {
      *lastendsnewstr = 0; // иначе отмечаем, то что он не равен переносу строки
    }

    if (empty == 1) { // если текущая строка пуста (то есть равна переносу строки), 
      *last_empty = 1; // помечаем то, что предыдущая строка была пустой, т.к текущая строка станет предыдущей
    } else {
      *last_empty = 0;
    }
  }
  return 0;
}