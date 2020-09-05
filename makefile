CC = gcc
FLAGS = -g -ansi -Wall -Wextra -pedantic
FILES = main.c lib_lista.c lib_spcinv.c lib_telas.c
LINKS = -lm -lncurses


space: main.c lib_lista.c lib_lista.h lib_spcinv.c lib_spcinv.h lib_telas.c lib_telas.h
	clear
	$(CC) $(FLAGS) -o space $(FILES) $(LINKS)
