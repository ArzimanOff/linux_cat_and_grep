CC = gcc
FLAGS = -Wall -Wextra -Werror -std=c11
TARGET = s21_cat

all: s21_cat

s21_cat:
	$(CC) $(FLAGS) s21_cat.c -o s21_cat

rebuild: clean all

clean:
	rm s21_cat