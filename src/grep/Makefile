CC = gcc
FLAGS = -Wall -Wextra -Werror -std=c11
TARGET = my_grep

all: my_grep

my_grep:
	$(CC) $(FLAGS) my_grep.c -o my_grep

rebuild: clean all

clean:
	rm my_grep