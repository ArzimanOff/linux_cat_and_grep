CC = gcc
FLAGS = -Wall -Wextra -Werror -std=c11
TARGET = s21_grep

all: s21_grep

s21_grep:
	$(CC) $(FLAGS) s21_grep.c -o s21_grep

rebuild: clean all

clean:
	rm s21_grep