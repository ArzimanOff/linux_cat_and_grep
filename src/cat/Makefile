CC = gcc
FLAGS = -Wall -Wextra -Werror -std=c11
TARGET = my_cat

all: my_cat

my_cat:
	$(CC) $(FLAGS) my_cat.c -o my_cat

rebuild: clean all

clean:
	rm my_cat